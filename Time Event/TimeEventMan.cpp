#include "TimeEventMan.h"
#include "TimeEvent.h"

TimeEventMan* TimeEventMan::pInstance = nullptr;

TimeEventMan::TimeEventMan(int reserveNum, int reserveGrow)
{
	this->BaseInitialize(reserveNum, reserveGrow);

	this->pNodeCompare = new TimeEvent();
	assert(this->pNodeCompare);

	this->GameTime.tic();
	this->mCurrentTime = this->GameTime.toc();
}

TimeEventMan::~TimeEventMan()
{
	delete this->pNodeCompare;

	Trace::out("---> ~TimeEventMan()\n");
}

void TimeEventMan::Create(int reserveNum, int reserveGrow)
{
	// initialize the singleton here
	assert(pInstance == nullptr);

	// Do the initialization
	if (pInstance == nullptr)
	{
		pInstance = new TimeEventMan(reserveNum, reserveGrow);
	}
}

void TimeEventMan::Destroy()
{
	Trace::out("\n");
	Trace::out("---- Destroy() ----\n");

	// Get the instance
	TimeEventMan* pMan = TimeEventMan::GetInstance();
	assert(pMan != nullptr);

	pMan->BaseDestroy();

	// kill the singleton
	delete pMan->pInstance;

}

TimeEvent* TimeEventMan::Add(Command* pCommand, Time deltaTimeToTrigger)
{
	TimeEventMan* pMan = TimeEventMan::GetInstance();
	assert(pMan != nullptr);

	TimeEvent* pNode = (TimeEvent*)pMan->BaseAdd();
	assert(pNode != nullptr);

	// Create a new one given a wash
	assert(pCommand);
	pNode->Set(pCommand, deltaTimeToTrigger);

	return pNode;
}



TimeEvent* TimeEventMan::Find(TimeEvent::ID event_id)
{
	TimeEventMan* pMan = TimeEventMan::GetInstance();
	assert(pMan != nullptr);

	pMan->pNodeCompare->SetID(event_id);

	TimeEvent* pData = (TimeEvent*)pMan->BaseFind(pMan->pNodeCompare);
	return pData;
}

Time TimeEventMan::GetTimeCurrent()
{
	TimeEventMan* pMan = TimeEventMan::GetInstance();
	assert(pMan != nullptr);

	return pMan->mCurrentTime;
}

void TimeEventMan::Remove(TimeEvent* pNode)
{
	TimeEventMan* pMan = TimeEventMan::GetInstance();
	assert(pMan != nullptr);

	assert(pNode != nullptr);
	pMan->BaseRemove(pNode);
}

void TimeEventMan::Dump()
{
	TimeEventMan* pMan = TimeEventMan::GetInstance();
	assert(pMan != nullptr);

	pMan->BaseDump();
}

void TimeEventMan::Update()
{
	TimeEventMan* pMan = TimeEventMan::GetInstance();
	assert(pMan != nullptr);

	pMan->mCurrentTime = pMan->GameTime.toc();

	TimeEvent* pEvent = (TimeEvent*)pMan->BaseGetActive();
	TimeEvent* pNextEvent = nullptr;

	while (pEvent != nullptr)
	{
		pNextEvent = (TimeEvent*)pEvent->pNext;

		if (pMan->mCurrentTime >= (pEvent->GetTriggerTime()))
		{
			// call it
			pEvent->Process();

			// remove from list
			pMan->BaseRemove(pEvent);
		}

		// advance the pointer
		pEvent = pNextEvent;
	}
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* TimeEventMan::DerivedCreateNode()
{
	DLink* pNode = new TimeEvent();
	assert(pNode != nullptr);

	return pNode;
}

bool TimeEventMan::DerivedCompare(DLink* pLinkA, DLink* pLinkB)
{
	assert(pLinkA != nullptr);
	assert(pLinkB != nullptr);

	TimeEvent* pDataA = (TimeEvent*)pLinkA;
	TimeEvent* pDataB = (TimeEvent*)pLinkB;

	bool status = false;

	if (pDataA->GetID() == pDataB->GetID())
	{
		status = true;
	}

	return status;
}

void TimeEventMan::DerivedWash(DLink* pLink)
{
	assert(pLink != nullptr);
	TimeEvent* pNode = (TimeEvent*)pLink;
	pNode->Wash();
}

void TimeEventMan::DerivedDumpNode(DLink* pLink)
{
	assert(pLink != nullptr);
	TimeEvent* pData = (TimeEvent*)pLink;
	pData->Dump();
}

void TimeEventMan::DerivedDestroyNode(DLink* pLink)
{
	assert(pLink);
	TimeEvent* pData = (TimeEvent*)pLink;
	delete pData;
}

TimeEventMan* TimeEventMan::GetInstance()
{
	// Safety - this forces users to call Create() first before using class
	assert(pInstance != nullptr);

	return pInstance;
}



