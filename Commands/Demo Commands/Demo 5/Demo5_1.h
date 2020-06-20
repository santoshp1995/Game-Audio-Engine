#ifndef DEMO5_1_H
#define DEMO5_1_H

#include "Command.h"
#include "SndMan.h"
#include "FileMan.h"
#include "GFileUserCallback.h"
#include <thread>
#include "ThreadHelper.h"
#include "LoadDemoThread2.h"

class Demo5_1 : public Command
{
public:
	Demo5_1() = delete;
	Demo5_1(const Demo5_1&) = delete;
	Demo5_1& operator= (const Demo5_1&) = delete;
	~Demo5_1() = default;

	Demo5_1(GFileUserCallback* _pGUserCB, Snd* _pSndB)
		: pGUserCB(_pGUserCB), pSndB(_pSndB)
	{

	}

	virtual void execute() override
	{
		// do check here.... hopefully this works...
		std::thread  LoadThread2(LoadDemoThread2_Main);
		ThreadHelper::SetThreadName(LoadThread2, "Load_Thread2");
		LoadThread2.join();

		this->pSndB->Stop();

		this->pGUserCB->execute();

		delete this->pGUserCB;
	}

private:
	GFileUserCallback* pGUserCB;
	Snd* pSndB;

};


#endif