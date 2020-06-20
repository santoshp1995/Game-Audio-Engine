#include "PanLeftCommand.h"
#include "ASnd.h"

PanLeftCommand::PanLeftCommand(Voice* voice)
{
	this->pVoice = voice;
}

PanLeftCommand::PanLeftCommand(SndId _id, Snd* _pSnd)
	:id(_id),
	pSnd(_pSnd)
{
}

void PanLeftCommand::execute()
{
	// make sure the snd has been set
	assert(this->pSnd);

	// Get ASnd
	ASnd* pASnd;
	this->pSnd->GetASnd(pASnd);
	//assert(this->pSnd->GetASnd(pASnd) == Handle::Status::SUCCESS);

	// now change it's attributes
	pASnd->PanLeft();
}

PanLeftCommand::~PanLeftCommand()
{
}



