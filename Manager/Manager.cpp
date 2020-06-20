#include "Manager.h"

Manager::Manager()
{
	this->mDeltaGrow = 0;
	this->mNumReserved = 0;
	this->mInitialNumReserved = 0;
	this->mNumActive = 0;
	this->mTotalNumNodes = 0;
	this->pActive = nullptr;
	this->pReserve = nullptr;
}

Manager::~Manager()
{
	// This function does our work!
	//      Derived class should have called this... but just in case
	this->BaseDestroy();

	assert(this->pActive == nullptr);
	assert(this->pReserve == nullptr);

	Trace::out("---> ~Manager()\n");
}


void Manager::BaseInitialize(int InitialNumReserved, int DeltaGrow)
{
	assert(InitialNumReserved >= 0);
	assert(DeltaGrow > 0);

	this->mDeltaGrow = DeltaGrow;
	this->mInitialNumReserved = InitialNumReserved;

	// preload the reserve
	this->FillReservedPool(InitialNumReserved);
}

void Manager::BaseSetReserve(int reserveNum, int reserveGrow)
{
	this->mDeltaGrow = reserveGrow;

	if (reserveNum > this->mNumReserved)
	{
		// preload the reserve
		this->FillReservedPool(reserveNum - this->mNumReserved);
	}
}

DLink* Manager::BaseAdd()
{
	// are there any nodes on the reserve list?
	if (this->pReserve == nullptr)
	{
		// refill the reserve list with delta grow
		this->FillReservedPool(this->mDeltaGrow);
	}

	// Always take from the reserved list
	DLink* pLink = DLink::PopFromFront(this->pReserve);

	assert(pLink != nullptr);

	// wash it
	this->DerivedWash(pLink);

	// update stats
	this->mNumActive++;
	this->mNumReserved--;

	// copy to active
	DLink::AddToFront(this->pActive, pLink);

	return pLink;
}

DLink* Manager::BaseFind(DLink* pNodeTarget)
{
	assert(pNodeTarget != nullptr);

	// search the active list
	DLink* pLink = this->pActive;

	// walk through the nodes
	while (pLink != nullptr)
	{
		if (this->DerivedCompare(pLink, pNodeTarget))
		{
			// found it
			break;
		}

		pLink = pLink->pNext;
	}

	return pLink;
}

void Manager::BaseRemove(DLink* pNode)
{
	assert(pNode != nullptr);

	DLink::RemoveNode(this->pActive, pNode);

	// wash node before returning to reserved list
	this->DerivedWash(pNode);

	// add to reserve list
	DLink::AddToFront(this->pReserve, pNode);

	// update stats
	this->mNumActive--;
	this->mNumReserved++;

}


DLink* Manager::BaseGetActive()
{
	return this->pActive;
}

void Manager::BaseDestroy()
{
	// search for the node
	DLink* pNode;
	DLink* pTmpNode;


	pNode = this->pActive;

	while (pNode != nullptr)
	{
		// walk through the list
		pTmpNode = pNode;
		pNode = pNode->pNext;

		// node to cleanup
		assert(pTmpNode != nullptr);

		DLink::RemoveNode(this->pActive, pTmpNode);

		this->DerivedDestroyNode(pTmpNode);
		pTmpNode = nullptr;

		// update stats
		this->mNumActive--;
		this->mTotalNumNodes--;
	}

	// reserve list
	pNode = this->pReserve;

	while (pNode != nullptr)
	{
		// walk the list
		pTmpNode = pNode;
		pNode = pNode->pNext;

		// node to cleanup
		assert(pTmpNode != nullptr);

		DLink::RemoveNode(this->pReserve, pTmpNode);

		this->DerivedDestroyNode(pTmpNode);
		pTmpNode = nullptr;

		// update stats
		this->mNumReserved--;
		this->mTotalNumNodes--;
	}
}

void Manager::BaseDump()
{
	this->BaseDumpStats();
	this->BaseDumpNodes();
}

void Manager::BaseDumpNodes()
{
	Trace::out("\n");
	Trace::out("------ Active List: ---------------------------\n");

	DLink* pNode = this->pActive;
	int i;

	if (pNode == nullptr)
	{
		Trace::out("  <list empty>\n");
	}
	else
	{
		i = 0;
		while (pNode != nullptr)
		{
			Trace::out("%d: -------------\n", i);
			this->DerivedDumpNode(pNode);
			i++;
			pNode = pNode->pNext;
		}
	}
	Trace::out("\n");
	Trace::out("------ Reserve List: ---------------------------\n");

	pNode = this->pReserve;

	if (pNode == nullptr)
	{
		Trace::out("  <list empty>\n");
	}
	else
	{
		i = 0;
		while (pNode != nullptr)
		{
			Trace::out("%d: -------------\n", i);
			this->DerivedDumpNode(pNode);
			i++;
			pNode = pNode->pNext;
		}
	}
}

void Manager::BaseDumpStats()
{
	Trace::out("\n");
	Trace::out("\n");
	Trace::out("-------- Stats: -------------\n");
	Trace::out("  Total Num Nodes: %d\n", this->mTotalNumNodes);
	Trace::out("       Num Active: %d\n", this->mNumActive);
	Trace::out("     Num Reserved: %d\n", this->mNumReserved);
	Trace::out("       Delta Grow: %d\n", this->mDeltaGrow);
}

void Manager::FillReservedPool(int count)
{
	// doesn't make sense if its not at least 1
	assert(count > 0);

	this->mTotalNumNodes += count;
	this->mNumReserved += count;

	// Preload the reserve
	for (int i = 0; i < count; i++)
	{
		DLink* pNode = this->DerivedCreateNode();
		assert(pNode != nullptr);

		DLink::AddToFront(this->pReserve, pNode);
	}
}








