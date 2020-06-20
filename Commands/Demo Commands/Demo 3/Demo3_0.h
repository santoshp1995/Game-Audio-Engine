#ifndef DEMO3_0_H
#define DEMO3_0_H

#include "Command.h"
#include "SndMan.h"

class Demo3_0 : public Command
{
public:
	Demo3_0() = default;
	~Demo3_0() = default;
	Demo3_0(const Demo3_0&) = delete;
	Demo3_0& operator = (const Demo3_0&) = delete;

	virtual void execute() override
	{
		Trace::out("-- PART A --- \n");
		Trace::out("-- Timer 0 s --\n");

		// Play SndA
		Snd* pSndA = SndMan::Add(SndId::Coma, nullptr, 10);
		assert(pSndA);

		// set volume & panning
		assert(pSndA->SetVolume(0.10f) == Handle::Status::SUCCESS);
		assert(pSndA->PanMiddle() == Handle::Status::SUCCESS);

		// call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);


		// Play SndB
		Snd* pSndB = SndMan::Add(SndId::Coma, nullptr,50);
		assert(pSndB);

		assert(pSndB->SetVolume(0.10f) == Handle::Status::SUCCESS);
		assert(pSndB->PanMiddle() == Handle::Status::SUCCESS);

		// call the sound
		assert(pSndB->Play() == Handle::Status::SUCCESS);

		// Play Snd C
		Snd* pSndC = SndMan::Add(SndId::Coma, nullptr, 150);
		assert(pSndC);

		assert(pSndC->SetVolume(0.10f) == Handle::Status::SUCCESS);
		assert(pSndC->PanMiddle() == Handle::Status::SUCCESS);

		// call it
		assert(pSndC->Play() == Handle::Status::SUCCESS);


		Snd::PrintPriorityTable();
	}
};

#endif