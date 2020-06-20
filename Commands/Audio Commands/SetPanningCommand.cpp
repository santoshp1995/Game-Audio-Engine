#include "SetPanningCommand.h"
#include "ASnd.h"

SetPanningCommand::SetPanningCommand(SndId _id, Snd* _pSnd, float _pan)
	:
	id(_id),
	pSnd(_pSnd),
	pan(_pan)
{
}

void SetPanningCommand::execute()
{
	// make sure snd has been set
	assert(this->pSnd);

	// Get the ASnd
	ASnd* pASnd;
	this->pSnd->GetASnd(pASnd);

	// now change it's attributes
	pASnd->SetPanning(this->pan);
}

SetPanningCommand::~SetPanningCommand()
{

}

