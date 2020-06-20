#include "Demo1C_1.h"

#include "ThreadHelper.h"
#include "Timer.h"

#include "AudioSystemMan.h"

void Demo1C_1_Main(Snd* pSnd)
{
	assert(pSnd);

	Timer timer;
	//float delta;
	float vol;
	int TimeElapsed_MS;

	vol = 1.0f;

	// timer tic
	timer.tic();

	TimeElapsed_MS = Time::quotient(timer.toc(), Time(Duration::TIME_ONE_MILLISECOND));

	// loop for 2 seconds
	while (TimeElapsed_MS < 2000)
	{
		vol -= 0.001f;

		AudioSystemMan::SetVolume(AudioSystemMan::GetSourceVoice(), vol);

		// update every 1 ms
		std::this_thread::sleep_for(std::chrono::microseconds(1000));

		TimeElapsed_MS = Time::quotient(timer.toc(), Time(Duration::TIME_ONE_MILLISECOND));
	}
}