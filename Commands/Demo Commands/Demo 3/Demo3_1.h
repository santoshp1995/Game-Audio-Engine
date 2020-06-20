#ifndef DEMO3_1_H
#define DEMO3_1_H

#include "Command.h"
#include "SndMan.h"

class Demo3_1 : public Command
{
public:
	Demo3_1() = default;
	Demo3_1(const Demo3_1&) = delete;
	Demo3_1& operator= (const Demo3_1&) = delete;
	~Demo3_1() = default;

	virtual void execute() override
	{
		Trace::out("--- PART A --- \n");
		Trace::out("--- Timer 1 s --- \n");

		// Play SndD
		Snd* pSndD = SndMan::Add(SndId::Coma, nullptr, 50);
		assert(pSndD);

		// set volume and panning
		assert(pSndD->PanMiddle() == Handle::Status::SUCCESS);
		assert(pSndD->SetVolume(0.10f) == Handle::Status::SUCCESS);

		// play it
		assert(pSndD->Play() == Handle::Status::SUCCESS);

		Snd::PrintPriorityTable();

	}


};

#endif