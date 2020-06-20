#include "LoadDemoThread2.h"
#include "ThreadHelper.h"
#include "FileMan.h"

void LoadDemoThread2_Main()
{

	ThreadHelper::DebugBegin(2);

	while (FileMan::GetStatus(WaveDataID::BEETHOVEN) != WaveData::Status::READY)
	{
		// spin
	}

	// Fall through... then end thread
	ThreadHelper::DebugEnd(2);




}