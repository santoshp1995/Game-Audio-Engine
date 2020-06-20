#include "AudioSystemMan.h"

AudioSystemMan* AudioSystemMan::privGetInstance()
{
	static AudioSystemMan audioMan;
	return &audioMan;
}

AudioSystemMan::AudioSystemMan()
	:
	pXAudio2(nullptr),
	pSourceVoice(nullptr),
	pMasterVoice(nullptr),
	pVoice(nullptr),
	pan(0.0f),
	volume(0.1f),
	handle()
{
	
}

AudioSystemMan::~AudioSystemMan()
{

}

void AudioSystemMan::Create()
{
	AudioSystemMan* pAudioMan = AudioSystemMan::privGetInstance();
	assert(pAudioMan);
}

void AudioSystemMan::InitializeXAudio2()
{

	AudioSystemMan* pAudioMan = privGetInstance();
	assert(pAudioMan);

	// Initializes the COM library for use by the calling thread
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// -------------------------------------------------------
	// Create an instance, use its default processor
	// -------------------------------------------------------
	HRESULT hr;

	if (FAILED(hr = XAudio2Create(&pAudioMan->pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
	{
		printf("error %x", (unsigned int)hr);
		assert(false);
	}

	// -------------------------------------------------------
	// Creating a master voice, with default settings:
	//
	//      InputChannels = XAUDIO2_DEFAULT_CHANNELS,
	//      InputSampleRate = XAUDIO2_DEFAULT_SAMPLERATE,
	//      Flags = 0,
	//      szDeviceId = NULL,
	//      *pEffectChain = NULL,
	//      StreamCategory = AudioCategory_GameEffects
	// -------------------------------------------------------

	if (FAILED(hr = pAudioMan->pXAudio2->CreateMasteringVoice(&pAudioMan->pMasterVoice)))
	{
		printf("error %x", hr);
		assert(false);
	}
}

void AudioSystemMan::Destroy()
{
	AudioSystemMan* pAudioMan = AudioSystemMan::privGetInstance();
	assert(pAudioMan);

	//pAudioMan->pSourceVoice->DestroyVoice();
	pAudioMan->pMasterVoice->DestroyVoice();
	pAudioMan->pXAudio2->Release();

	CoUninitialize();
}

void AudioSystemMan::CallSound(CircularData* pOut, WAVEFORMATEXTENSIBLE& wfx, XAUDIO2_BUFFER& buffer)
{
	AudioSystemMan* pAudioMan = AudioSystemMan::privGetInstance();
	assert(pAudioMan);

	HRESULT hr;
	// -------------------------------------------------------
	// Create a source voice
	//		Format in wfx
	// -------------------------------------------------------

	UNUSED_VAR(wfx);

	// Create a Callback object!!!
	//pAudioMan->pCallback = new VoiceCallback();
	
	//hr = pAudioMan->pXAudio2->CreateSourceVoice(&pAudioMan->pSourceVoice, (WAVEFORMATEX*)& wfx, 0, 2.0f, 
	//	pAudioMan->pCallback);
	//assert(hr == S_OK);

	// -------------------------------------------------------
	// Create a move the voice onto the voice queue
	//		Only files on the queue can be played
	//		There is no deep copy, we still hold the buffer while its active
	// -------------------------------------------------------

	if (FAILED(hr = pAudioMan->pSourceVoice->SubmitSourceBuffer(&buffer)))
	{
		assert(false);
	}

	// -------------------------------------------------------
	// Start the source voice
	// -------------------------------------------------------
	 pAudioMan->pSourceVoice->SetVolume(0.1f);
	if (FAILED(hr = pAudioMan->pSourceVoice->Start(0)))
	{
		assert(false);
	}


	//while (!pAudioMan->pCallback->IsFinished())
	//{
	//	// spin until down
	//}

	pAudioMan->pSourceVoice->Stop();

	UNUSED_VAR(pOut);
}

void AudioSystemMan::StopSound(IXAudio2SourceVoice* pSource)
{
	HRESULT hr;

	if (FAILED(hr = pSource->Stop(0)))
	{
		assert(false);
	}
}

void AudioSystemMan::VolumeUp(const float vol)
{
	AudioSystemMan* pAudioMan = AudioSystemMan::privGetInstance();
	assert(pAudioMan);

	float newVol = pAudioMan->volume + vol;

	pAudioMan->pMasterVoice->SetVolume(newVol);
}

void AudioSystemMan::VolumeDown(const float vol)
{
	AudioSystemMan* pAudioMan = AudioSystemMan::privGetInstance();
	assert(pAudioMan);

	float newVol = pAudioMan->volume - vol;

	pAudioMan->pMasterVoice->SetVolume(newVol);
}


IXAudio2SourceVoice* AudioSystemMan::GetSourceVoice()
{
	AudioSystemMan* pAudioMan = AudioSystemMan::privGetInstance();
	assert(pAudioMan);

	return pAudioMan->pSourceVoice;
}

IXAudio2MasteringVoice* AudioSystemMan::GetMasterVoice()
{
	AudioSystemMan* pAudioMan = AudioSystemMan::privGetInstance();
	assert(pAudioMan);


	return pAudioMan->pMasterVoice;
}

void AudioSystemMan::CreateSourceVoice(IXAudio2SourceVoice*& pSource, WAVEFORMATEXTENSIBLE* wfx, IXAudio2VoiceCallback* pCallback)
{
	assert(wfx);
	

	AudioSystemMan* pAudioMan = AudioSystemMan::privGetInstance();
	assert(pAudioMan);

	if (pAudioMan->pXAudio2->CreateSourceVoice(&pSource, (WAVEFORMATEX*)wfx, 0, XAUDIO2_MAX_FREQ_RATIO, pCallback))
	{
		assert(false);
	}
}

void AudioSystemMan::SubmitSourceBuffer(IXAudio2SourceVoice* pSource, XAUDIO2_BUFFER* pBuffer)
{
	assert(pSource);
	assert(pBuffer);

	pBuffer->Flags = XAUDIO2_END_OF_STREAM;
	if (pSource->SubmitSourceBuffer(pBuffer))
	{
		assert(false);
	}
}

void AudioSystemMan::StartVoice(IXAudio2SourceVoice* pSource)
{
	HRESULT hr;

	if (FAILED(hr = pSource->Start(0)))
	{
		assert(false);
	}

}

void AudioSystemMan::ChangePan(IXAudio2MasteringVoice& masterVoice, IXAudio2SourceVoice& sourceVoice, float pan)
{
	AudioSystemMan* pAudioMan = AudioSystemMan::privGetInstance();
	assert(pAudioMan);

	pAudioMan->pan = pan;

	DWORD dwChannelMask;

	masterVoice.GetChannelMask(&dwChannelMask);

	float outputMatrix[8];

	for (int i = 0; i < 8; i++)
		outputMatrix[i] = 0;

	// pan of -1.0 indicates all left speaker, 
	// 1.0 is all right speaker, 0.0 is split between left and right
	float left = 0.5f - pAudioMan->pan / 2;
	float right = 0.5f + pAudioMan->pan / 2;

	switch (dwChannelMask)
	{
	case KSAUDIO_SPEAKER_MONO:
		outputMatrix[0] = 1.0f;
		break;
	
	case KSAUDIO_SPEAKER_STEREO:
		outputMatrix[0] = left;
		outputMatrix[1] = right;
		break;

	case KSAUDIO_SPEAKER_2POINT1:
	case KSAUDIO_SPEAKER_SURROUND:
		outputMatrix[0] = left;
		outputMatrix[1] = right;
		break;
	case KSAUDIO_SPEAKER_QUAD:
		outputMatrix[0] = outputMatrix[2] = left;
		outputMatrix[1] = outputMatrix[3] = right;
		break;

	case KSAUDIO_SPEAKER_5POINT1:
	case KSAUDIO_SPEAKER_7POINT1:

	case KSAUDIO_SPEAKER_5POINT1_SURROUND:
		outputMatrix[0] = outputMatrix[4] = left;
		outputMatrix[1] = outputMatrix[5] = right;
		break;

	case KSAUDIO_SPEAKER_7POINT1_SURROUND:
		outputMatrix[0] = outputMatrix[4] = outputMatrix[6] = left;
		outputMatrix[1] = outputMatrix[5] = outputMatrix[7] = right;
		break;
	}

	// assuming Voice sends to master voice
	XAUDIO2_VOICE_DETAILS VoiceDetails;
	sourceVoice.GetVoiceDetails(&VoiceDetails);

	XAUDIO2_VOICE_DETAILS MasterVoiceDetails;
	masterVoice.GetVoiceDetails(&MasterVoiceDetails);

	sourceVoice.SetOutputMatrix(nullptr, VoiceDetails.InputChannels, MasterVoiceDetails.InputChannels, outputMatrix);
}

void AudioSystemMan::SetVolume(IXAudio2SourceVoice* sourceVoice, const float vol)
{
	sourceVoice->SetVolume(vol);
}

void AudioSystemMan::SetCurrentVoice(Voice* pSource, float pan)
{
	AudioSystemMan* pAudioMan = AudioSystemMan::privGetInstance();
	assert(pAudioMan);

	pAudioMan->pVoice = pSource;

	pAudioMan->pSourceVoice = pSource->GetSourceVoice();

	pAudioMan->pan = pan;

	pAudioMan->ChangePan(*pAudioMan->pMasterVoice, *pAudioMan->pSourceVoice, pAudioMan->pan);
}

void AudioSystemMan::SetCurrentVoice(Voice* pSource)
{
	AudioSystemMan* pAudioMan = AudioSystemMan::privGetInstance();
	assert(pAudioMan);

	pAudioMan->pVoice = pSource;

	pAudioMan->pSourceVoice = pSource->GetSourceVoice();
}

IXAudio2SourceVoice* AudioSystemMan::GetCurrentSourceVoice()
{
	AudioSystemMan* pAudioMan = AudioSystemMan::privGetInstance();
	assert(pAudioMan);

	return pAudioMan->pSourceVoice;
}

float AudioSystemMan::GetCurrentPan()
{
	AudioSystemMan* pAudioMan = AudioSystemMan::privGetInstance();
	assert(pAudioMan);

	return pAudioMan->pan;
}

IXAudio2* AudioSystemMan::GetXAudio2()
{
	AudioSystemMan* pAudioMan = AudioSystemMan::privGetInstance();
	assert(pAudioMan);

	return pAudioMan->pXAudio2;
}

Voice* AudioSystemMan::GetActiveVoice()
{
	AudioSystemMan* pAudioMan = AudioSystemMan::privGetInstance();
	assert(pAudioMan);

	return pAudioMan->pVoice;
}








