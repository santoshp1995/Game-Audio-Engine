#include "VoiceMan.h"
#include "WaveDataMan.h"


VoiceMan* VoiceMan::pInstance = nullptr;

VoiceMan::VoiceMan(int reserveNum, int reserveGrow) : Manager()
{
	// at this point Voice Man is created sooo...
	// initialize the reserve
	this->BaseInitialize(reserveNum, reserveGrow);

	// initialize the derived data
	this->pNodeCompare = new Voice();
	assert(this->pNodeCompare != nullptr);
}

VoiceMan::~VoiceMan()
{
	delete this->pNodeCompare;

	Trace::out("---> ~VoiceMan()\n");
}

void VoiceMan::Create(int reserveNum, int reserveGrow)
{
	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(pInstance == nullptr);

	// Do the Initilization
	if (pInstance == nullptr)
	{
		pInstance = new VoiceMan(reserveNum, reserveGrow);
	}
}

void VoiceMan::Destroy()
{
	Trace::out("\n");
	Trace::out("---- Destroy() ----\n");

	// Get the instance
	VoiceMan* pMan = GetInstance();
	assert(pMan != nullptr);

	pMan->BaseDestroy();

	// kill the singleton
	delete pInstance;
}

Voice* VoiceMan::Add(VoiceID voice_id, WaveDataID wave_id)
{
	VoiceMan* pMan = GetInstance();
	assert(pMan);

	WaveData* pWave = WaveDataMan::Find(wave_id);
	assert(pWave);

	Voice* pVoice = (Voice*)pMan->BaseAdd();
	assert(pVoice != nullptr);

	pVoice->Set(voice_id, pWave);

	return pVoice;
}

Voice* VoiceMan::Add(VoiceID voice_id, WaveDataID wave_id, IXAudio2VoiceCallback* pCallback)
{
	VoiceMan* pMan = GetInstance();
	assert(pMan);

	WaveData* pWave = WaveDataMan::Find(wave_id);
	assert(pWave);

	Voice* pVoice = (Voice*)pMan->BaseAdd();
	assert(pVoice != nullptr);

	pVoice->Set(voice_id, pWave, pCallback);

	return pVoice;
}



Voice* VoiceMan::Find(VoiceID voice_id)
{
	VoiceMan* pMan = GetInstance();
	assert(pMan != nullptr);

	pMan->pNodeCompare->SetVoiceID(voice_id);

	Voice* pData = (Voice*)pMan->BaseFind(pMan->pNodeCompare);

	return pData;
}

void VoiceMan::Remove(Voice* pVoice)
{
	VoiceMan* pMan = GetInstance();
	assert(pMan != nullptr);

	assert(pVoice != nullptr);

	pMan->BaseRemove(pVoice);
}

void VoiceMan::Dump()
{
	VoiceMan* pMan = GetInstance();
	assert(pMan != nullptr);

	pMan->BaseDump();
}

DLink* VoiceMan::DerivedCreateNode()
{
	DLink* pNode = new Voice();
	assert(pNode != nullptr);

	return pNode;
}

bool VoiceMan::DerivedCompare(DLink* pLinkA, DLink* pLinkB)
{
	assert(pLinkA != nullptr);
	assert(pLinkB != nullptr);

	Voice* pDataA = (Voice*)pLinkA;
	Voice* pDataB = (Voice*)pLinkB;

	bool status = false;

	VoiceID A;
	VoiceID B;

	if (pDataA->GetVoiceId(A) != Handle::Status::SUCCESS)
	{
		assert(false);
	}

	if (pDataB->GetVoiceId(B) != Handle::Status::SUCCESS)
	{
		assert(false);
	}

	if (A == B)
	{
		status = true;
	}

	return status;
}

void VoiceMan::DerivedWash(DLink* pLink)
{
	assert(pLink != nullptr);
	Voice* pNode = (Voice*)pLink;
	pNode->Wash();
}

void VoiceMan::DerivedDumpNode(DLink* pLink)
{
	assert(pLink != nullptr);
	Voice* pData = (Voice*)pLink;
	pData->Dump();
}

void VoiceMan::DerivedDestroyNode(DLink* pLink)
{
	assert(pLink);
	Voice* pData = (Voice*)pLink;
	delete pData;
}

VoiceMan* VoiceMan::GetInstance()
{
	// Safety - this forces users to call Create() first before using class
	assert(pInstance != nullptr);

	return pInstance;
}


















