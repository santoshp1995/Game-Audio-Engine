#ifndef MANAGER_H
#define MANAGER_H

#include "DLink.h"

class Manager
{
public:
	DLink* BaseGetActive();

protected:
	// Big Four
	Manager();
	Manager(const Manager&) = delete;
	Manager& operator = (const Manager&) = delete;
	virtual ~Manager();

	void BaseInitialize(int InitialNumReserved = 3, int DeltaGrow = 1);

	void BaseSetReserve(int reserveNum, int reserveGrow);
	DLink* BaseAdd();
	DLink* BaseFind(DLink* pNodeTarget);
	void BaseRemove(DLink* pNode);
	void BaseDestroy();
	void BaseDump();
	void BaseDumpNodes();
	void BaseDumpStats();

	// abstract methods
	virtual DLink* DerivedCreateNode() = 0;
	virtual bool DerivedCompare(DLink* pLinkA, DLink* pLinkB) = 0;
	virtual void DerivedWash(DLink* pLink) = 0;
	virtual void DerivedDumpNode(DLink* pLink) = 0;
	virtual void DerivedDestroyNode(DLink* pLink) = 0;

private:
	// helper functions
	void FillReservedPool(int count);

private:
	DLink* pActive;
	DLink* pReserve;

	int mDeltaGrow;
	int mTotalNumNodes;
	int mNumReserved;
	int mInitialNumReserved;
	int mNumActive;

};


#endif