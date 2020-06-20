#include "WaveDataMan.h"

WaveDataMan* WaveDataMan::pInstance = nullptr;

WaveDataMan::WaveDataMan(int reserveNum, int reserveGrow) : Manager()
{
	// At this point manager is created, now initialize the reserve
	this->BaseInitialize(reserveNum, reserveGrow);

	// initialize the derived data here
	this->pNodeCompare = new WaveData();
	assert(this->pNodeCompare != nullptr);
}

WaveDataMan::~WaveDataMan()
{
	delete this->pNodeCompare;

	Trace::out("---> ~WaveMan()\n");
}

void WaveDataMan::Create(int reserveNum, int reserveGrow)
{
	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(pInstance == nullptr);

	if (pInstance == nullptr)
	{
		pInstance = new WaveDataMan(reserveNum, reserveGrow);
	}
}

void WaveDataMan::Destroy()
{
	Trace::out("\n");
	Trace::out("---- Destroy() ----\n");

	// get the instance
	WaveDataMan* pMan = GetInstance();
	assert(pMan != nullptr);

	pMan->BaseDestroy();

	// kill the singleton
	delete pMan->pInstance;
}

WaveData* WaveDataMan::Add(const char* const pFileName, WaveDataID id, FileUserCallback* pFileUserCB)
{
	WaveDataMan* pMan = GetInstance();
	assert(pMan != nullptr);

	WaveData* pNode = (WaveData*)pMan->BaseAdd();
	assert(pNode != nullptr);

	pNode->Set(pFileName, id, pFileUserCB);

	return pNode;
}

WaveData* WaveDataMan::Find(const WaveDataID id)
{
	WaveDataMan* pMan = GetInstance();
	assert(pMan != nullptr);

	pMan->pNodeCompare->SetID(id);

	WaveData* pData = (WaveData*)pMan->BaseFind(pMan->pNodeCompare);
	return pData;
}

void WaveDataMan::Remove(WaveData* pNode)
{
	WaveDataMan* pMan = GetInstance();
	assert(pMan != nullptr);

	assert(pNode != nullptr);
	pMan->BaseRemove(pNode);
}

void WaveDataMan::Dump()
{
	WaveDataMan* pMan = GetInstance();
	assert(pMan != nullptr);

	pMan->BaseDump();
}

DLink* WaveDataMan::DerivedCreateNode()
{
	DLink* pNode = new WaveData();
	assert(pNode != nullptr);

	return pNode;
}

bool WaveDataMan::DerivedCompare(DLink* pLinkA, DLink* pLinkB)
{
	assert(pLinkA != nullptr);
	assert(pLinkB != nullptr);

	WaveData* pDataA = (WaveData*)pLinkA;
	WaveData* pDataB = (WaveData*)pLinkB;

	bool status = false;

	WaveDataID A;
	WaveDataID B;

	pDataA->GetWaveID(A);
	(pDataB->GetWaveID(B));

	if (A == B)
	{
		status = true;
	}

	return status;
}

void WaveDataMan::DerivedWash(DLink* pLink)
{
	assert(pLink != nullptr);
	WaveData* pNode = (WaveData*)pLink;
	pNode->Wash();
}

void WaveDataMan::DerivedDumpNode(DLink* pLink)
{
	assert(pLink != nullptr);
	WaveData* pData = (WaveData*)pLink;
	pData->Dump();
}

void WaveDataMan::DerivedDestroyNode(DLink* pLink)
{
	assert(pLink);
	WaveData* pData = (WaveData*)pLink;
	delete pData;
}

WaveDataMan* WaveDataMan::GetInstance()
{
	// Safety - this forces users to call Create() first before using class
	assert(pInstance != nullptr);

	return pInstance;
}









