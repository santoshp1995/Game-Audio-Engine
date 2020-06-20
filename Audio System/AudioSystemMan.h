#ifndef AUDIO_SYSTEM_MAN
#define AUDIO_SYSTEM_MAN

#include "ks.h"
#include "ksmedia.h"
#include "XAudio2Wrapper.h"
#include "CircularData.h"
#include "BufferMan.h"
#include "Voice.h"

// forward declare
class VoiceCallback;

class AudioSystemMan
{
	friend class VoiceCallback;

public:
	static const unsigned int size = 10000;


	AudioSystemMan(const AudioSystemMan&) = delete;
	const AudioSystemMan& operator=(const AudioSystemMan&) = delete;
	~AudioSystemMan();

	static void Create();
	static void InitializeXAudio2();
	static void Destroy(); 
	static void CallSound(CircularData* pOut, WAVEFORMATEXTENSIBLE& wfx, XAUDIO2_BUFFER& buffer);
	static void StopSound(IXAudio2SourceVoice* pSource);
	static void VolumeUp(const float vol);
	static void VolumeDown(const float vol);
	static IXAudio2SourceVoice* GetSourceVoice();
	static IXAudio2MasteringVoice* GetMasterVoice();
	static void CreateSourceVoice(IXAudio2SourceVoice*& pSource, WAVEFORMATEXTENSIBLE* wfx, IXAudio2VoiceCallback* pCallback);
	static void SubmitSourceBuffer(IXAudio2SourceVoice* pSource, XAUDIO2_BUFFER* pBuffer);
	static void StartVoice(IXAudio2SourceVoice* pSource);
	static void ChangePan(IXAudio2MasteringVoice& masterVoice, IXAudio2SourceVoice& sourceVoice, float pan);
	static void SetVolume(IXAudio2SourceVoice* sourceVoice, const float vol);
	static void SetCurrentVoice(Voice* pSource, float pan);
	static void SetCurrentVoice(Voice* pSource);
	static IXAudio2SourceVoice* GetCurrentSourceVoice();
	static float GetCurrentPan();
	static IXAudio2* GetXAudio2();
	static Voice* GetActiveVoice();


private:
	static AudioSystemMan* privGetInstance();
	AudioSystemMan();


	// private data
	IXAudio2* pXAudio2;
	IXAudio2MasteringVoice* pMasterVoice;
	IXAudio2SourceVoice* pSourceVoice;
	Voice* pVoice;
	float pan;
	float volume;
	Handle handle;


};



#endif