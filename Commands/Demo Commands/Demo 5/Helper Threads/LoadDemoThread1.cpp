#include "LoadDemoThread1.h"
#include "ThreadHelper.h"
#include "FileMan.h"

void LoadDemoThread1_Main()
{
	ThreadHelper::DebugBegin(2);

	while (FileMan::GetStatus(WaveDataID::ALARM) != WaveData::Status::READY)
	{
		// spin
	}

	// Fall through... then end thread
	ThreadHelper::DebugEnd(2);
}