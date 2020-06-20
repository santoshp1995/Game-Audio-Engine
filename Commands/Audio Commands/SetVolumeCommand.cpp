#include "SetVolumeCommand.h"
#include "ASnd.h"

SetVolumeCommand::SetVolumeCommand(Voice* voice, float volume)
{
	this->pVoice = voice;
	this->vol = volume;
}

SetVolumeCommand::SetVolumeCommand(SndId _id, Snd* _pSnd, const float _vol)
	:id(_id),
	pSnd(_pSnd),
	vol(_vol)
{
}

void SetVolumeCommand::execute()
{
	// make sure snd has been set
	assert(this->pSnd);

	// Get the ASnd
	ASnd* pASnd;
	this->pSnd->GetASnd(pASnd);
	//assert(this->pSnd->GetASnd(pASnd) == Handle::Status::SUCCESS);

	// now change it's attributes
	pASnd->SetVolume(this->vol);
}

SetVolumeCommand::~SetVolumeCommand()
{

}



