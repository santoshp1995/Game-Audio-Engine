#ifndef DEMO1E_0_H
#define DEMO1E_0_H

#include "Command.h"
#include "SndMan.h"

#include "Timer.h"

class Demo1E_0 : public Command
{
public:
	Demo1E_0() = default;
	Demo1E_0(const Demo1E_0&) = delete;
	Demo1E_0& operator= (const Demo1E_0&) = delete;
	~Demo1E_0() = default;

	// public for easy access
	Snd* pSndA = SndMan::Add(SndId::Bassoon);

	virtual void execute() override
	{
		Trace::out("pSndA -- Playing 102 -- 40 volume\n");

		assert(pSndA->SetVolume(0.4f) == Handle::Status::SUCCESS);
		assert(pSndA->Play() == Handle::Status::SUCCESS);
	}
};


#endif