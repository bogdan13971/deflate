#pragma once

#include <deque>
#include <iterator>
#include <algorithm>
#include <unordered_map>

class CircularBuffer
{
protected:
	size_t max_size;

public:
	CircularBuffer(size_t max_size)
		:max_size{ max_size }
	{};


	virtual ~CircularBuffer()
	{}

	virtual void push(int element) = 0;
	virtual int pop() = 0;
	virtual int at(size_t index) const = 0;
	virtual size_t size() const = 0;
};

class QueueCircularBuffer : public CircularBuffer
{
private:
	std::deque<int> buffer;

public:
	QueueCircularBuffer(size_t max_size)
		:CircularBuffer{max_size}
	{}

	void push(int element) override
	{
		if (buffer.size() == max_size)
		{
			buffer.pop_front();
		}

		buffer.push_back(element);
	}

	int pop() override
	{
		int temp = buffer.front();
		buffer.pop_front();

		return temp;
	}

	int at(size_t index) const override
	{
		return buffer.at(index);
	}

	size_t size() const override
	{
		return buffer.size();
	}
};

class ArrayCircularBuffer : public CircularBuffer
{
private:
	int* array;
	size_t start;
	size_t end;
	bool isEmpty;

public:
	ArrayCircularBuffer(size_t max_size)
		:CircularBuffer{max_size},
		array{nullptr},
		start{0},
		end{0},
		isEmpty{true}
	{
		array = new int[max_size];
	}

	~ArrayCircularBuffer()
	{
		delete array;
	}

	void push(int element) override
	{
		if (!isEmpty && end % max_size == start)
		{
			start = (start + 1) % max_size;
		}

		array[end] = element;
		end = (end + 1) % max_size;

		isEmpty = false;
	}

	int pop() override
	{
		int temp = array[start];
		start = (start + 1) % max_size;

		if (start == end)
		{
			isEmpty = true;
		}

		return temp;
	}

	int at(size_t index) const override
	{
		return array[(index + start) % max_size];
	}

	size_t size() const override
	{
		if (isEmpty)
		{
			return 0;
		}

		if (start < end)
		{
			return end - start;
		}

		return max_size - start + end;
	}
};

class LinkedArrayCircularBuffer : public CircularBuffer
{
private:
	struct Node
	{
		uint16_t next;
		int value;
	};

	const uint16_t MAX_INDEX;

	Node* array;
	uint16_t head;
	uint16_t tail;
	bool isEmpty;

public:
	LinkedArrayCircularBuffer(size_t max_size)
		:CircularBuffer{ max_size },
		MAX_INDEX{ static_cast<uint16_t>(max_size) },
		array{nullptr},
		head{ MAX_INDEX },
		tail{ MAX_INDEX },
		isEmpty{true}
	{
		array = new Node[max_size];
		std::for_each(array, array + max_size, [max_index = MAX_INDEX](auto& node) {node.value = -1; node.next = max_index; });
	};

	~LinkedArrayCircularBuffer()
	{
		delete array;
	}

	void push(int element)
	{
		uint16_t index = MAX_INDEX;

		if (isEmpty)
		{
			head = 0;
			tail = 0;
			index = 0;
		}
		else
		{
			index = (tail + 1) % max_size;
			array[tail].next = index;

			if (index == head)
			{
				head = (head + 1) % max_size;
			}
		}

		array[index].value = element;
		array[index].next = MAX_INDEX;
		tail = index;

		isEmpty = false;
	}

	int pop()
	{
		int temp = array[head].value;
		head = (head + 1) % max_size;

		return temp;
	}

	int at(size_t index) const override
	{
		return array[(index + head) % max_size].value;
	}

	size_t size() const override
	{
		if (isEmpty)
		{
			return 0;
		}

		if (head < tail)
		{
			return static_cast<size_t>(tail - head + 1);
		}

		return static_cast<size_t>(max_size - head + tail + 1);
	}
};