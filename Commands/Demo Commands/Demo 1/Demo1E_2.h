#ifndef DEMO1E_2_H
#define DEMO1E_2_h

#include "Command.h"
#include "SndMan.h"

#include "Timer.h"


class Demo1E_2 : public Command
{
public:
	Demo1E_2() = default;
	Demo1E_2(const Demo1E_2&) = delete;
	Demo1E_2& operator= (const Demo1E_2&) = delete;
	~Demo1E_2() = default;

	Snd* pSndC = SndMan::Add(SndId::Bassoon);

	virtual void execute() override
	{
		Trace::out("pSndC -- Playing 102 -- 40 volume\n");

		assert(pSndC->SetVolume(0.4f) == Handle::Status::SUCCESS);
		assert(pSndC->Play() == Handle::Status::SUCCESS);
	}

};



#endif
