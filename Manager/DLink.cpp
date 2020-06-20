#include "DLink.h"

DLink::DLink()
{
	this->Clear();
}

DLink::~DLink()
{
	// Safety
	this->Clear();

	Trace::out("           ~DLink(%p) \n", this);
}

void DLink::Clear()
{
	this->pNext = nullptr;
	this->pPrev = nullptr;
}

void DLink::AddToFront(DLink*& pHead, DLink* pNode)
{
	// Will Work for active or reserve lists

	// check pointer is valid
	assert(pNode != nullptr);

	// add node
	// is head null?
	if (pHead == nullptr)
	{
		// push to front
		pHead = pNode;
		pNode->pNext = nullptr;
		pNode->pPrev = nullptr;
	}

	// head already exists
	else
	{
		// push to front
		pNode->pPrev = nullptr;
		pNode->pNext = pHead;

		pHead->pPrev = pNode;
		pHead = pNode;
	}
	assert(pHead != nullptr);
}

void DLink::AddToLast(DLink*& pHead, DLink*& pTail, DLink* pNode)
{
	// Will work for Active or Reserve List

	assert(pNode != nullptr);

	// add node
	if (pTail == pHead && pHead == nullptr)
	{
		pHead = pNode;
		pTail = pNode;
		pNode->pNext = nullptr;
		pNode->pPrev = nullptr;
	}
	else
	{
		assert(pTail != nullptr);

		//add to end
		pTail->pNext = pNode;
		pNode->pPrev = pTail;
		pNode->pNext = nullptr;

		pTail = pNode;
	}

	assert(pHead != nullptr);
	assert(pTail != nullptr);

}

DLink* DLink::PopFromFront(DLink*& pHead)
{
	// There should always be something on list
	assert(pHead != nullptr);

	DLink* pNode = pHead;

	pHead = pHead->pNext;

	if (pHead != nullptr)
	{
		pHead->pPrev = nullptr;
	}

	pNode->Clear();

	return pNode;

}

void DLink::RemoveNode(DLink*& pHead, DLink* pNode)
{
	// protection
	assert(pNode != nullptr);

	// 4 different conditions... 
	if (pNode->pPrev != nullptr)
	{	
		// middle or last node
		pNode->pPrev->pNext = pNode->pNext;
	}
	else
	{  
		// first
		pHead = pNode->pNext;
	}

	if (pNode->pNext != nullptr)
	{	
		// middle node
		pNode->pNext->pPrev = pNode->pPrev;
	}
}

void DLink::RemoveNode(DLink*& pHead, DLink*& pTail, DLink* pNode)
{
	// protection
	assert(pNode != nullptr);

	if (pNode->pPrev != nullptr)
	{	
		// middle or last node
		pNode->pPrev->pNext = pNode->pNext;

		if (pNode == pTail)
		{
			pTail = pNode->pPrev;
		}
	}
	else
	{  
		// first
		pHead = pNode->pNext;

		if (pNode == pTail)
		{
			// Only one node
			pTail = pNode->pNext;
		}
		else
		{
			// Only first not the last
			// do nothing more
		}
	}

	if (pNode->pNext != nullptr)
	{	
		// middle node
		pNode->pNext->pPrev = pNode->pPrev;
	}
}








