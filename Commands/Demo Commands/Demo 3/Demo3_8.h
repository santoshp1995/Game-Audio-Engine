#ifndef DEMO3_8_H
#define DEMO3_8_H

#include "Command.h"
#include "SndMan.h"

class Demo3_8 : public Command
{
public:
	Demo3_8() = default;
	Demo3_8(const Demo3_8&) = delete;
	Demo3_8& operator= (const Demo3_8&) = delete;
	~Demo3_8() = default;

	virtual void execute() override
	{
		Trace::out("--- PART A --- \n");
		Trace::out("--- Timer 8 s --- \n");

		Snd* pSndK = SndMan::Add(SndId::Coma, nullptr, 150);

		assert(pSndK->SetVolume(0.10f) == Handle::Status::SUCCESS);
		assert(pSndK->PanMiddle() == Handle::Status::SUCCESS);

		assert(pSndK->Play() == Handle::Status::SUCCESS);

		Snd::PrintPriorityTable();
	}




};


#endif
