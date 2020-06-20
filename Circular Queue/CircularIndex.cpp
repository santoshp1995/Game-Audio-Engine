#include "CircularIndex.h"

CircularIndex::CircularIndex(int buffSize)
{
	this->size = buffSize;
	this->mask = buffSize - 1;
	this->index = 0;
}

// postfix
int CircularIndex::operator++(int)
{
	this->index++;

	// circular
	this->index = this->index & this->mask;

	return this->index;
}

bool CircularIndex::operator==(const CircularIndex& c)
{
	assert(this->size == c.size);

	return (this->index == c.index);
}

bool CircularIndex::operator!=(const CircularIndex& c)
{
	assert(this->size == c.size);

	return (this->index != c.index);
}

int CircularIndex::getIndex() const
{
	return this->index;
}
