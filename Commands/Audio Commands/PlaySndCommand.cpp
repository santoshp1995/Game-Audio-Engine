#include "PlaySndCommand.h"
#include "ASndMan.h"

PlaySndCommand::~PlaySndCommand()
{
}

PlaySndCommand::PlaySndCommand(SndId _id, Snd* _pSnd)
	:
	id(_id),
	pSnd(_pSnd)
{
}

void PlaySndCommand::execute()
{
	// make sure pSnd is valid
	assert(this->pSnd);

	// Get the Asnd
	ASnd* pASnd;
	this->pSnd->GetASnd(pASnd);
	//assert(this->pSnd->GetASnd(pASnd) == Handle::Status::SUCCESS);
	assert(pASnd);

	if (this->id == SndId::Beethoven)
	{
		pASnd->PlayStereo();

		return;
	}


	// play it
	pASnd->Play();
}




