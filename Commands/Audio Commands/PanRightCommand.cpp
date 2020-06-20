#include "PanRightCommand.h"
#include "ASnd.h"

PanRightCommand::PanRightCommand(Voice* voice)
{
	this->pVoice = voice;
}

PanRightCommand::PanRightCommand(SndId _id, Snd* _pSnd)
	:id(_id),
	pSnd(_pSnd)
{
}

void PanRightCommand::execute()
{
	// make sure pSnd was created
	assert(this->pSnd);

	// Get the ASnd
	ASnd* pASnd;
	this->pSnd->GetASnd(pASnd);
	//assert(this->pSnd->GetASnd(pASnd) == Handle::Status::SUCCESS);

	// now change it's attributes
	pASnd->PanRight();
}

PanRightCommand::~PanRightCommand()
{
}


