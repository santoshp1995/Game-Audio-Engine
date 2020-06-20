#ifndef DEMO1A_1_H
#define DEMO1A_1_H

#include "Command.h"
#include "SndMan.h"

class Demo1A_1 : public Command
{
public:
	Demo1A_1() = default;
	Demo1A_1(const Demo1A_1&) = delete;
	Demo1A_1& operator= (const Demo1A_1&) = delete;
	~Demo1A_1() = default;

	// demo
	virtual void execute() override
	{
		Trace::out("--- Playing 101 ---\n");
		Trace::out("--- Panning Left --\n");

		// create sound instance
		Snd* pSndA = SndMan::Add(SndId::Fiddle);
		assert(pSndA);

		// set the volume and panning for this demo
		assert(pSndA->SetVolume(0.7f) == Handle::Status::SUCCESS);
		assert(pSndA->PanLeft() == Handle::Status::SUCCESS);

		// now play it
		assert(pSndA->Play() == Handle::Status::SUCCESS);
	}




};


#endif
