#include "Command.h"
#include "SndMan.h"
#include "UserCallback.h"


class Demo4_1 : public Command
{
public:
	Demo4_1() = default;
	Demo4_1(const Demo4_1&) = delete;
	Demo4_1& operator= (const Demo4_1&) = delete;
	~Demo4_1() = default;

	virtual void execute() override
	{

		UserCallback* pCallbackD = new UserCallback();

		Snd* pSndD = SndMan::Add(SndId::Donkey, pCallbackD);
		assert(pSndD);

		assert(pSndD->SetVolume(0.10f) == Handle::Status::SUCCESS);
		assert(pSndD->PanLeft() == Handle::Status::SUCCESS);


		// play it
		assert(pSndD->Play() == Handle::Status::SUCCESS);

	}

};