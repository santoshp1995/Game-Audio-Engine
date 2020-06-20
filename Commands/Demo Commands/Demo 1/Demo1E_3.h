#ifndef DEMO1E_3_H
#define DEMO1E_3_H

#include "Command.h"
#include "SndMan.h"

#include "Timer.h"

class Demo1E_3 : public Command
{
public:
	Demo1E_3() = delete;
	Demo1E_3(const Demo1E_3&) = delete;
	Demo1E_3& operator= (const Demo1E_3&) = delete;
	~Demo1E_3() = default;

	Demo1E_3(Snd* _pSndA, Snd* _pSndB, Snd* _pSndC)
		:pSndA(_pSndA), pSndB(_pSndB), pSndC(_pSndC)
	{
	}

	virtual void execute() override
	{
		// Start snd D
		Trace::out("pSndD -- Playing 102 -- 40 volume\n");
		Snd* pSndD = SndMan::Add(SndId::Bassoon);
		
		assert(pSndD->SetVolume(0.4f) == Handle::Status::SUCCESS);
		assert(pSndD->Play() == Handle::Status::SUCCESS);

		Trace::out("Stopping SndA\n");
		assert(this->pSndA->Stop() == Handle::Status::SUCCESS);

		Trace::out("Stopping SndB\n");
		assert(this->pSndB->Stop() == Handle::Status::SUCCESS);

		Trace::out("Stopping SndC\n");
		assert(this->pSndC->Stop() == Handle::Status::SUCCESS);

	}

private:
	Snd* pSndA;
	Snd* pSndB;
	Snd* pSndC;
};


#endif