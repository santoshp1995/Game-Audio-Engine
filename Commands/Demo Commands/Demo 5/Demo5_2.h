#include "Command.h"
#include "SndMan.h"

class Demo5_2 : public Command
{
public:
	Demo5_2() = default;
	Demo5_2(const Demo5_2&) = delete;
	Demo5_2& operator= (const Demo5_2&) = delete;
	~Demo5_2() = default;

	virtual void execute() override
	{
		Snd* pSndC = SndMan::Find(SndId::Beethoven);
		assert(pSndC);

		assert(pSndC->Stop() == Handle::Status::SUCCESS);

		Trace::out("--- DEMO 5 DONE ---\n");
	}
};

