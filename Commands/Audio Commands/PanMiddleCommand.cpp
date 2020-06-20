#include "PanMiddleCommand.h"
#include "ASnd.h"

PanMiddleCommand::PanMiddleCommand(Voice* voice)
{
	this->pVoice = voice;
}

PanMiddleCommand::PanMiddleCommand(SndId _id, Snd* _pSnd)
	:
	id(_id),
	pSnd(_pSnd)
{
}

void PanMiddleCommand::execute()
{
	// make sure pSnd created
	assert(this->pSnd);

	// Get the Asnd
	ASnd* pASnd;
	this->pSnd->GetASnd(pASnd);
	//assert(this->pSnd->GetASnd(pASnd) == Handle::Status::SUCCESS);

	// now change it's attributes
	pASnd->PanMiddle();
}

PanMiddleCommand::~PanMiddleCommand()
{

}



