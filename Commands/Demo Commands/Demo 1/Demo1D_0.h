#ifndef DEMO1D_0_H
#define DEMO1D_0_H

#include "Command.h"
#include "SndMan.h"

#include "Timer.h"

#include "ThreadHelper.h"

class Demo1D_0 : public Command
{
public:
	Demo1D_0() = default;
	Demo1D_0(const Demo1D_0& d) = delete;
	Demo1D_0& operator= (const Demo1D_0&) = delete;
	~Demo1D_0() = default;

	// public... keep it simple
	Snd* pSndA = SndMan::Add(SndId::SongA);
	Snd* pSndB = SndMan::Add(SndId::SongB);


	virtual void execute() override
	{
		Trace::out("--- Playing 104 ---\n");
		Trace::out("--- SONG A PAN LEFT ---\n");

		// set volume and panning
		assert(this->pSndA->SetVolume(0.7f) == Handle::Status::SUCCESS);
		assert(this->pSndA->PanLeft() == Handle::Status::SUCCESS);

		assert(this->pSndA->Play() == Handle::Status::SUCCESS);
		assert(this->pSndA->StartTime() == Handle::Status::SUCCESS);

		Trace::out("--- Playing 105 ---\n");
		Trace::out("--- SONG B PAN RIGHT ---\n");
	
		// set volume and panning
		assert(this->pSndB->SetVolume(0.7f) == Handle::Status::SUCCESS);
		assert(this->pSndB->PanRight() == Handle::Status::SUCCESS);

		assert(this->pSndB->Play() == Handle::Status::SUCCESS);
		assert(this->pSndB->StartTime() == Handle::Status::SUCCESS);
	}
};


#endif