//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

// Game App stuff
#include "AzulCore.h"
#include "Game.h"
#include "GameApp.h"
#include "InputTest.h"

#include "SndManger.h"
#include "Snd.h"

#include "ASndMan.h"
#include "SndMan.h"

#include "BufferMan.h"
#include "AudioSystemMan.h"
#include "PlayListMan.h"
#include "WaveDataMan.h"
#include "VoiceMan.h"

#include "TimeEventMan.h"

// DEMOS
#include "Demo1.h"
#include "Demo2.h"
#include "Demo3.h"
#include "Demo4.h"
#include "Demo5.h"

// Thread stuff
#include <thread>
#include "ThreadHelper.h"
#include "AudioThread.h"
#include "CircularData.h"

// File Thread stuff
#include "FileMain.h"
#include "FileMan.h"

// helper thread
#include "LoadDemoThread1.h"

//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Game::Initialize()
{
	// Game Window Device setup
	this->setWindowName("Audio Engine");
	this->setWidthHeight(400, 300);
	this->SetClearColor(0.74f, 0.74f, 0.86f, 1.0f);
}

//-----------------------------------------------------------------------------
// Game::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void Game::LoadContent()
{
	// Load up the demo application
	GameApp::LoadDemo(this->getWidth(), this->getHeight());

	// Name the current main thread
	ThreadHelper::SetCurrentThreadName("--- Game ---");
	ThreadHelper::DebugBegin(0);

	SndMan::Create();
	ASndMan::Create(3, 1);
	WaveDataMan::Create(3, 1);
	VoiceMan::Create(10, 3);
	PlayListMan::Create(3, 1);
	TimeEventMan::Create(3, 1);

	//---------------------------------------------------------------------------------------------------------
	// Launch a Thread
	//---------------------------------------------------------------------------------------------------------
	
	// Create an Audio thread...
	std::thread  AudioThread(AudioMain);
	ThreadHelper::SetThreadName(AudioThread, "AUDIO");
	AudioThread.detach();

	std::thread  FileThread(FileMain);
	ThreadHelper::SetThreadName(FileThread, "FILE");
	FileThread.detach();

	// DEMO 1 XAUDIO2 BASICS - FILE LOADING
	FileMan::Add("../../MS2_AudioFiles/SongA.wav", WaveDataID::SONGA);
	FileMan::Add("../../MS2_AudioFiles/SongB.wav", WaveDataID::SONGB);
	FileMan::Add("../../MS2_AudioFiles/Fiddle_mono.wav", WaveDataID::FIDDLE);
	FileMan::Add("../../MS2_AudioFiles/Bassoon_mono.wav", WaveDataID::BASSOON);
	FileMan::Add("../../MS2_AudioFiles/Oboe_mono.wav", WaveDataID::OBOE2);

	// DEMO 2 SEINFEILD STICHING - FILE LOADING
	FileMan::Add("../../MS2_AudioFiles/Intro_mono.wav", WaveDataID::INTRO);
	FileMan::Add("../../MS2_AudioFiles/A_mono.wav", WaveDataID::A);
	FileMan::Add("../../MS2_AudioFiles/AtoB_mono.wav", WaveDataID::AtoB);
	FileMan::Add("../../MS2_AudioFiles/B_mono.wav", WaveDataID::B);
	FileMan::Add("../../MS2_AudioFiles/BtoC_mono.wav", WaveDataID::BtoC);
	FileMan::Add("../../MS2_AudioFiles/C_mono.wav", WaveDataID::C);
	FileMan::Add("../../MS2_AudioFiles/CtoA_mono.wav", WaveDataID::CtoA);
	FileMan::Add("../../MS2_AudioFiles/End_mono.wav", WaveDataID::END);

	// DEMO 3 PRIORITY TABLE - FILE LOADING
	FileMan::Add("../../MS2_AudioFiles/Coma_mono.wav", WaveDataID::COMA);

	// DEMO 4 GAME USER CALLBACKS - FILE LOADING
	FileMan::Add("../../MS2_AudioFiles/Dial_mono.wav", WaveDataID::DIAL);
	FileMan::Add("../../MS2_AudioFiles/MoonPatrol_mono.wav", WaveDataID::MOON_PATROL);
	FileMan::Add("../../MS2_AudioFiles/Sequence1_mono.wav", WaveDataID::SEQUENCE);
	FileMan::Add("../../MS2_AudioFiles/Donkey_mono.wav", WaveDataID::DONKEY);

	// DEMO 5
	FileMan::Add("../../MS2_AudioFiles/Alert_mono.wav", WaveDataID::ALARM);
	FileMan::Add("../../MS2_AudioFiles/Electro_mono.wav", WaveDataID::ELECTRO);
	


	Sleep(5000);

	while (FileMan::GetStatus(WaveDataID::ELECTRO) != WaveData::Status::READY)
	{
		// spin
	}

	Trace::out("\n\n\n");
	Trace::out("All files loaded\n");
	Trace::out("\n\n\n");

}


//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void Game::Update()
{
	// Update the demo application
	GameApp::UpdateDemo();
	SndManager::Update();
	TimeEventMan::Update();

	// Read Quit Key
	Keyboard* key = Keyboard::GetInstance();
	assert(key);
	
	static bool QuitKey = false;

	if (key != nullptr)
	{
		if (key->GetKeyState(AZUL_KEY::KEY_Q) && !QuitKey)
		{
			// create a snd call
			SndMan::Quit(SndId::Quit);
			FileMan::Quit();
			QuitKey = true;
		}
	}

	static bool key1_state = false;
	// --- DEMO 1 --- //
	if (key->GetKeyState(AZUL_KEY::KEY_1) && !key1_state)
	{
		key1_state = true;
		
		Trace::out("--- INITIATING DEMO 1 ON THE GAME SIDE --- \n");

		Demo1();
		
	}

	static bool key2_state = false;
	// --- DEMO 2 --- //
	if (key->GetKeyState(AZUL_KEY::KEY_2) && !key2_state)
	{
		key2_state = true;
	
		Trace::out("--- INITIATING DEMO 2 ON THE GAME SIDE --- \n");

		Demo2();

	}

	static bool key3_state = false;
	if (key->GetKeyState(AZUL_KEY::KEY_3) && !key3_state)
	{
		key3_state = true;

		Demo3();
	}

	static bool key4_state = false;
	if (key->GetKeyState(AZUL_KEY::KEY_4) && !key4_state)
	{
		key4_state = true;

		Demo4();
	}

	static bool key5_state = false;
	if (key->GetKeyState(AZUL_KEY::KEY_5) && !key5_state)
	{
		key5_state = true;

		Demo5();

	}
}

//-----------------------------------------------------------------------------
// Game::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Game::Draw()
{
	// Draw the demo application
	GameApp::DrawDemo();

}



//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Game::UnLoadContent()
{
	// unload managers
	ASndMan::Destroy();
	PlayListMan::Destroy();
	VoiceMan::Destroy();
	WaveDataMan::Destroy();
	SndMan::Destroy();
	TimeEventMan::Destroy();
	BufferMan::Destroy();
	AudioSystemMan::Destroy();


	ThreadHelper::DebugEnd(0);
}

void Game::ProcessInQueue()
{
	// Process Queue
	Command* pCmd = nullptr;

	// Any commands to process?
	while (SndMan::GetGameInQueue()->PopFront(pCmd) == true)
	{
		assert(pCmd);
		pCmd->execute();

		// Commands are instantly killed after execution
		delete pCmd;
	}
}
// End of File 

