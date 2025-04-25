#pragma once

#include <string>

class SlidingWindow
{
private:
	const std::string& str;
	size_t m_offset;
	const size_t size;

public:
	SlidingWindow(const std::string& str, const size_t size)
		:str{str},
		m_offset{0},
		size{size}
	{}

	void moveFront(size_t offset)
	{
		size_t next_offset = m_offset + offset;
		if (next_offset >= str.length())
		{
			m_offset = str.length() - 1;
		}
		else
		{
			m_offset = next_offset;
		}
	}

	void moveBack(size_t offset)
	{
		size_t next_offset = m_offset - offset;
		if (next_offset >= str.length())
		{
			m_offset = 0;
		}
		else
		{
			m_offset = next_offset;
		}
	}

	char at(size_t index)
	{
		return str.at(m_offset + index);
	}

	std::string slice()
	{
		return str.substr(m_offset, size);
	}

	//implement iterators
	struct Iterator
	{
	private:
		const SlidingWindow& window;
		size_t index;

	public:
		Iterator(const SlidingWindow& window, size_t index)
			:window{window},
			index{index}
		{}

		Iterator(const Iterator& other)
			:window{other.window},
			index{other.index}
		{}

		Iterator operator++(int)
		{
			return { window, index + 1 };
		}

		char operator*() const
		{
			return window.str[index];
		}

		//pointer operator->() const;

		friend bool operator==(const Iterator& it1, const Iterator& it2)
		{
			return it1.index == it2.index;
		}

		friend bool operator!=(const Iterator& it1, const Iterator& it2)
		{
			return it1.index != it2.index;
		}
	};

	Iterator begin()
	{
		return { *this, m_offset};
	}

	Iterator end()
	{
		return { *this, std::min(str.length(), m_offset+size)};
	}
};