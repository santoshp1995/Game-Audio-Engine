#ifndef CIRCULAR_DATA_H
#define CIRCULAR_DATA_H

#include "CircularIndex.h"
#include "Command.h"
#include <mutex>

class CircularData
{
public:
	// needs to be a power of 2
	static const int CIRCULAR_DATA_SIZE = 128;

public:
	// big four
	CircularData();
	CircularData(const CircularData&) = delete;
	const CircularData& operator = (const CircularData&) = delete;
	~CircularData();

	bool PushBack(Command* p);
	bool PopFront(Command*& p);

private:
	Command* data[CIRCULAR_DATA_SIZE];

	CircularIndex front;
	CircularIndex back;
	bool empty;
	bool full;
	bool enable;
	std::mutex mtx;
};

#endif
