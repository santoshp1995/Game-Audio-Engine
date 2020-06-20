#include "Demo1_Thread.h"
#include "ThreadHelper.h"
#include "WaveDataMan.h"
#include "CallbackVoice.h"
#include "VoiceMan.h"
#include "AudioCommandsWrapper.h"
#include "LeftRightPan.h"
#include "RightLeftPan.h"
#include "IncreaseVolume.h"
#include "DecreaseVolume.h"

#include "Time.h"
#include "Timer.h"

bool WaitFor(Timer& t, Time TriggerTime)
{
	Time deltaTime(TIME_ZERO);

	if (deltaTime != TriggerTime)
	{
		while (!Time::quotient(deltaTime, TriggerTime))
		{
			// Spin
			deltaTime = t.toc();
		}
	}

	return true;
}

void Demo1_Main()
{
	ThreadHelper::DebugBegin(2);

	Voice* pFiddle0 = VoiceMan::Add(VoiceID::Fiddle, WaveDataID::FIDDLE);
	Voice* pFiddle1 = VoiceMan::Add(VoiceID::Fiddle, WaveDataID::FIDDLE);
	Voice* pFiddle2 = VoiceMan::Add(VoiceID::Fiddle, WaveDataID::FIDDLE);

	Voice* pBassoon0 = VoiceMan::Add(VoiceID::Bassoon, WaveDataID::BASSOON);
	Voice* pBassoon1 = VoiceMan::Add(VoiceID::Bassoon, WaveDataID::BASSOON);

	Voice* Oboe2 = VoiceMan::Add(VoiceID::Oboe, WaveDataID::OBOE2);
	Voice* pOboe2_1 = VoiceMan::Add(VoiceID::Oboe, WaveDataID::OBOE2);


	Voice* pSongA = VoiceMan::Add(VoiceID::SongA, WaveDataID::SONGA);
	Voice* pSongB = VoiceMan::Add(VoiceID::SongB, WaveDataID::SONGB);

	// sound instancing
	Voice* pBassoonA = VoiceMan::Add(VoiceID::Bassoon, WaveDataID::BASSOON);
	Voice* pBassoonB = VoiceMan::Add(VoiceID::Bassoon, WaveDataID::BASSOON);
	Voice* pBassoonC = VoiceMan::Add(VoiceID::Bassoon, WaveDataID::BASSOON);
	Voice* pBassoonD = VoiceMan::Add(VoiceID::Bassoon, WaveDataID::BASSOON);
	Timer t1;
	// start global timer
	t1.tic();
	
	Trace::out("--- PART B START ---\n");

	if (WaitFor(t1, Time(TIME_ZERO)))
	{
		Trace::out("--- Playing 101 ---\n");
		Trace::out("--- Panning Middle --\n");

		Command* pSetVolumeCommand = new SetVolumeCommand(pFiddle0, 0.7f);
		Command* pPlayCommand = new PlayCommand(pFiddle0);
		Command* pPanMiddle = new PanMiddleCommand(pFiddle0); 

		pSetVolumeCommand->execute();
		pPlayCommand->execute();
		pPanMiddle->execute();

		delete pPlayCommand;

	}


	if (WaitFor(t1, 3 * Time(TIME_ONE_SECOND)))
	{
		Trace::out("--- Playing 101 ---\n");
		Trace::out("--- Panning Left --\n");

		Command* pSetVolumeCommand = new SetVolumeCommand(pFiddle1, 0.7f);
		Command* pPanLeftCommand = new PanLeftCommand(pFiddle1);
		Command* pPlayCommand = new PlayCommand(pFiddle1);


		pSetVolumeCommand->execute();
		pPanLeftCommand->execute();
		pPlayCommand->execute();

		delete pPlayCommand;

	}

	if (WaitFor(t1, 6 * Time(TIME_ONE_SECOND)))
	{
		Trace::out("--- Playing 101 ---\n");
		Trace::out("--- Panning Right --\n");

		Command* pSetVolumeCommand = new SetVolumeCommand(pFiddle2, 0.7f);
		Command* pPanRightCommand = new PanRightCommand(pFiddle2);
		Command* pPlayCommand = new PlayCommand(pFiddle2);

		pSetVolumeCommand->execute();
		pPanRightCommand->execute();
		pPlayCommand->execute();


		delete pPlayCommand;
	}
	
	Sleep(2000);

	Trace::out("--- PART B END ---\n");
	
	Trace::out("--- PART C START ---\n");

	if (WaitFor(t1, 10 * Time(TIME_ONE_SECOND)))
	{
		Trace::out("--- PAN FROM LEFT TO RIGHT --- \n");
		ThreadHelper::TabMe(1);
		std::thread t(LeftRightPan_Main, pBassoon0);
		ThreadHelper::SetThreadName(t, "---LeftRightPan---");
		t.join();
	}

	if (WaitFor(t1, 15 * Time(TIME_ONE_SECOND)))
	{
		Trace::out("--- PAN FROM RIGHT TO LEFT --- \n");
		ThreadHelper::TabMe(1);
		std::thread t(RightLeftPan_Main, pBassoon1);
		ThreadHelper::SetThreadName(t, "---RightLeftPan---");
		t.join();
	}

	Trace::out("--- PART C END ---\n");

	Trace::out("--- PART D START ---\n");

	if (WaitFor(t1, 20 * Time(TIME_ONE_SECOND)))
	{
		Trace::out("--- VOLUME 0 TO 100 --- \n");
		ThreadHelper::TabMe(1);
		std::thread t(IncreaseVolume_Main, Oboe2);
		ThreadHelper::SetThreadName(t, "---IncreaseVolume---");
		t.join();
	}

	if (WaitFor(t1, 25 * Time(TIME_ONE_SECOND)))
	{
		Trace::out("--- VOLUME 100 TO 0 --- \n");
		ThreadHelper::TabMe(1);
		std::thread t(DecreaseVolume_Main, pOboe2_1);
		ThreadHelper::SetThreadName(t, "---DecreaseVolume---");
		t.join();
	}

	Trace::out("--- PART D END --- \n");

	Trace::out("--- PART E START ---\n");

	Command* pPanLeftCommand = new PanLeftCommand(pSongA);
	Command* pPlayCommand1 = new PlayCommand(pSongA);

	Command* pPanRightCommand = new PanRightCommand(pSongB);
	Command* pPlayCommand2 = new PlayCommand(pSongB);

	Timer songA_timer;
	Timer songB_timer;

	if (WaitFor(t1, 30 * Time(TIME_ONE_SECOND)))
	{
		pPanLeftCommand->execute();
		pPlayCommand1->execute();
		// start song timer
		songA_timer.tic();

		pPanRightCommand->execute();
		pPlayCommand2->execute();

		// start song timer
		songB_timer.tic();

		delete pPlayCommand1;
		delete pPlayCommand2;
	}

	if (WaitFor(t1, 35 * Time(TIME_ONE_SECOND)))
	{
		// check current time passed
		Time elapsedTime = songA_timer.toc();

		int timeInSeconds_Integer = Time::quotient(elapsedTime, Time(TIME_ONE_SECOND));

		Trace::out("SongA.wav has been playing for %d seconds\n", timeInSeconds_Integer);
	}

	if (WaitFor(t1, 38 * Time(TIME_ONE_SECOND)))
	{
		// check current time passed
		Time elapsedTime = songA_timer.toc();

		int timeInSeconds_Integer = Time::quotient(elapsedTime, Time(TIME_ONE_SECOND));

		Trace::out("SongA.wav has been playing for %d seconds\n", timeInSeconds_Integer);

	}

	if (WaitFor(t1, 60 * Time(TIME_ONE_SECOND)))
	{
		// check current time passed
		Time elapsedTime = songA_timer.toc();

		int timeInSeconds_Integer = Time::quotient(elapsedTime, Time(TIME_ONE_SECOND));

		Trace::out("SongA.wav has been playing for %d seconds\n", timeInSeconds_Integer);

		Command* pSetVolumeCommand = new SetVolumeCommand(pSongB, 0.0f);
		pSetVolumeCommand->execute();

		Command* pStopCommand = new StopCommand(pSongB);
		pStopCommand->execute();

		delete pStopCommand;

	}

	if (WaitFor(t1, 72 * Time(TIME_ONE_SECOND)))
	{
		// check current time passed
		Time elapsedTime = songB_timer.toc();

		int timeInSeconds_Integer = Time::quotient(elapsedTime, Time(TIME_ONE_SECOND));

		Trace::out("SongB.wav has been playing for %d seconds\n", timeInSeconds_Integer);

		Command* pSetVolumeCommand = new SetVolumeCommand(pSongA, 0.0f);
		pSetVolumeCommand->execute();

		Command* pStopCommand = new StopCommand(pSongA);
		pStopCommand->execute();

		delete pStopCommand;
		
	}

	Trace::out("--- PART E END --- \n");

	Trace::out("--- PART F START --- \n");

	if (WaitFor(t1, 80 * Time(TIME_ONE_SECOND)))
	{
		Command* pSetVolumeCommand = new SetVolumeCommand(pBassoonA, 0.4f);
		Command* pPlayCommand = new PlayCommand(pBassoonA);

		pSetVolumeCommand->execute();
		pPlayCommand->execute();

		delete pPlayCommand;
	}


	if (WaitFor(t1, 80.5f * Time(TIME_ONE_SECOND)))
	{
		Command* pSetVolumeCommand = new SetVolumeCommand(pBassoonB, 0.4f);
		Command* pPlayCommand = new PlayCommand(pBassoonB);

		pSetVolumeCommand->execute();
		pPlayCommand->execute();

		delete pPlayCommand;
	}

	if (WaitFor(t1, 81 * Time(TIME_ONE_SECOND)))
	{
		Command* pSetVolumeCommand = new SetVolumeCommand(pBassoonC, 0.4f);
		Command* pPlayCommand = new PlayCommand(pBassoonC);

		pSetVolumeCommand->execute();
		pPlayCommand->execute();

		delete pPlayCommand;
	}

	if (WaitFor(t1, 81.5f * Time(TIME_ONE_SECOND)))
	{
		Command* pSetVolumeCommand = new SetVolumeCommand(pBassoonD, 0.4f);
		Command* pPlayCommand = new PlayCommand(pBassoonD);

		Command* pStop1 = new StopCommand(pBassoonA);
		Command* pStop2 = new StopCommand(pBassoonB);
		Command* pStop3 = new StopCommand(pBassoonC);

		pSetVolumeCommand->execute();
		pPlayCommand->execute();
	
		pStop1->execute();
		pStop2->execute();
		pStop3->execute();

		delete pPlayCommand;
		delete pStop1;
		delete pStop2;
		delete pStop3;


	}


	Sleep(5000);


	Trace::out("--- PART F END --- \n");


	ThreadHelper::DebugEnd(2);

}