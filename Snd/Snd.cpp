#include "CircularData.h"
#include "SndManger.h"
#include "Snd.h"
#include "SndMan.h"
#include "AudioCommandsWrapper.h"
#include "TimeEventMan.h"
#include "ASndMan.h"

// Static store
SndPriorityEntry  Snd::sndPriorityTable[Snd::SND_PRIORITY_TABLE_SIZE];
Handle	          Snd::table_handle;

Snd::Snd()
	:sndID(SndId::Uninitialized),
	pAsnd(nullptr),
	vol(0.0f),
	pan(0.0f),
	priority(0),
	timer(),
	handle()
{
}

Snd& Snd::operator=(const Snd& s)
{
	this->sndID = s.sndID;
	this->pAsnd = s.pAsnd;
	this->vol = s.vol;
	this->priority = s.priority;

	return *this;
}

Snd::~Snd()
{
	//delete this->pCommand;
	// Kills handle automatically
}

void Snd::RemoveFromPriorityTable()
{
	for (unsigned int i = 0; i < Snd::SND_PRIORITY_TABLE_SIZE; i++)
	{
		if (Snd::sndPriorityTable[i].handleID == this->handle.GetID())
		{
			Snd::sndPriorityTable[i].Clear();
			break;
		}
	}
	
}

void Snd::PrintPriorityTable()
{

	Trace::out("---------------------------------\n");
	Trace::out(" Snd Priority Table \n");
	Trace::out("---------------------------------\n");
	for (unsigned int i = 0; i < Snd::SND_PRIORITY_TABLE_SIZE; i++)
	{
		if (Snd::sndPriorityTable[i].priority != -1)
		{
			Time delta = (TimeEventMan::GetTimeCurrent()) - sndPriorityTable[i].StartTime;

			Trace::out("handle: 0x%x SndID: %d priority:%4d  time: %d ms\n",
				sndPriorityTable[i].handleID,
				sndPriorityTable[i].sndID,
				sndPriorityTable[i].priority,
				Time::quotient(delta, Time(Duration::TIME_ONE_MILLISECOND)));
		}
		else
		{

			Trace::out("handle: 0x-------- SndID: --- priority: ---  time: --- \n");
		}
	}

	Trace::out("---------------------------------\n");
}

// Sorts table by Time in MS
void Snd::SortTable(SndPriorityEntry table[])
{
	SndPriorityEntry temp;

	for (int i = 0; i < Snd::SND_PRIORITY_TABLE_SIZE; i++)
	{
		for (int j = i + 1; j < Snd::SND_PRIORITY_TABLE_SIZE; j++)
		{
			if (table[i].StartTime > table[j].StartTime)
			{
				temp = table[i];
				table[i] = table[j];
				table[j] = temp;
			}
		}
	}
}

bool Snd::isPreemptable(const int inPriority, int& outPriority, int& index)
{
	int lowest_priority = -1;

	for (int i = 0; i < Snd::SND_PRIORITY_TABLE_SIZE; i++)
	{
		if (sndPriorityTable[i].priority > lowest_priority)
		{
			lowest_priority = sndPriorityTable[i].priority;
			index = i;
		}
	}

	// found the lower priority, or we have to remove priority of the same
	if (lowest_priority >= inPriority)
	{
		outPriority = lowest_priority;

		return true;
	}

	return false;
}

void Snd::RemoveFromTableByIndex(const int index)
{
	// kill the current snd
	Snd::sndPriorityTable[index].pSnd->Stop();

	// clear everything from the current index in the table
	Snd::sndPriorityTable[index].Clear();

}

void Snd::KillActiveSnds()
{
	for (int i = 0; i < Snd::SND_PRIORITY_TABLE_SIZE; i++)
	{
		Snd::sndPriorityTable[i].pSnd->Stop();

		Snd::sndPriorityTable[i].Clear();
	}
}

bool Snd::isTableEmpty()
{
	if (Snd::sndPriorityTable[0].priority == -1)
	{
		return true;
	}

	return false;
}


void Snd::SetID(SndId snd_id)
{
	this->sndID = snd_id;
}

SndId Snd::GetID(SndId& snd_id) const
{
	return snd_id = this->sndID;
}

void Snd::Set(SndId snd_id, SndPriority _priority)
{
	this->sndID = snd_id;
	this->priority = _priority;
}

void Snd::Dump()
{
	SndId _id;
	this->GetID(_id);

	// Dump - Print contents to the debug output window
	Trace::out("   Name: %d (%p) \n", this->GetID(_id), this);
}

void Snd::Wash()
{
	// Wash - clear the entire hierarchy
	DLink::Clear();

	// Sub class clear
	this->Clear();
}

void Snd::SetASnd(ASnd* p)
{
	this->pAsnd = p;
}

void Snd::GetASnd(ASnd*& p) const
{
	p = this->pAsnd;
}

Handle::Status Snd::Play()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		Handle::Lock tableLock(this->table_handle);

		if (tableLock)
		{
			if (this->OpenSlotInTable())
			{
				// cleaner
				this->privPlayHelper();
			}
			else
			{
				int priorityToRemove = -1;
				int index = -1;

				bool status = this->isPreemptable(this->priority, priorityToRemove, index);

				if (status)
				{
					this->RemoveFromTableByIndex(index);

					// should always be true here, verify

					assert(this->OpenSlotInTable() == true);

					// go
					this->privPlayHelper();
				}

				else
				{
					Trace::out("--- SND CALL FAILED ---");
				}

				// No - Slots
				// Can I preempt the sound?
				// To DO
			}
		}
		else
		{
			assert(false);
		}
	}
	else
	{
		assert(false);
	}

	return lock;
}

bool Snd::OpenSlotInTable()
{
	bool status = false;

	// find open slot?
	for (int i = 0; i < Snd::SND_PRIORITY_TABLE_SIZE; i++)
	{
		if (sndPriorityTable[i].priority == -1)
		{
			sndPriorityTable[i].priority = this->priority;
			sndPriorityTable[i].sndID = this->sndID;
			sndPriorityTable[i].handleID = this->handle.GetID();
			sndPriorityTable[i].StartTime = TimeEventMan::GetTimeCurrent();
			sndPriorityTable[i].pSnd = this;

			// Found one
			status = true;
			break;
		}
	}

	return status;
}

void Snd::privPlayHelper()
{
	this->SortTable(Snd::sndPriorityTable);

	// Place the Play command in the queue to the Audio thread
	CircularData* pOut = SndMan::GetAudioInQueue();
	assert(pOut);

	Command* pCommand = new PlaySndCommand(this->sndID, this);
	assert(pCommand);

	pOut->PushBack(pCommand);

}

Handle::Status Snd::SetVolume(const float _vol)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		CircularData* pOut = SndMan::GetAudioInQueue();
		assert(pOut);

		this->vol = _vol;

		// create command
		Command* pCommand = new SetVolumeCommand(this->sndID, this, vol);
		assert(pCommand);

		// push command to queue
		pOut->PushBack(pCommand);
	}

	return lock;
}

Handle::Status Snd::SetPanning(const float _pan)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		CircularData* pOut = SndMan::GetAudioInQueue();
		assert(pOut);

		// Create command 
		Command* pCommand = new SetPanningCommand(this->sndID, this, _pan);
		assert(pCommand);

		// push command to queue
		pOut->PushBack(pCommand);
	}

	return lock;
}

Handle::Status Snd::PanLeft()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		this->pan = -1.0f;

		// Send a play command to the Audio thread
		CircularData* pOut = SndMan::GetAudioInQueue();
		assert(pOut);

		// Create command
		Command* pCommand = new PanLeftCommand(this->sndID, this);

		// push command to queue
		pOut->PushBack(pCommand);

	}
	return lock;
}

Handle::Status Snd::PanRight()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		this->pan = 1.0f;

		// Send a play command to the Audio thread
		CircularData* pOut = SndMan::GetAudioInQueue();
		assert(pOut);

		// create the command
		Command* pCommand = new PanRightCommand(this->sndID, this);
		assert(pCommand);

		// push to queue
		pOut->PushBack(pCommand);
	}
	return lock;
}

Handle::Status Snd::PanMiddle()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		this->pan = 0.0f;


		// Send a play command to the Audio thread
		CircularData* pOut = SndManager::GetG2A();
		assert(pOut);

		// create command
		Command* pCommand = new PanMiddleCommand(this->sndID, this);
		assert(pCommand);

		// push to queue
		pOut->PushBack(pCommand);

		delete pCommand;
	}
	return lock;
}

Handle::Status Snd::Stop()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		// Send a play command to the Audio thread
		CircularData* pOut = SndManager::GetG2A();
		assert(pOut);

		// create command
		Command* pCommand = new StopCommand(this->sndID, this);
		assert(pCommand);

		// push to queue
		pOut->PushBack(pCommand);

		pCommand->execute();

		delete pCommand;
	}

	return lock;
}

Handle::Status Snd::GetPan(float& _pan) const
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		_pan = this->pan;
	}

	return lock;
}

Handle::Status Snd::GetTimeInMS(int& timeInMS) const
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		// table lock
		Handle::Lock tableLock(this->table_handle);

		// Check Priority table
		if (tableLock)
		{
			bool status = false;
			for (unsigned int i = 0; i < Snd::SND_PRIORITY_TABLE_SIZE; i++)
			{
				if (Snd::sndPriorityTable[i].handleID == this->handle.GetID())
				{
					Time delta = (TimeEventMan::GetTimeCurrent()) - sndPriorityTable[i].StartTime;

					timeInMS = Time::quotient(delta, Time(Duration::TIME_ONE_MILLISECOND));

					status = true;
					break;
				}
			}

			if (!status)
			{
				assert(false);
			}
		}
		else
		{
			assert(false);
		}
	}

	return lock;
}

Handle::Status Snd::GetVol(float& _vol) const
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		_vol = this->vol;
	}

	return lock;
}

Handle::Status Snd::StartTime() 
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		// start time
		this->timer.tic();
	}
	return lock;
}

Time Snd::GetSndPlayingTime()
{
	return this->timer.toc();
}

void Snd::Clear()
{
	this->sndID = SndId::Uninitialized;
}

