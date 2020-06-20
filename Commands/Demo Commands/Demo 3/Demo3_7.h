#ifndef DEMO3_7_H
#define DEMO3_7_H


#include "Command.h"
#include "SndMan.h"

class Demo3_7 : public Command
{
public:
	Demo3_7() = default;
	Demo3_7(const Demo3_7&) = delete;
	Demo3_7& operator= (const Demo3_7&) = delete;
	~Demo3_7() = default;

	virtual void execute() override
	{
		Trace::out("--- PART A --- \n");
		Trace::out("--- Timer 7 s --- \n");

		Snd* pSndJ = SndMan::Add(SndId::Coma, nullptr, 75);
		assert(pSndJ);

		assert(pSndJ->SetVolume(0.10f) == Handle::Status::SUCCESS);
		assert(pSndJ->PanMiddle() == Handle::Status::SUCCESS);

		// play j
		assert(pSndJ->Play() == Handle::Status::SUCCESS);

		Snd::PrintPriorityTable();
	}




};



#endif
