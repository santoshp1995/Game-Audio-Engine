#include "ASndMan.h"
ASndMan* ASndMan::pInstance = nullptr;


ASndMan::ASndMan(int reserveNum, int reserveGrow)
	: Manager()
{

	this->QuitFlag = false;

	this->BaseInitialize(reserveNum, reserveGrow);

	this->pNodeCompare = new ASnd();
	assert(this->pNodeCompare);
}

ASndMan::~ASndMan()
{
	assert(ASndMan::IsQuit() == true);
	
	delete this->pNodeCompare;

	Trace::out("---> ~ASndMan()\n");
}

void ASndMan::Create(int reserveNum, int reserveGrow)
{
	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(pInstance == nullptr);

	// do initilization
	if (pInstance == nullptr)
	{
		pInstance = new ASndMan(reserveNum, reserveGrow);
	}
}

void ASndMan::Destroy()
{
	Trace::out("\n");
	Trace::out("---- Destroy() ----\n");

	// Get the instance
	ASndMan* pMan = GetInstance();
	assert(pMan);

	pMan->BaseDestroy();

	// kill the singleton
	delete pMan->pInstance;
}

ASnd* ASndMan::Add(SndId snd_id)
{
	ASndMan* pMan = GetInstance();
	assert(pMan);

	ASnd* pNode = (ASnd*)pMan->BaseAdd();
	assert(pNode != nullptr);

	pNode->Set(snd_id);

	return pNode;
}

ASnd* ASndMan::Find(SndId snd_id)
{
	ASndMan* pMan = GetInstance();
	assert(pMan);

	pMan->pNodeCompare->SetSndID(snd_id);

	ASnd* pData = (ASnd*)pMan->BaseFind(pMan->pNodeCompare);

	return pData;
}

void ASndMan::Remove(ASnd* pNode)
{
	ASndMan* pMan = GetInstance();
	assert(pMan);

	assert(pNode != nullptr);

	pMan->BaseRemove(pNode);
}

void ASndMan::Dump()
{
	ASndMan* pMan = GetInstance();
	assert(pMan != nullptr);

	pMan->BaseDump();
}

void ASndMan::SetQuit()
{
	ASndMan* pMan = ASndMan::GetInstance();
	assert(pMan->pInstance);

	pMan->QuitFlag = true;
}

bool ASndMan::IsQuit()
{
	ASndMan* pMan = ASndMan::GetInstance();
	assert(pMan->pInstance);

	return pMan->QuitFlag;
}

DLink* ASndMan::DerivedCreateNode()
{
	DLink* pNode = new ASnd();
	assert(pNode != nullptr);

	return pNode;
}

bool ASndMan::DerivedCompare(DLink* pLinkA, DLink* pLinkB)
{
	assert(pLinkA != nullptr);
	assert(pLinkB != nullptr);

	ASnd* pDataA = (ASnd*)pLinkA;
	ASnd* pDataB = (ASnd*)pLinkB;

	bool status = false;

	SndId A;
	SndId B;

	pDataA->GetSndId(A);
	pDataB->GetSndId(B);

	if (A == B)
	{
		status = true;
	}

	return status;
}

void ASndMan::DerivedWash(DLink* pLink)
{
	assert(pLink != nullptr);
	ASnd* pNode = (ASnd*)pLink;
	pNode->Wash();
}

void ASndMan::DerivedDumpNode(DLink* pLink)
{
	assert(pLink != nullptr);
	ASnd* pData = (ASnd*)pLink;
	pData->Dump();
}

void ASndMan::DerivedDestroyNode(DLink* pLink)
{
	assert(pLink);
	ASnd* pData = (ASnd*)pLink;
	delete pData;
}

ASndMan* ASndMan::GetInstance()
{
	// Safety - this forces users to call Create() first before using class
	assert(pInstance != nullptr);

	return pInstance;
}













