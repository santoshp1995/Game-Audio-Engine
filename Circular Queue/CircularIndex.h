#ifndef CIRCULAR_INDEX_H
#define CIRCULAR_INDEX_H

class CircularIndex
{
public:
	// Big Four
	CircularIndex() = delete;
	CircularIndex(const CircularIndex&) = delete;
	const CircularIndex& operator = (const CircularIndex&) = delete;
	~CircularIndex() = default;

	// Specialized Constructor
	CircularIndex(int buffSize);

	// postfix
	int operator++(int);
	bool operator==(const CircularIndex& c);
	bool operator!=(const CircularIndex& c);

	int getIndex() const;

private:
	int index;
	int size;
	unsigned int mask;
};


#endif
