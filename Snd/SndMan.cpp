#include "SndMan.h"
#include "CreateSndCommand.h"
#include "Timer.h"
#include "QuitCommand.h"

SndMan* SndMan::pInstance = nullptr;

SndMan::SndMan(int reserveNum, int reserveGrow)
{
	this->BaseInitialize(reserveNum, reserveGrow);

	this->pNodeCompare = new Snd();
	assert(this->pNodeCompare);

	this->pAudioInQueue = new CircularData();
	assert(this->pAudioInQueue);

	this->pGameInQueue = new CircularData();
	assert(this->pGameInQueue);


}

SndMan::~SndMan()
{
	delete this->pNodeCompare;

	delete this->pAudioInQueue;
	delete this->pGameInQueue;

	Trace::out("---> ~ASndMan()\n");
}

void SndMan::Create(int reserveNum, int reserveGrow)
{
	// initialize the singleton
	assert(pInstance == nullptr);

	if (pInstance == nullptr)
	{
		pInstance = new SndMan(reserveNum, reserveGrow);
	}
}

void SndMan::Destroy()
{
	Trace::out("\n");
	Trace::out("---- Destroy() ----\n");

	// Get the instance
	SndMan* pMan = SndMan::GetInstance();
	assert(pMan != nullptr);

	pMan->BaseDestroy();

	// kill the singleton
	delete pMan->pInstance;
}

Snd* SndMan::Add(SndId snd_id, UserCallback* pCallback, SndPriority snd_priority)
{
	SndMan* pMan = SndMan::GetInstance();
	assert(pMan);

	Snd* pNode = (Snd*)pMan->BaseAdd();
	assert(pNode != nullptr);

	// create a new one given a wash
	pNode->Set(snd_id, snd_priority);

	CircularData* pOut = SndMan::GetAudioInQueue();
	assert(pOut);

	Command* pCreateCommand = new CreateSndCommand(snd_id, pNode, pCallback);
	assert(pCreateCommand);

	// push command to queue
	pOut->PushBack(pCreateCommand);

	return pNode;

}

Snd* SndMan::Find(SndId snd_id)
{
	SndMan* pMan = SndMan::GetInstance();
	assert(pMan);

	pMan->pNodeCompare->SetID(snd_id);

	Snd* pData = (Snd*)pMan->BaseFind(pMan->pNodeCompare);

	return pData;
}

void SndMan::Remove(Snd* pNode)
{
	SndMan* pMan = SndMan::GetInstance();
	assert(pMan);

	assert(pNode);
	pMan->BaseRemove(pNode);
}

void SndMan::Dump()
{
	SndMan* pMan = SndMan::GetInstance();
	assert(pMan != nullptr);

	pMan->BaseDump();
}

void SndMan::Quit(SndId snd_id)
{
	SndMan* pMan = SndMan::GetInstance();
	assert(pMan != nullptr);

	Snd* pNode = (Snd*)pMan->BaseAdd();
	assert(pNode != nullptr);

	pNode->Set(snd_id, 0);

	// Now create a the sound call on the Audio thread
	CircularData* pOut = SndMan::GetAudioInQueue();
	assert(pOut);

	Command* pCommand = new QuitCommand(snd_id, pNode);
	assert(pCommand);

	// push command to queue
	pOut->PushBack(pCommand);


}

CircularData* SndMan::GetAudioInQueue()
{
	SndMan* pMan = SndMan::GetInstance();
	assert(pMan);

	return pMan->pAudioInQueue;
}

CircularData* SndMan::GetGameInQueue()
{
	SndMan* pMan = SndMan::GetInstance();
	assert(pMan);

	return pMan->pGameInQueue;
}

DLink* SndMan::DerivedCreateNode()
{
	DLink* pNode = new Snd();
	assert(pNode != nullptr);

	return pNode;
}

bool SndMan::DerivedCompare(DLink* pLinkA, DLink* pLinkB)
{
	// This is used in baseFind() 
	assert(pLinkA != nullptr);
	assert(pLinkB != nullptr);

	Snd* pDataA = (Snd*)pLinkA;
	Snd* pDataB = (Snd*)pLinkB;

	bool status = false;
	SndId A_id;
	SndId B_id;

	pDataA->GetID(A_id);
	pDataB->GetID(B_id);

	if (A_id == B_id)
	{
		status = true;
	}

	return status;
}

void SndMan::DerivedWash(DLink* pLink)
{
	assert(pLink != nullptr);
	Snd* pNode = (Snd*)pLink;
	pNode->Wash();
}

void SndMan::DerivedDumpNode(DLink* pLink)
{
	assert(pLink != nullptr);
	Snd* pData = (Snd*)pLink;
	pData->Dump();
}

void SndMan::DerivedDestroyNode(DLink* pLink)
{
	assert(pLink);
	Snd* pData = (Snd*)pLink;
	delete pData;
}

SndMan* SndMan::GetInstance()
{
	// Safety - this forces users to call Create() first before using class
	assert(pInstance != nullptr);

	return pInstance;
}





