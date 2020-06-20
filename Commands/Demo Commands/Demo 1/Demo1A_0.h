#ifndef DEMO1_A_0_H
#define DEMO1_A_0_H

#include "Command.h"
#include "SndMan.h"

class Demo1A_0 : public Command
{
public:
	Demo1A_0() = default;
	Demo1A_0(const Demo1A_0&) = delete;
	Demo1A_0& operator= (const Demo1A_0&) = delete;
	~Demo1A_0() = default;

	// demo
	virtual void execute() override
	{
		Trace::out("--- Playing 101 ---\n");
		Trace::out("--- Panning Middle --\n");

		Snd* pSndA = SndMan::Add(SndId::Fiddle);
		assert(pSndA);

		// set the volume and panning for this demo
		assert(pSndA->SetVolume(0.7f) == Handle::Status::SUCCESS);
		assert(pSndA->PanMiddle() == Handle::Status::SUCCESS);

		// start play!
		assert(pSndA->Play() == Handle::Status::SUCCESS);
	}
};


#endif