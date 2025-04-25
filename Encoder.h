#pragma once

#include "RollingHash.h"

#include <algorithm>
#include <string>
#include <iostream>
#include <vector>

struct FindResult
{
	size_t index;
	size_t len;
	size_t next_index;
};

template<size_t N, size_t WINDOW_SIZE>
FindResult findSequence4Chars(const char* buffer, size_t search_start, size_t search_end, size_t lookahead_end)
{
	FindResult result{ lookahead_end, 0, lookahead_end };

	RollingHash<N, WINDOW_SIZE> lookahead_hash{};
	RollingHash<N, WINDOW_SIZE> search_hash{};

	lookahead_hash.initialize(buffer, search_end);

	search_hash.initialize(buffer, search_start);
	size_t search_index = 0;

	while (search_index < search_end
		&& lookahead_hash.getHash() != search_hash.getHash())
	{
		search_index++;
		search_hash.roll(buffer, search_index);
	}

	if (search_index == search_end)
	{
		return result;
	}

	//one chunk matched
	result.len = WINDOW_SIZE;
	search_index += WINDOW_SIZE;

	//check if rest of lookahead buffer
	//allow search buffer to go past the search limit to support overlapping
	size_t lookahead_index = search_end + WINDOW_SIZE;
	while (lookahead_index < lookahead_end
		&& buffer[search_index] == buffer[lookahead_index])
	{
		result.len++;
		search_index++;
		lookahead_index++;
	}

	result.index = search_index - result.len - WINDOW_SIZE;
	result.next_index = result.index + 1;

	return result;
}

FindResult findSequence(const char* buffer, size_t search_start, size_t search_end, size_t lookahead_end)
{
	FindResult result{ lookahead_end, 0, lookahead_end };

	//find occurence of first value
	size_t search_index = search_start;
	while (search_index < search_end 
		&& buffer[search_index] != buffer[search_end])
	{
		search_index++;
	}

	if (search_index == search_end)
	{
		return result;
	}

	//one value matched
	result.len = 1;
	search_index++;

	//check if rest of lookahead buffer
	//allow search buffer to go past the search limit to support overlapping
	size_t lookahead_index = search_end + 1;
	while (lookahead_index < lookahead_end
		&& buffer[search_index] == buffer[lookahead_index])
	{
		result.len++;
		search_index++;
		lookahead_index++;
	}
	
	result.index = search_index - result.len;
	result.next_index = result.index + 1;

	return result;
}

struct Code
{
	size_t index;
	size_t len;
	char unmatched;
};

Code computeCode(const char* buffer, size_t search_start, size_t search_end, size_t lookahead_end)
{
	FindResult findResult = findSequence(buffer, search_start, search_end, lookahead_end);
	if (findResult.len == 0)
	{
		return Code{ 0, 0, buffer[search_end] };
	}

	//find longest sequence with min index
	size_t max_sequence = findResult.len;
	size_t max_seq_index = findResult.index;

	while (findResult.next_index < lookahead_end)
	{
		findResult = findSequence(buffer, findResult.next_index, search_end, lookahead_end);
		if (max_sequence <= findResult.len)
		{
			max_sequence = findResult.len;
			max_seq_index = findResult.index;
		}
	}

	//convert absolute index to relative
	return Code{ search_end - max_seq_index , max_sequence, buffer[search_end + max_sequence]};
}

std::vector<Code> encode(const char* buffer, size_t search_start, size_t search_end, size_t lookahead_end)
{
	std::vector<Code> codes;
	//magic number to already reserve
	codes.reserve(1024);

	while (search_end < strlen(buffer) && search_end < 7)
	{
		Code code = computeCode(buffer, search_start, search_end, lookahead_end);
		search_end += code.len + 1;
		lookahead_end += code.len + 1;

		codes.push_back(std::move(code));
	}

	search_start = search_end - 7;

	while (search_end < strlen(buffer))
	{
		Code code = computeCode(buffer, search_start, search_end, lookahead_end);
		search_start += code.len + 1;
		search_end += code.len + 1;
		lookahead_end += code.len + 1;
		lookahead_end = std::min(lookahead_end, strlen(buffer));

		codes.push_back(std::move(code));
	}

	return codes;
}

void decode(char* buffer, size_t size, const std::vector<Code>& codes)
{
	(size);
	size_t cursor = 0;
	for (const auto& code : codes)
	{
		size_t len = code.len;
		if (len != 0)
		{
			//if it was overlapped copy in mulitple steps
			//each step is of relative index size
			while (len > code.index)
			{
				memcpy_s(buffer + cursor, size - cursor, buffer + (cursor - code.index), code.index);
				cursor += code.index;
				len -= code.index;
			}
			//copy remaining
			memcpy_s(buffer + cursor, size - cursor, buffer + (cursor - code.index), len);
			cursor += len;
		}

		buffer[cursor] = code.unmatched;
		
		cursor++;
	}
}