#include "Command.h"
#include "SndMan.h"

// thread stuff
#include "ThreadHelper.h"

// thread that moves the snd
void Demo1B_0_Main(Snd* pSnd);


class Demo1B_0 : public Command
{
public:
	Demo1B_0() = default;
	Demo1B_0(const Demo1B_0&) = delete;
	Demo1B_0& operator= (const Demo1B_0&) = delete;
	~Demo1B_0() = default;

	virtual void execute() override
	{
		Trace::out("--- Playing 102 ---\n");
		Trace::out("--- Panning Pan Left to Right --\n");

		// create a snd call
		Snd* pSndA = SndMan::Add(SndId::Bassoon);

		// set volume and panning
		assert(pSndA->SetVolume(0.7f) == Handle::Status::SUCCESS);
		assert(pSndA->PanLeft() == Handle::Status::SUCCESS);

		// call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);

		// move it around in a seperate thread
		std::thread Demo1B_0_Thread(Demo1B_0_Main, pSndA);
		ThreadHelper::SetThreadName(Demo1B_0_Thread, "DEMO_1B_0");
		Demo1B_0_Thread.detach();
	}
};