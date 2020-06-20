#ifndef DEMO3_3_H
#define DEMO3_3_H


#include "Command.h"
#include "SndMan.h"

class Demo3_3 : public Command
{
public:
	Demo3_3() = default;
	Demo3_3(const Demo3_3&) = delete;
	Demo3_3& operator= (const Demo3_3&) = delete;
	~Demo3_3() = default;


	virtual void execute() override
	{
		Trace::out("--- PART A --- \n");
		Trace::out("--- Timer 3 s --- \n");

		Snd* pSndF = SndMan::Add(SndId::Coma, nullptr ,100);
		assert(pSndF);

		// set volume and pan
		assert(pSndF->SetVolume(0.10f) == Handle::Status::SUCCESS);
		assert(pSndF->PanMiddle() == Handle::Status::SUCCESS);

		// now play it
		assert(pSndF->Play() == Handle::Status::SUCCESS);

		Snd::PrintPriorityTable();

	}

};


#endif