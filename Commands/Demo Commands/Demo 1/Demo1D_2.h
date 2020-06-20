#include "Command.h"
#include "Snd.h"

#include "Timer.h"

class Demo1D_2 : public Command
{
public:
	Demo1D_2() = delete;
	Demo1D_2(const Demo1D_2&) = delete;
	Demo1D_2& operator= (const Demo1D_2&) = delete;
	~Demo1D_2() = default;

	Demo1D_2(Snd* _pSnd)
		:pSnd(_pSnd)
	{

	}

	virtual void execute() override
	{
		assert(pSnd);

		Time elapsedTime = this->pSnd->GetSndPlayingTime();

		int timeInSeconds_Integer = Time::quotient(elapsedTime, Time(TIME_ONE_SECOND));

		Trace::out("SongA.wav has been playing for %d seconds\n", timeInSeconds_Integer);
	}

private:
	Snd* pSnd;
};
