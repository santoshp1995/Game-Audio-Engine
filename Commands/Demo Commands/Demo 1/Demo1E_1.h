#ifndef DEMO1E_1_H
#define DEMO1E_1_H

#include "Command.h"
#include "SndMan.h"

#include "Timer.h"

class Demo1E_1 : public Command
{
public:
	Demo1E_1() = default;
	Demo1E_1(const Demo1E_1&) = delete;
	Demo1E_1& operator= (const Demo1E_1&) = delete;
	~Demo1E_1() = default;

	// public for easy access
	Snd* pSndB = SndMan::Add(SndId::Bassoon);

	virtual void execute() override
	{
		Trace::out("pSndB -- Playing 102 -- 40 volume\n");

		assert(pSndB->SetVolume(0.4f) == Handle::Status::SUCCESS);
		assert(pSndB->Play() == Handle::Status::SUCCESS);
	}
};

#endif