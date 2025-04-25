#include <cassert>
#include <iostream>
#include <string>

#include "CircularBuffer.h"
#include "SlidingWindow.h"
#include "Encoder.h"
#include "MultiMap.h"
#include <cmath>
#include "EncodeTest.h"

#include "RollingHash.h"

void test1(CircularBuffer* circ)
{
	assert(circ->size() == 0);

	circ->push(0);
	circ->push(1);

	assert(circ->size() == 2);

	circ->push(2);
	circ->push(3);

	assert(circ->size() == 4);

	assert(circ->at(0) == 0);
	assert(circ->at(1) == 1);

	assert(circ->at(2) == 2);
	assert(circ->at(3) == 3);

	circ->push(4);
	circ->push(5);

	assert(circ->size() == 4);

	assert(circ->at(0) == 2);
	assert(circ->at(1) == 3);
	assert(circ->at(2) == 4);
	assert(circ->at(3) == 5);

	assert(circ->pop() == 2);
	assert(circ->pop() == 3);

	assert(circ->size() == 2);

	circ->push(6);

	assert(circ->size() == 3);

	assert(circ->at(0) == 4);
	assert(circ->at(1) == 5);
	assert(circ->at(2) == 6);
}

void test2(const std::string& str)
{
	SlidingWindow sw{ str, 4 };

	assert(sw.at(0) == 'A');
	assert(sw.at(1) == 'B');
	assert(sw.at(2) == 'C');
	assert(sw.at(3) == 'D');

	sw.moveFront(3);

	assert(sw.at(0) == 'D');
	assert(sw.at(1) == 'E');
	assert(sw.at(2) == 'F');
	assert(sw.at(3) == 'G');

	assert(sw.slice() == std::string{"DEFG"});

	sw.moveBack(1);

	assert(sw.at(0) == 'C');
	assert(sw.at(1) == 'D');
	assert(sw.at(2) == 'E');
	assert(sw.at(3) == 'F');

	assert(sw.slice() == std::string{"CDEF"});

	sw.moveBack(10);

	assert(sw.at(0) == 'A');
	assert(sw.at(1) == 'B');
	assert(sw.at(2) == 'C');
	assert(sw.at(3) == 'D');

	assert(sw.slice() == std::string{"ABCD"});

	sw.moveFront(100);

	assert(sw.at(0) == 'J');

	assert(sw.slice() == std::string{"J"});
}

void test_roll()
{
	RollingHash<10, 4, 2, 1000> rh{};

	const char* buffer = "BACAB";
	rh.initialize(buffer, 0);

	assert(rh.getHash() == 987);

	rh.roll(buffer, 1);
	
	assert(rh.getHash() == 984);
}

int main()
{
	//encode_all_tests();

	//test_roll();

	constexpr RollingHash<10, 4, 2, 1000> rh{};
	rh.initialize("ABCD", 0);

	return 0;
}