#ifndef DEMO1C_0_H
#define DEMO1C_0_H

#include "Command.h"
#include "SndMan.h"

#include "ThreadHelper.h"

void Demo1C_0_Main(Snd* pSnd);


class Demo1C_0 : public Command
{
public:
	Demo1C_0() = default;
	Demo1C_0(const Demo1C_0&) = delete;
	Demo1C_0& operator= (const Demo1C_0&) = delete;
	~Demo1C_0() = default;

	virtual void execute() override
	{
		Trace::out("--- Playing 103 ---\n");
		Trace::out("--- VOLUME 0 TO 100 --\n");

		Snd* pSndA = SndMan::Add(SndId::Oboe2);

		assert(pSndA->SetVolume(0.0f) == Handle::Status::SUCCESS);
		assert(pSndA->PanMiddle() == Handle::Status::SUCCESS);

		// start playing
		assert(pSndA->Play() == Handle::Status::SUCCESS);

		std::thread  Demo1C_0_Thread(Demo1C_0_Main, pSndA);
		ThreadHelper::SetThreadName(Demo1C_0_Thread, "DEMO_1C_0");
		Demo1C_0_Thread.detach();
	}
};


#endif