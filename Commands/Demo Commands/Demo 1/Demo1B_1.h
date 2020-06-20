#ifndef DEMO1B_1_H
#define DEMO1B_1_H

#include "Command.h"
#include "SndMan.h"

// thread stuff
#include "ThreadHelper.h"

// thread that moves the sound
void Demo1B_1_Main(Snd* pSnd);

class Demo1B_1 : public Command
{
public:
	Demo1B_1() = default;
	Demo1B_1(const Demo1B_1&) = delete;
	Demo1B_1& operator= (const Demo1B_1&) = delete;
	~Demo1B_1() = default;

	virtual void execute() override
	{
		Trace::out("--- Playing 102 ---\n");
		Trace::out("--- Panning Pan Right to Left --\n");

		// create a Snd Call
		Snd* pSndA = SndMan::Add(SndId::Bassoon);

		// set the volume and panning
		assert(pSndA->SetVolume(0.7f) == Handle::Status::SUCCESS);
		assert(pSndA->PanRight() == Handle::Status::SUCCESS);

		// call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);

		std::thread Demo1B_1_Thread(Demo1B_1_Main, pSndA);
		ThreadHelper::SetThreadName(Demo1B_1_Thread, "DEMO_1B_1");
		Demo1B_1_Thread.detach();
	}
};


#endif