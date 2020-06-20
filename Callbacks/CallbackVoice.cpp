#include "VoiceCallback.h"
#include "ACommandQueue.h"
#include "ASndMan.h"
#include "SndMan.h"
#include "CallbackVoice.h"
#include "AudioSystemMan.h"

VoiceCallback::VoiceCallback()
	:pASnd(nullptr),
	hBufferEndEvent(CreateEvent(0, FALSE, FALSE, 0)),
	finished(true),
	count(0),
	pNextVoice(nullptr)
{
}

VoiceCallback::VoiceCallback(const char* const pInName)
	:pASnd(nullptr),
	hBufferEndEvent(CreateEvent(0, FALSE, FALSE, 0)),
	finished(false),
	count(0),
	pNextVoice(nullptr)
{
	strcpy_s(this->name, 100, pInName);
}

VoiceCallback::~VoiceCallback()
{
	memset(this->name, 0, 100);
	CloseHandle(hBufferEndEvent);
}

void VoiceCallback::SetASnd(ASnd* _pASnd)
{
	this->pASnd = _pASnd;
}

ASnd* VoiceCallback::GetASnd() const
{
	return this->pASnd;
}

void __stdcall VoiceCallback::OnStreamEnd() noexcept
{
	// Send a command and leave
	if (this->pASnd != nullptr)
	{
		ACommandQueue::SndEnd(this->pASnd);
	}


	if (this->pNextVoice != nullptr)
	{
		AudioSystemMan::SetCurrentVoice(this->pNextVoice, AudioSystemMan::GetCurrentPan());

		this->pNextVoice->Start();
	}
	else
	{
		this->finished = true;
	}
}

bool VoiceCallback::IsFinished() const
{
	return this->finished;
}

void VoiceCallback::SetNextVoice(Voice* pVoice)
{
	this->pNextVoice = pVoice;
}

void __stdcall VoiceCallback::OnVoiceProcessingPassEnd() noexcept
{
}

void __stdcall VoiceCallback::OnVoiceProcessingPassStart(UINT32) noexcept
{
}

void __stdcall VoiceCallback::OnBufferEnd(void*) noexcept
{
}

void __stdcall VoiceCallback::OnBufferStart(void*) noexcept
{
	if (!finished)
	{
		Trace::out("Playing %s\n", this->name);
	}

}

void __stdcall VoiceCallback::OnLoopEnd(void*) noexcept
{
}

void __stdcall VoiceCallback::OnVoiceError(void*, HRESULT) noexcept
{
}





