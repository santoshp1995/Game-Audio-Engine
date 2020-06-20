#ifndef DEMO5_0_H
#define DEMO5_0_H

#include "Command.h"
#include "SndMan.h"
#include "UserCallback.h"
#include "FileMan.h"
#include "GFileUserCallback.h"
#include "FileUserCallback.h"

class Demo5_0 : public Command
{
public:
	Demo5_0()
	{
		this->pFileCB = new FileUserCallback();
		assert(pFileCB);

		this->pFileCB->Set(SndId::Beethoven);

		this->pGFileCB = new GFileUserCallback(WaveDataID::BEETHOVEN, pFileCB);
		assert(pGFileCB);

	}
	Demo5_0(const  Demo5_0&) = delete;
	Demo5_0& operator= (const Demo5_0&) = delete;
	~Demo5_0() = default;

	Snd* pSndA = SndMan::Add(SndId::Electro);
	
	virtual void execute() override
	{
		UserCallback* pUserCB = new UserCallback();

		FileMan::Add("../../MS2_AudioFiles/Beethoven_stereo.wav", WaveDataID::BEETHOVEN, this->pFileCB);

		Snd* pSndB = SndMan::Add(SndId::Alarm, pUserCB);
		
		assert(pSndB);

		assert(pSndB->SetVolume(0.30f) == Handle::Status::SUCCESS);
		assert(pSndB->PanLeft() == Handle::Status::SUCCESS);

		// play
		assert(pSndB->Play() == Handle::Status::SUCCESS);


		assert(pSndA);

		assert(pSndA->SetVolume(0.30f) == Handle::Status::SUCCESS);
		assert(pSndA->PanLeft() == Handle::Status::SUCCESS);

		// play
		assert(pSndA->Play() == Handle::Status::SUCCESS);
	}

	FileUserCallback* pFileCB;
	GFileUserCallback* pGFileCB;
};



#endif