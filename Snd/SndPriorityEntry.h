#ifndef SND_PRIORITY_ENTRY_H
#define SND_PRIORITY_ENTRY_H

#include "Handle.h"
#include "SndID.h"

// forward declare
class Snd;

class SndPriorityEntry
{
public:
	SndPriorityEntry();

	void Clear();


	// Data
	Handle::ID handleID;
	SndId sndID;
	int priority;
	Time StartTime;
	Snd* pSnd;

};


#endif