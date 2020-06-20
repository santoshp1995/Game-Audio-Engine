#ifndef DEMO3_6_H
#define DEMO3_6_H

#include "Command.h"
#include "SndMan.h"

class Demo3_6 : public Command
{
public:
	Demo3_6() = default;
	Demo3_6(const Demo3_6&) = delete;
	Demo3_6& operator= (const Demo3_6&) = delete;
	~Demo3_6() = default;

	virtual void execute() override
	{
		Trace::out("--- PART A --- \n");
		Trace::out("--- Timer 6 s --- \n");

		Snd* pSndI = SndMan::Add(SndId::Coma, nullptr, 75);
		assert(pSndI);

		// set volume and pan
		assert(pSndI->SetVolume(0.10f) == Handle::Status::SUCCESS);
		assert(pSndI->PanMiddle() == Handle::Status::SUCCESS);


		// play it
		assert(pSndI->Play() == Handle::Status::SUCCESS);

		Snd::PrintPriorityTable();
	}


};


#endif