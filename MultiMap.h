#pragma once

#include <unordered_map>
#include <array>
#include <utility>
#include <iostream>

template<class V, size_t MAX_SIZE>
class MultiMap
{
private:
	static constexpr float SUPPOSED_DISTINCT_PERCENTAGE = 0.3f;

	struct Node
	{
		size_t indexOfValue;
		size_t next;
	};

	struct HeadTail
	{
		size_t head;
		size_t tail;
	};

	std::unordered_map<V, HeadTail> keyToHeadTailMap;
	std::array<Node, MAX_SIZE> nodeArray;

public:
	void preprocess(const V* values, size_t start, size_t end)
	{
		//count unique values
		std::unordered_map<V, size_t> uniqueValues;
		for (size_t i = start; i < end; i++)
		{
			uniqueValues[values[i]] = uniqueValues[values[i]] + 1;
		}

		//reserve distinct map based on unique values
		keyToHeadTailMap.reserve(uniqueValues.size());

		//add head index for each unique key
		size_t lastIndex = 0;
		for (const auto& keyVal : uniqueValues)
		{
			HeadTail headTail{ lastIndex, MAX_SIZE };
			keyToHeadTailMap.insert(std::make_pair(keyVal.first, std::move(headTail)));
			lastIndex = lastIndex + keyVal.second;
		}

		//free up some space
		uniqueValues.clear();

		//add each item into the corresponding bucket
		for (size_t i = start; i < end; i++)
		{
			//insert at tail in each bucket
			const auto headTail = keyToHeadTailMap.at(values[i]);
			size_t head = headTail.head;
			size_t tail = headTail.tail;
			
			//empty bucket case
			if (tail == MAX_SIZE)
			{
				nodeArray[head].indexOfValue = i;
				nodeArray[head].next = MAX_SIZE;
				tail = head;
			}
			//add at tail
			//SHOULD NOT overlap with next bucket because of previous preprocessing
			else
			{
				nodeArray[tail].next = tail + 1;
				nodeArray[tail + 1].indexOfValue = i;
				nodeArray[tail + 1].next = MAX_SIZE;
				tail += 1;
			}

			keyToHeadTailMap.at(values[i]).tail = tail;
		}
	}

	//print all values for each item
	void print()
	{
		for (const auto& keyToHeadTail : keyToHeadTailMap)
		{
			const HeadTail& headTail = keyToHeadTail.second;
			std::cout << keyToHeadTail.first << " : ";

			size_t index = headTail.head;
			while (index != MAX_SIZE)
			{
				std::cout << nodeArray[index].indexOfValue << ", ";
				index = nodeArray[index].next;
			}

			std::cout << "\n";
		}
	}

	//remove first value of key1 while adding new value to key2
	void roll(const V* values, size_t ejectionPos, size_t pos)
	{
		//removing first key is done by moving head to next value
		V oldKey = values[ejectionPos];
		const HeadTail& headTail = keyToHeadTailMap.at(oldKey);

		size_t emptyIndex = headTail.head;
		size_t newHead = nodeArray[headTail.head].next;

		//update new head
		keyToHeadTailMap.at(oldKey).head = newHead;

		//update value in place for deleted node
		nodeArray[emptyIndex].indexOfValue = pos;
		nodeArray[emptyIndex].next = MAX_SIZE;

		//add new value on the same node
		const auto it = keyToHeadTailMap.find(values[pos]);
		if (it == keyToHeadTailMap.end())
		{
			//add new head-tail for new key
			keyToHeadTailMap.insert(it, std::make_pair(values[pos], HeadTail{ emptyIndex, MAX_SIZE}));
		}
		else
		{
			//link last node of key to his one
			size_t tail = it->second.tail;
			nodeArray[tail].next = emptyIndex;
		}
	}

	//longest common subsequence
	size_t getLCS(const V* values, size_t ejectPos, size_t start, size_t end)
	{
		V key = values[start];
		//roll if key not found and return 0
		const auto it = keyToHeadTailMap.find(key);
		if (it == keyToHeadTailMap.end())
		{
			roll(values, ejectPos, start);
			return 0;
		}

		const HeadTail& headTail = it->second;
		//iterate each value and test with rest of pin
		size_t index = headTail.head;
		size_t maxLcs{0};
		//can be put in an array and paralleise it
		while (index != MAX_SIZE)
		{
			size_t indexOfValue = nodeArray[index].indexOfValue;

			size_t lcs = 0;
			size_t pinIndex = start;
			//remove second to enable overlapping
			while (pinIndex < end && indexOfValue < start && values[indexOfValue] == values[pinIndex])
			{
				lcs++;
				pinIndex++;
				indexOfValue++;
			}

			maxLcs = std::max(maxLcs, lcs);

			index = nodeArray[index].next;
		}

		return maxLcs;
	}
};