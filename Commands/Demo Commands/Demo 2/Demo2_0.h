#ifndef DEMO2_0_H
#define DEMO2_0_H

#include "SndMan.h"
#include "Command.h"
#include "SeinfeldThread.h"
#include "ThreadHelper.h"

class Demo2_0 : public Command
{
public:
	Demo2_0() = default;
	Demo2_0(const Demo2_0&) = delete;
	Demo2_0& operator= (const Demo2_0&) = delete;
	~Demo2_0() = default;

	virtual void execute() override
	{
		std::thread  Seinfeld(SeinfeldThread_Main);
		ThreadHelper::SetThreadName(Seinfeld, "Seinfeld");
		Seinfeld.detach();
	}
};


#endif