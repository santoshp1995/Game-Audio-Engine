#include "Demo1C_0.h"

#include "ThreadHelper.h"
#include "Timer.h"

#include "AudioSystemMan.h"

void Demo1C_0_Main(Snd* pSnd)
{
	assert(pSnd);

	Timer timer;
	float delta;
	float vol;
	int TimeElapsed_MS;

	delta = (1.0f - (-1.0f)) / 1000.0f;
	vol = 0.0f;

	// timer tic
	timer.tic();

	TimeElapsed_MS = Time::quotient(timer.toc(), Time(Duration::TIME_ONE_MILLISECOND));

	// loop for 2 seconds
	while (TimeElapsed_MS < 2000)
	{
		vol += delta;

		AudioSystemMan::SetVolume(AudioSystemMan::GetSourceVoice(), vol);

		// update every 1 ms
		std::this_thread::sleep_for(std::chrono::microseconds(1000));

		TimeElapsed_MS = Time::quotient(timer.toc(), Time(Duration::TIME_ONE_MILLISECOND));
	}
}