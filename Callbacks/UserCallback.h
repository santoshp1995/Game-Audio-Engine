#ifndef USER_CALLBACK_H
#define USER_CALLBACK_H

#include "Snd.h"
#include "CallbackVoice.h"

class UserCallback : public VoiceCallback
{
public:
	UserCallback() = default;
	UserCallback(const UserCallback&) = delete;
	UserCallback& operator= (const UserCallback&) = delete;
	~UserCallback() = default;

	void STDMETHODCALLTYPE OnStreamEnd() noexcept override;
	void STDMETHODCALLTYPE OnVoiceProcessingPassEnd() noexcept override;
	void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32) noexcept override;
	void STDMETHODCALLTYPE OnBufferEnd(void*) noexcept override;
	void STDMETHODCALLTYPE OnBufferStart(void*) noexcept override;
	void STDMETHODCALLTYPE OnLoopEnd(void*) noexcept override;
	void STDMETHODCALLTYPE OnVoiceError(void*, HRESULT) noexcept override;

	void Set(Snd* _pSnd, char* _pWaveName);
	

private:
	Snd* pSnd;
	char* pWaveName;
};


#endif