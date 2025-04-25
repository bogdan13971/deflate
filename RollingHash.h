#pragma once

#include <cstdint>

template<size_t N, uint16_t BASE, uint32_t MODULUS>
class Powers
{
private:
	uint32_t POWERS[N + 1];

public:
	constexpr Powers()
		:POWERS{}
	{
		POWERS[0] = 1;
		for (size_t i = 1; i <= N; i++)
		{
			POWERS[i] = (POWERS[i - 1] * BASE) % MODULUS;
		}
	}

	constexpr uint32_t at(size_t i) const
	{
		return POWERS[i];
	}
};

template<size_t N, size_t WINDOW_SIZE, uint16_t BASE = 26, uint32_t MODULUS = 1000000007>
class RollingHash
{
private:
	uint32_t hash{};
	static constexpr Powers<N, BASE, MODULUS> pows;

public:
	constexpr RollingHash()
	{}
	
	constexpr void initialize(const char* buffer, size_t window_start)
	{
		for (size_t i = window_start; i < window_start + WINDOW_SIZE; i++)
		{
			hash = (hash * BASE + buffer[i]) % MODULUS;
		}
	}

	uint32_t getHash() const
	{
		return hash;
	}

	//remove first character and add next one
	void roll(const char* buffer, size_t new_window_start)
	{
		if (new_window_start + WINDOW_SIZE >= N)
		{
			throw std::runtime_error{"Rolling hash index of window is out of bounds"};
		}

		char first_char = buffer[new_window_start - 1];
		hash = (hash - pows.at(WINDOW_SIZE - 1) * first_char) % MODULUS;

		char new_char = buffer[new_window_start + WINDOW_SIZE - 1];
		hash = (hash * BASE + new_char) % MODULUS;
	}
};
