#ifndef DEMO1C_1_H
#define DEMO1C_1_H

#include "Command.h"
#include "SndMan.h"

#include "ThreadHelper.h"

void Demo1C_1_Main(Snd* pSnd);

class Demo1C_1 : public Command
{
public:
	Demo1C_1() = default;
	Demo1C_1(const Demo1C_1&) = delete;
	Demo1C_1& operator= (const Demo1C_1&) = delete;
	~Demo1C_1() = default;

	virtual void execute() override
	{
		Trace::out("--- Playing 103 ---\n");
		Trace::out("--- VOLUME 100 TO 0 --\n");

		Snd* pSndA = SndMan::Add(SndId::Oboe2);

		// set volume and panning
		assert(pSndA->SetVolume(1.0f) == Handle::Status::SUCCESS);
		assert(pSndA->PanMiddle() == Handle::Status::SUCCESS);

		// start playing
		assert(pSndA->Play() == Handle::Status::SUCCESS);

		std::thread  Demo1C_1_Thread(Demo1C_1_Main, pSndA);
		ThreadHelper::SetThreadName(Demo1C_1_Thread, "DEMO_1C_1");
		Demo1C_1_Thread.detach();
	}


};


#endif