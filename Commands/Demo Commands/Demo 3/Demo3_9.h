#ifndef DEMO3_9_H
#define DEMO3_9_h

#include "Command.h"
#include "SndMan.h"

class Demo3_9 : public Command
{
public:
	Demo3_9() = default;
	Demo3_9(const Demo3_9&) = delete;
	Demo3_9& operator= (const Demo3_9&) = delete;
	~Demo3_9() = default;

	virtual void execute() override
	{

		// print before table killed
		Snd::PrintPriorityTable();


		Snd::KillActiveSnds();

		Trace::out("--- TABLE KILLED ---\n");
		Snd::PrintPriorityTable();
	}
};


#endif