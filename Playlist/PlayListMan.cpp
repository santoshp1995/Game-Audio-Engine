#include "PlayListMan.h"

PlayListMan* PlayListMan::pInstance = nullptr;


PlayListMan::PlayListMan(int reserveNum, int reserveGrow) : Manager()
{
	this->BaseInitialize(reserveNum, reserveGrow);

	this->pNodeCompare = new PlayList();
	assert(this->pNodeCompare != nullptr);
}

PlayListMan::~PlayListMan()
{
	delete this->pNodeCompare;

	Trace::out("---> ~PlaylistMan()\n");
}

void PlayListMan::Create(int reserveNum, int reserveGrow)
{
	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(pInstance == nullptr);

	// do the singleton
	if (pInstance == nullptr)
	{
		pInstance = new PlayListMan(reserveNum, reserveGrow);
	}
}

void PlayListMan::Destroy()
{
	Trace::out("\n");
	Trace::out("---- Destroy() ----\n");

	PlayListMan* pMan = GetInstance();
	assert(pMan != nullptr);

	pMan->BaseDestroy();

	// kill the singleton
	delete pMan->pInstance;
}

PlayList* PlayListMan::Add(SndId snd_id)
{
	PlayListMan* pMan = GetInstance();
	assert(pMan != nullptr);

	PlayList* pNode = (PlayList*)pMan->BaseAdd();
	assert(pNode != nullptr);

	// create a new one
	switch (snd_id)
	{
	case SndId::Fiddle:
		pNode->Set(snd_id, VoiceID::Fiddle, WaveDataID::FIDDLE);
		break;

	case SndId::Bassoon:
		pNode->Set(snd_id, VoiceID::Bassoon, WaveDataID::BASSOON);
		break;

	case SndId::Oboe2:
		pNode->Set(snd_id, VoiceID::Oboe, WaveDataID::OBOE2);
		break;

	case SndId::SongA:
		pNode->Set(snd_id, VoiceID::SongA, WaveDataID::SONGA);
		break;

	case SndId::SongB:
		pNode->Set(snd_id, VoiceID::SongB, WaveDataID::SONGB);
		break;

	case SndId::Intro:
		pNode->Set(snd_id, VoiceID::INTRO, WaveDataID::INTRO);
		break;

	case SndId::A:
		pNode->Set(snd_id, VoiceID::A, WaveDataID::A);
		break;

	case SndId::AtoB:
		pNode->Set(snd_id, VoiceID::AtoB, WaveDataID::AtoB);
		break;

	case SndId::B:
		pNode->Set(snd_id, VoiceID::B, WaveDataID::B);
		break;

	case SndId::BtoC:
		pNode->Set(snd_id, VoiceID::BtoC, WaveDataID::BtoC);
		break;

	case SndId::C:
		pNode->Set(snd_id, VoiceID::C, WaveDataID::C);
		break;

	case SndId::CtoA:
		pNode->Set(snd_id, VoiceID::CtoA, WaveDataID::CtoA);
		break;

	case SndId::End:
		pNode->Set(snd_id, VoiceID::END, WaveDataID::END);
		break;

	case SndId::Coma:
		pNode->Set(snd_id, VoiceID::COMA, WaveDataID::COMA);
		break;

	case SndId::Dial:
		pNode->Set(snd_id, VoiceID::Dial, WaveDataID::DIAL);
		break;

	case SndId::Moon_Patrol:
		pNode->Set(snd_id, VoiceID::Moon_Patrol, WaveDataID::MOON_PATROL);
		break;

	case SndId::Sequence:
		pNode->Set(snd_id, VoiceID::Sequence, WaveDataID::SEQUENCE);
		break;

	case SndId::Donkey:
		pNode->Set(snd_id, VoiceID::Donkey, WaveDataID::DONKEY);
		break;

	case SndId::Electro:
		pNode->Set(snd_id, VoiceID::Electro, WaveDataID::ELECTRO);
		break;

	case SndId::Alarm:
		pNode->Set(snd_id, VoiceID::Alarm, WaveDataID::ALARM);
		break;

	case SndId::Beethoven:
		pNode->Set(snd_id, VoiceID::Beethoven, WaveDataID::BEETHOVEN);
		break;

	case SndId::Quit:
		assert(false);
		break;

	case SndId::Uninitialized:
		assert(false);
		break;
	}

	return pNode;	
}

PlayList* PlayListMan::Find(SndId id)
{
	PlayListMan* pMan = GetInstance();
	assert(pMan != nullptr);

	pMan->pNodeCompare->SetID(id);

	PlayList* pData = (PlayList*)pMan->BaseFind(pMan->pNodeCompare);

	return pData;
}

void PlayListMan::Remove(PlayList* pNode)
{
	PlayListMan* pMan = GetInstance();
	assert(pMan != nullptr);

	assert(pNode != nullptr);
	pMan->BaseRemove(pNode);
}

void PlayListMan::Dump()
{
	PlayListMan* pMan = GetInstance();
	assert(pMan != nullptr);

	pMan->BaseDump();
}

DLink* PlayListMan::DerivedCreateNode()
{
	DLink* pNode = new PlayList();
	assert(pNode != nullptr);

	return pNode;
}

bool PlayListMan::DerivedCompare(DLink* pLinkA, DLink* pLinkB)
{
	// This is used in baseFind() 
	assert(pLinkA != nullptr);
	assert(pLinkB != nullptr);

	PlayList* pDataA = (PlayList*)pLinkA;
	PlayList* pDataB = (PlayList*)pLinkB;

	bool status = false;

	SndId A;
	SndId B;

	if (pDataA->GetID(A) != Handle::Status::SUCCESS)
	{
		assert(false);
	}

	if (pDataB->GetID(B) != Handle::Status::SUCCESS)
	{
		assert(false);
	}

	if (A == B)
	{
		status = true;
	}

	return status;
}

void PlayListMan::DerivedWash(DLink* pLink)
{
	assert(pLink != nullptr);
	PlayList* pNode = (PlayList*)pLink;
	pNode->Wash();
}

void PlayListMan::DerivedDumpNode(DLink* pLink)
{
	assert(pLink != nullptr);
	PlayList* pData = (PlayList*)pLink;
	pData->Dump();
}

void PlayListMan::DerivedDestroyNode(DLink* pLink)
{
	assert(pLink);
	PlayList* pData = (PlayList*)pLink;
	delete pData;
}

PlayListMan* PlayListMan::GetInstance()
{
	// Safety - this forces users to call Create() first before using class
	assert(pInstance != nullptr);

	return pInstance;
}


















