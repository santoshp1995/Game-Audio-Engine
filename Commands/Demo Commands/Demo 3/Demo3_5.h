#ifndef DEMO3_5_H
#define DEMO3_5_H

#include "Command.h"
#include "SndMan.h"

class Demo3_5 : public Command
{
public:
	Demo3_5() = default;
	Demo3_5(const Demo3_5&) = delete;
	Demo3_5& operator= (const Demo3_5&) = delete;
	~Demo3_5() = default;

	virtual void execute() override
	{
		Trace::out("--- PART A --- \n");
		Trace::out("--- Timer 5 s --- \n");

		Snd* pSndH = SndMan::Add(SndId::Coma, nullptr ,75);
		assert(pSndH);

		// set volume and panning
		assert(pSndH->SetVolume(0.10f) == Handle::Status::SUCCESS);
		assert(pSndH->PanMiddle() == Handle::Status::SUCCESS);

		// play it
		assert(pSndH->Play() == Handle::Status::SUCCESS);

		Snd::PrintPriorityTable();

	}

};



#endif