#ifndef DEMO3_4_H
#define DEMO3_4_H

#include "Command.h"
#include "SndMan.h"


class Demo3_4 : public Command
{
public:
	Demo3_4() = default;
	Demo3_4(const Demo3_4&) = delete;
	Demo3_4& operator= (const Demo3_4&) = delete;
	~Demo3_4() = default;

	virtual void execute() override
	{
		Trace::out("--- PART A --- \n");
		Trace::out("--- Timer 4 s --- \n");

		Snd* pSndG = SndMan::Add(SndId::Coma, nullptr, 150);
		assert(pSndG);

		// set volume and pan
		assert(pSndG->SetVolume(0.10f) == Handle::Status::SUCCESS);
		assert(pSndG->PanMiddle() == Handle::Status::SUCCESS);

		// now play it
		assert(pSndG->Play() == Handle::Status::SUCCESS);

		Snd::PrintPriorityTable();
	}
};


#endif