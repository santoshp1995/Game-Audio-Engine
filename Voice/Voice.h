#include "XAudio2Wrapper.h"
#include "Handle.h"
#include "WaveData.h"
#include "VoiceID.h"

#ifndef VOICE_H
#define VOICE_H

struct XAUDIO2_BUFFER_ALIAS
{
	UINT32 Flags;                       // Either 0 or XAUDIO2_END_OF_STREAM.
	UINT32 AudioBytes;                  // Size of the audio data buffer in bytes.
	RawData* pAudioData;             // Pointer to the audio data buffer.
	UINT32 PlayBegin;                   // First sample in this buffer to be played.
	UINT32 PlayLength;                  // Length of the region to be played in samples,
										//  or 0 to play the whole buffer.
	UINT32 LoopBegin;                   // First sample of the region to be looped.
	UINT32 LoopLength;                  // Length of the desired loop region in samples,
										//  or 0 to loop the entire buffer.
	UINT32 LoopCount;                   // Number of times to repeat the loop region,
										//  or XAUDIO2_LOOP_INFINITE to loop forever.
	void* pContext;                     // Context value to be passed back in callbacks.
};


class Voice : public DLink
{
public:
	// Big 4
	Voice();
	Voice(const Voice&) = delete;
	Voice& operator = (const Voice&) = delete;
	~Voice();

	Handle::Status Set(VoiceID _id, WaveData* pData);
	Handle::Status Set(VoiceID _id, WaveData* _pWave, IXAudio2VoiceCallback* _pCallback);


	// audio playback functionality (start, stop, pan, pitch, etc...)
	// protection with handles
	Handle::Status Start();
	Handle::Status StartStereo();
	Handle::Status Stop();
	Handle::Status PanMiddle();
	Handle::Status PanRight();
	Handle::Status PanLeft();
	Handle::Status SetVolume(const float vol);
	Handle::Status SetPanning(const float pan);

	Handle::Status Wash();
	Handle::Status Dump();
	Handle::Status GetVoiceId(VoiceID &) const;
	Handle::Status SetVoiceID(VoiceID _id);

	// getters
	Voice* GetNextVoice() const;
	void SetNextVoice(Voice* p);
	const char* GetStringName();
	WaveData* GetWave() const;

	IXAudio2SourceVoice* GetSourceVoice() const;
	IXAudio2VoiceCallback* GetVoiceCallback() const;


private:
	void Clear();

private:
	// TODO:: make private
	XAUDIO2_BUFFER_ALIAS* pBuff;
	IXAudio2VoiceCallback* pCallback;
	IXAudio2SourceVoice* pSourceVoice;
	WaveData* pWave;
	VoiceID id;
	Voice* pNextVoice;
	
	Handle handle;
};


#endif 