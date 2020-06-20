#include "UserCallback.h"
#include "Snd.h"

void UserCallback::Set(Snd* _pSnd, char* _pWaveName)
{
	assert(_pSnd);
	this->pSnd = _pSnd;

	assert(_pWaveName);
	this->pWaveName = _pWaveName;
}

void __stdcall UserCallback::OnStreamEnd() noexcept
{
	assert(this->pSnd);
	assert(this->pWaveName);

	Trace::out("------------------------------\n");
	Trace::out("  UserCallback() \n");

	SndId id;
	this->pSnd->GetID(id);

	Trace::out("      SndID: %d \n", id);

	int timeInMS;
	this->pSnd->GetTimeInMS(timeInMS);
	Trace::out("       Time: %d ms \n", timeInMS);

	float pan;
	this->pSnd->GetPan(pan);
	Trace::out("        Pan: %f  \n", pan);

	Trace::out("       Wave: %s  \n", this->pWaveName);

	Trace::out("------------------------------\n");

}

void __stdcall UserCallback::OnVoiceProcessingPassEnd() noexcept
{
}

void __stdcall UserCallback::OnVoiceProcessingPassStart(UINT32) noexcept
{
}

void __stdcall UserCallback::OnBufferEnd(void*) noexcept
{
}

void __stdcall UserCallback::OnBufferStart(void*) noexcept
{
}

void __stdcall UserCallback::OnLoopEnd(void*) noexcept
{
}

void __stdcall UserCallback::OnVoiceError(void*, HRESULT) noexcept
{
}
