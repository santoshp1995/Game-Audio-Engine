#ifndef DEMO1D_4_H
#define DEMO1D_4_H

#include "Command.h"
#include "Snd.h"

#include "Timer.h"

class Demo1D_4 : public Command
{
public:
	Demo1D_4() = delete;
	Demo1D_4(const Demo1D_4&) = delete;
	Demo1D_4& operator = (const Demo1D_4&) = delete;
	~Demo1D_4() = default;

	Demo1D_4(Snd* _pSnd)
		:pSnd(_pSnd)
	{
	}

	virtual void execute() override
	{
		assert(pSnd);

		Time elapsedTime = this->pSnd->GetSndPlayingTime();

		int timeInSeconds_Integer = Time::quotient(elapsedTime, Time(TIME_ONE_SECOND));

		Trace::out("SongB.wav has been playing for %d seconds\n", timeInSeconds_Integer);

		Trace::out("Stopping SongB.wav\n");

		assert(this->pSnd->Stop() == Handle::Status::SUCCESS);
		
	}


private:
	Snd* pSnd;
	
};

#endif