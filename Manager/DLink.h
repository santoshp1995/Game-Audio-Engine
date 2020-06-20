#ifndef DLINK_H
#define DLINK_H

class DLink
{
protected:
	// big four
	DLink();
	DLink(const DLink&) = delete;
	DLink& operator = (const DLink&) = delete;
	virtual ~DLink();

public:
	void Clear();

	// methods with head pointer
	static void AddToFront(DLink*& pHead, DLink* pNode);
	static DLink* PopFromFront(DLink*& pHead);
	static void RemoveNode(DLink*& pHead, DLink* pNode);

	// methods with head and tail pointers
	static void AddToLast(DLink*& pHead, DLink*& pTail, DLink* pNode);
	static void RemoveNode(DLink*& pHead, DLink*& pTail, DLink* pNode);

	// TODO -- Make Private
	DLink* pNext;
	DLink* pPrev;
};

#endif DLINK_H
