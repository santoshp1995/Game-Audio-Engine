#include "FileMan.h"
#include "SndMan.h"
#include "FileLoadCommand.h"
#include "FileQuitCommand.h"
#include "WaveDataMan.h"

FileMan::FileMan()
{
	this->poFileInQueue = new CircularData();
	assert(this->poFileInQueue);

	this->QuitFlag = false;
}

FileMan::~FileMan()
{
	assert(FileMan::IsQuit() == true);

	delete this->poFileInQueue;
}

Handle::Status FileMan::Add(const char* const pWaveName, WaveDataID name, FileUserCallback* pFileCallback)
{
	FileMan* pMan = FileMan::GetInstance();
	assert(pMan != nullptr);

	Handle::Lock lock(pMan->handle);

	if (lock)
	{
		// Now create a the sound call on the Audio thread
		// Place the "Create" command in the queue to the Audio thread
		CircularData* pOut = SndMan::GetAudioInQueue();
		assert(pOut);

		// Doesn't need to know snd_priority its only on game side
		Command* pCmd = new FileLoadCommand(pWaveName, name, pFileCallback);
		assert(pCmd);

		pOut->PushBack(pCmd);
	}
	else
	{
		assert(false);
	}

	//Trace::out("SndMan::Add() unlock\n");
	return lock;
}

CircularData* FileMan::GetFileInQueue()
{
	FileMan* pMan = FileMan::GetInstance();
	return pMan->poFileInQueue;
}

WaveData::Status FileMan::GetStatus(const WaveDataID id)
{
	FileMan* pMan = FileMan::GetInstance();
	assert(pMan != nullptr);

	WaveData::Status status = WaveData::Status::UNINITIALIZED;

	WaveData* pWave = WaveDataMan::Find(id);

	if (pWave)
	{
		status = pWave->GetStatus();
	}

	return status;

}

void FileMan::SetQuit()
{
	FileMan* pMan = FileMan::GetInstance();
	assert(pMan != nullptr);

	pMan->QuitFlag = true;

}

bool FileMan::IsQuit()
{
	FileMan* pMan = FileMan::GetInstance();
	assert(pMan != nullptr);

	return pMan->QuitFlag;
}

void FileMan::Quit()
{

	FileMan* pMan = FileMan::GetInstance();
	assert(pMan != nullptr);

	// Place the "Quit" command in the queue 
	CircularData* pOut = FileMan::GetFileInQueue();
	assert(pOut);

	Command* pCmd = new FileQuitCommand();
	assert(pCmd);

	pOut->PushBack(pCmd);

}

FileMan* FileMan::GetInstance()
{
	static FileMan fileMan;

	return &fileMan;
}
