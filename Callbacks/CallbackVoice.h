#ifndef CALLBACK_VOICE_H
#define CALLBACK_VOICE_H

#include "XAudio2Wrapper.h"
#include "ASnd.h"

// forward declare
//class AudioSystemMan;


//  Sample voice callback
class VoiceCallback : public IXAudio2VoiceCallback
{
public:
	VoiceCallback(const VoiceCallback&) = delete;
	VoiceCallback(VoiceCallback&&) = delete;
	VoiceCallback& operator = (const VoiceCallback&) = delete;
	VoiceCallback& operator = (VoiceCallback&&) = delete;

	VoiceCallback();
	VoiceCallback(const char* const pInName);

	virtual ~VoiceCallback();

	bool IsFinished() const;
	void SetNextVoice(Voice* pVoice);

	void SetASnd(ASnd* _pASnd);
	ASnd* GetASnd() const;

	void STDMETHODCALLTYPE OnStreamEnd() noexcept override;
	void STDMETHODCALLTYPE OnVoiceProcessingPassEnd() noexcept override;
	void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32) noexcept override;
	void STDMETHODCALLTYPE OnBufferEnd(void*) noexcept override;
	void STDMETHODCALLTYPE OnBufferStart(void*) noexcept override;
	void STDMETHODCALLTYPE OnLoopEnd(void*) noexcept override;
	void STDMETHODCALLTYPE OnVoiceError(void*, HRESULT) noexcept override;

	// Data: 
	ASnd* pASnd;
	HANDLE hBufferEndEvent;
	bool   finished = false;
	int	   count = 0;
	Voice* pNextVoice;
	char name[100];


};

#endif
