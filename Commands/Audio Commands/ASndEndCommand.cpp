#include "ASndEndCommand.h"

ASndEndCommand::ASndEndCommand(SndId _id, Snd* _pSnd)
	:id(_id), pSnd(_pSnd)
{
}

void ASndEndCommand::execute()
{
	assert(this->pSnd);

	// Get the ASnd
	ASnd* pASnd;
	this->pSnd->GetASnd(pASnd);
	assert(pASnd);

	// now end the sound
	pASnd->SndEnd();


}
