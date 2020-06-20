//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "ThreadHelper.h"
#include "SndCallRegistry.h"
#include "AudioThread.h"
#include "BufferMan.h"
#include "AudioSystemMan.h"
#include "WaveDataMan.h"
#include "VoiceMan.h"
#include "ASndMan.h"
#include "SndMan.h"

void AudioMain()
{
	ThreadHelper::DebugBegin(1);

	// Create Audio System Manager
	AudioSystemMan::Create();

	AudioSystemMan::InitializeXAudio2();

	while (!ASndMan::IsQuit())
	{
		Command* pCommand = 0;

		if (SndMan::GetAudioInQueue()->PopFront(pCommand) == true)
		{
 			pCommand->execute();

			delete pCommand;
		}

		//std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}


	// Fall through... then end thread
	ThreadHelper::DebugEnd(1);
}


// End of File 