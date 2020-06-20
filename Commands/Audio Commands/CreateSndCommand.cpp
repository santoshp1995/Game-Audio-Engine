#include "CreateSndCommand.h"
#include "ASndMan.h"
#include "CallbackVoice.h"

CreateSndCommand::CreateSndCommand(SndId _id, Snd* _pSnd, UserCallback* _pUserCallback)
	:id(_id),
	pSnd(_pSnd),
	pUserCallback(_pUserCallback)
{
}

void CreateSndCommand::execute()
{
	if (pUserCallback == nullptr)
	{
		assert(this->id != SndId::Uninitialized);

		ASnd* pASnd = ASndMan::Add(this->id);
		assert(pASnd);

		// update the snd call
		assert(this->pSnd);
		pSnd->SetASnd(pASnd);
	}

	
	else
	{
		assert(this->id != SndId::Uninitialized);

		ASnd* pA = ASndMan::Add(this->id);
		assert(pA);

		// Update the SND call
		// This way its faster to execute commands on the Audio thread side

		assert(this->pSnd);
		pSnd->SetASnd(pA);
		pA->SetSnd(pSnd);

		// user callback
		pA->pCallback = this->pUserCallback;

		// Set the ASnd pointer in the VoiceCallback - HACK
		// Not sure if this is the best place for this...
		PlayList* pPlaylist = pA->pPlayList;
		assert(pPlaylist);

		Voice* pVoice = pPlaylist->pVoice;
		assert(pVoice);
		//pVoice->GetVoiceCallback();

		// OK to down cast this... might want to change voice.h to use VoiceCallback
		VoiceCallback* pCallback = (VoiceCallback*)pVoice->GetVoiceCallback();
		assert(pCallback);

		if (pCallback != nullptr)
		{
			pCallback->SetASnd(pA);
		}
	}
}
