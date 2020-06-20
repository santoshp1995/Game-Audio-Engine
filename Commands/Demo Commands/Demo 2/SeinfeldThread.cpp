#include "SeinfeldThread.h"
#include "ThreadHelper.h"
#include "VoiceMan.h"
#include "CallbackVoice.h"
#include "AudioSystemMan.h"

void SeinfeldThread_Main()
{
	ThreadHelper::DebugBegin(2);

	VoiceCallback* pCallbackA = new VoiceCallback("Intro.wav");
	VoiceCallback* pCallbackB = new VoiceCallback("A.wav");
	VoiceCallback* pCallbackC = new VoiceCallback("AtoB.wav");
	VoiceCallback* pCallbackD = new VoiceCallback("B.wav");
	VoiceCallback* pCallbackE = new VoiceCallback("BtoC.wav");
	VoiceCallback* pCallbackF = new VoiceCallback("C.wav");
	VoiceCallback* pCallbackG = new VoiceCallback("CtoA.wav");
	VoiceCallback* pCallbackH = new VoiceCallback("End.wav");

	Voice* pIntro = VoiceMan::Add(VoiceID::INTRO, WaveDataID::INTRO, pCallbackA);
	assert(pIntro);

	Voice* pA = VoiceMan::Add(VoiceID::A, WaveDataID::A, pCallbackB);
	assert(pA);

	Voice* pAtoB = VoiceMan::Add(VoiceID::AtoB, WaveDataID::AtoB, pCallbackC);
	assert(pAtoB);

	Voice* pB = VoiceMan::Add(VoiceID::B, WaveDataID::B, pCallbackD);
	assert(pB);

	Voice* pBtoC = VoiceMan::Add(VoiceID::BtoC, WaveDataID::BtoC, pCallbackE);
	assert(pBtoC);

	Voice* pC = VoiceMan::Add(VoiceID::C, WaveDataID::C, pCallbackF);
	assert(pC);

	Voice* pCtoA = VoiceMan::Add(VoiceID::CtoA, WaveDataID::CtoA, pCallbackG);
	assert(pCtoA);

	Voice* pEnd = VoiceMan::Add(VoiceID::END, WaveDataID::END, pCallbackH);

	pCallbackA->SetNextVoice(pA);
	pCallbackB->SetNextVoice(pAtoB);
	pCallbackC->SetNextVoice(pB);
	pCallbackD->SetNextVoice(pBtoC);
	pCallbackE->SetNextVoice(pC);
	pCallbackF->SetNextVoice(pCtoA);
	pCallbackG->SetNextVoice(pEnd);
	pCallbackH->SetNextVoice(nullptr);

	pIntro->Start();


	while (!pCallbackH->IsFinished())
	{
		Trace::out("Panning Middle\n");
		AudioSystemMan::ChangePan(*AudioSystemMan::GetMasterVoice(), *AudioSystemMan::GetCurrentSourceVoice(), 0.0f);
		AudioSystemMan::SetVolume(AudioSystemMan::GetCurrentSourceVoice(), 0.8f);
		std::this_thread::sleep_for(std::chrono::seconds(10));

		Trace::out("Panning Right\n");
		AudioSystemMan::ChangePan(*AudioSystemMan::GetMasterVoice(), *AudioSystemMan::GetCurrentSourceVoice(), 1.0f);
		AudioSystemMan::SetVolume(AudioSystemMan::GetCurrentSourceVoice(), 0.8f);
		std::this_thread::sleep_for(std::chrono::seconds(10));


		Trace::out("Panning Left\n");
		AudioSystemMan::ChangePan(*AudioSystemMan::GetMasterVoice(), *AudioSystemMan::GetCurrentSourceVoice(), -1.0f);
		AudioSystemMan::SetVolume(AudioSystemMan::GetCurrentSourceVoice(), 0.8f);
		std::this_thread::sleep_for(std::chrono::seconds(10));
	}


	// Fall through... then end thread
	ThreadHelper::DebugEnd(2);

	Trace::out("THREAD ENDED\n");
}