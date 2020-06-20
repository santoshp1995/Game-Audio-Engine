#ifndef DEMO3_2_H
#define DEMO3_2_H

#include "Command.h"
#include "SndMan.h"

class Demo3_2 : public Command
{
public:
	Demo3_2() = default;
	~Demo3_2() = default;
	Demo3_2(const Demo3_2&) = delete;
	Demo3_2& operator = (const Demo3_2&) = delete;

	virtual void execute() override
	{
		Trace::out("--- PART A --- \n");
		Trace::out("--- Timer 2 s --- \n");

		Snd* pSndE = SndMan::Add(SndId::Coma, nullptr, 75);
		assert(pSndE);

		// set volume and panning
		assert(pSndE->SetVolume(0.10f) == Handle::Status::SUCCESS);
		assert(pSndE->PanMiddle() == Handle::Status::SUCCESS);

		// now play it
		assert(pSndE->Play() == Handle::Status::SUCCESS);

		Snd::PrintPriorityTable();

	}


};


#endif