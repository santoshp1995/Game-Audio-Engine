#include "SndPriorityEntry.h"

SndPriorityEntry::SndPriorityEntry()
{
	this->Clear();
}

void SndPriorityEntry::Clear()
{
	this->priority = -1;
	this->sndID = SndId::Uninitialized;
	this->handleID = 0;
	this->StartTime = Time(Duration::TIME_ZERO);
	this->pSnd = nullptr;
}

