#ifndef SND_H
#define SND_H

#include "HandleMan.h"
#include "SndID.h"
#include "ASnd.h"
#include "PlayDemo1Command.h"
#include "PlayDemo2Command.h"
#include "SndPriorityEntry.h"
#include "DLink.h"
#include "Timer.h"


typedef int SndPriority;

class Snd : public DLink
{
public:
	// CONSTANTS
	static const unsigned int SND_PRIORITY_TABLE_SIZE = 6;
	static const int SND_PRIORITY_TABLE_INVALID = -1;

public:
	Snd();
	Snd(const Snd&) = delete;
	Snd& operator=(const Snd&);
	~Snd();

	void SetID(SndId snd_id);
	SndId GetID(SndId& snd_id) const;

	void Set(SndId snd_id, SndPriority priority);

	void Dump();
	void Wash();


	// Audio Thread Sets
	void SetASnd(ASnd* p);
	void GetASnd(ASnd*& p) const;

	
	Handle::Status SetVolume(const float vol);
	Handle::Status SetPanning(const float pan);
	Handle::Status PanLeft();
	Handle::Status PanRight();
	Handle::Status PanMiddle();
	Handle::Status Stop();

	Handle::Status GetVol(float& _vol) const;
	Handle::Status GetPan(float& _pan) const;
	Handle::Status GetTimeInMS(int& timeInMS) const;


	// Priority Table functions
	Handle::Status Play();
	void RemoveFromPriorityTable();
	static void PrintPriorityTable();
	void SortTable(SndPriorityEntry table[]);
	bool isPreemptable(const int inPriority, int& outPriority, int& index);
	void RemoveFromTableByIndex(const int index);
	static void KillActiveSnds();
	static bool isTableEmpty();


	Handle::Status StartTime();
	Time GetSndPlayingTime();

	//------- DEBUG -----------------
	unsigned int GetHandleID()
	{
		return this->handle.GetID();
	}
	unsigned int GetHandleIndex()
	{
		return this->handle.GetIndex();
	}


private:
	void Clear();
	bool OpenSlotInTable();
	void privPlayHelper();


	// Snd data
	SndId sndID;
	ASnd* pAsnd;
	float vol;
	float pan;
	SndPriority priority;
	Timer timer;
	Handle handle;

public:
	static SndPriorityEntry  sndPriorityTable[SND_PRIORITY_TABLE_SIZE];
	static Handle	         table_handle;

};


#endif
