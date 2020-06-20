#ifndef DEMO4_0_H
#define DEMO4_0_H

#include "Command.h"
#include "SndMan.h"
#include "UserCallback.h"

class Demo4_0 : public Command
{
public:
	Demo4_0() = default;
	Demo4_0(const Demo4_0&) = delete;
	Demo4_0& operator = (const Demo4_0&) = delete;
	~Demo4_0() = default;

	virtual void execute() override
	{
		UserCallback* pCallbackA = new UserCallback();

		Snd* pSndA = SndMan::Add(SndId::Dial, pCallbackA);

		assert(pSndA->SetVolume(0.10f) == Handle::Status::SUCCESS);
		assert(pSndA->PanLeft() == Handle::Status::SUCCESS);

		// call play
		assert(pSndA->Play() == Handle::Status::SUCCESS);

		UserCallback* pCallbackB = new UserCallback();
		
		Snd* pSndB = SndMan::Add(SndId::Moon_Patrol, pCallbackB);

		assert(pSndB->SetVolume(0.10f) == Handle::Status::SUCCESS);
		assert(pSndB->PanRight() == Handle::Status::SUCCESS);

		// call play
		assert(pSndB->Play() == Handle::Status::SUCCESS);

		UserCallback* pCallbackC = new UserCallback();

		Snd* pSndC = SndMan::Add(SndId::Sequence, pCallbackC);
		assert(pSndC->SetVolume(0.10f) == Handle::Status::SUCCESS);
		assert(pSndC->PanLeft() == Handle::Status::SUCCESS);

		// call play
		assert(pSndC->Play() == Handle::Status::SUCCESS);

	}
};

#endif