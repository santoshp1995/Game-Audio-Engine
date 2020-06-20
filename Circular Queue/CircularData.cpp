#include "CircularData.h"
#include "ASndMan.h"


CircularData::CircularData()
	: front(CIRCULAR_DATA_SIZE),
	back(CIRCULAR_DATA_SIZE),
	empty(true),
	full(false),
	enable(true)
{
	// initialized data
	for (int i = 0; i < CIRCULAR_DATA_SIZE; i++)
	{
		this->data[i] = 0;
	}
}

CircularData::~CircularData()
{
	Command* pCommand = nullptr;

	while (this->PopFront(pCommand) == true)
	{
		assert(pCommand);
		//delete pCommand;
	}
}

bool CircularData::PushBack(Command* val)
{
	bool status = false;

	std::lock_guard<std::mutex> lock(this->mtx);

	// do we have space to add?
	if (this->front != this->back || this->empty)
	{
		// add data
		this->data[this->back.getIndex()] = val;
		this->back++;

		this->empty = false;

		// check if this add made it full
		if (this->front == this->back)
		{
			this->full = true;
		}

		status = true;
	}

	else
	{
		status = false;
	}

	return status;
}

bool CircularData::PopFront(Command*& val)
{
	bool status = false;

	std::lock_guard<std::mutex> lock(this->mtx);

	// is there data to process
	if (this->front != this->back || this->full)
	{
		// grab one
		val = this->data[this->front.getIndex()];
		this->front++;

		this->full = false;

		// check if this pop made it empty
		if (this->front == this->back)
		{
			this->empty = true;
		}

		status = true;
	}

	else
	{
		status = false;
	}

	return status;
}





