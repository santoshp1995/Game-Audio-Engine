#ifndef DEMO1A_2_H
#define DEMO1A_2_H

#include "Command.h"
#include "SndMan.h"

class Demo1A_2 : public Command
{
public:
	Demo1A_2() = default;
	Demo1A_2(const Demo1A_2&) = delete;
	Demo1A_2& operator= (const Demo1A_2&) = delete;
	~Demo1A_2() = default;

	// demo
	virtual void execute() override
	{
		Trace::out("--- Playing 101 ---\n");
		Trace::out("--- Panning Right --\n");

		// create a sound instance
		Snd* pSndA = SndMan::Add(SndId::Fiddle);
		assert(pSndA);

		// set volume and panning for this demo
		assert(pSndA->SetVolume(0.7f) == Handle::Status::SUCCESS);
		assert(pSndA->PanRight() == Handle::Status::SUCCESS);

		// now play it
		assert(pSndA->Play() == Handle::Status::SUCCESS);
	}

};


#endif
