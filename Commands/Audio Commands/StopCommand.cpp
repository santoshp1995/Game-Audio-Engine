#include "StopCommand.h"

StopCommand::StopCommand(Voice* voice)
{
	this->pVoice = voice;
}

StopCommand::StopCommand(SndId _id, Snd* _pSnd)
	:id(_id), pSnd(_pSnd)
{
}

void StopCommand::execute()
{
	// make sure pSnd created
	assert(pSnd);

	// created ASnd
	ASnd* pAsnd;
	this->pSnd->GetASnd(pAsnd);

	// now change it's attributes
	pAsnd->Stop();
}

StopCommand::~StopCommand()
{
}


