#include "Demo1B_0.h"

// thread helper
#include "ThreadHelper.h"
#include "Timer.h"

#include "AudioSystemMan.h"

// launch point for the thread
void Demo1B_0_Main(Snd* pSnd)
{
	assert(pSnd);

	//Handle::Status status;
	Timer timer;
	float delta;
	float pan;
	int TimeElapsed_MS;

	delta = (1.0f - (-1.0f)) / 1000.0f;
	pan = -1.0f;

	// start the timer
	timer.tic();

	// get the current time
	TimeElapsed_MS = Time::quotient(timer.toc(), Time(Duration::TIME_ONE_SECOND));

	// loop for 2 seconds
	while (TimeElapsed_MS < 2000)
	{
		pan += delta;

		AudioSystemMan::ChangePan(*AudioSystemMan::GetMasterVoice(), *AudioSystemMan::GetSourceVoice(), pan);
		
		// update every 1 ms
		std::this_thread::sleep_for(std::chrono::microseconds(1000));

		TimeElapsed_MS = Time::quotient(timer.toc(), Time(Duration::TIME_ONE_MILLISECOND));
	}

}