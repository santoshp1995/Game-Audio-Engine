
#include "XAudio2Wrapper.h"

#include "AudioSystemMan.h"
#include "Voice.h"
#include "VoiceID.h"
#include "CallbackVoice.h"

struct VoiceNameTable
{
	VoiceID id;
	const char* pString;
};

VoiceNameTable table[] =
{
	{ VoiceID::Fiddle, "Fiddle" },
	{ VoiceID::Bassoon, "Bassoon" },
	{VoiceID::Calliope, "Calliope" },
	{ VoiceID::Oboe, "Oboe" },
	{VoiceID::SongA, "SongA" },
	{ VoiceID::SongB, "SongB" },
	{ VoiceID::Unitilized, "Uninitialized"}
};

#define VoiceTableCount  (sizeof(table) / sizeof(table[0]))

Voice::Voice()
	: pBuff(nullptr),
	pCallback(nullptr),
	pSourceVoice(nullptr),
	pWave(nullptr),
	id(VoiceID::Unitilized),
	handle()
{
	// nothing dynamic...

	// Pattern:
	//    Manager calls default wave
	//    set(...)  dynamic allocation
	//    privClear(...) release dynamic allocation
	//    destructor release of any owned objects
}

Handle::Status Voice::Set(VoiceID _id, WaveData* _pWave)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// set id
		this->id = _id;

		// Set the wave pointer
		assert(_pWave);
		this->pWave = _pWave;

		// Create a voice callback
		this->pCallback = new VoiceCallback();
		assert(this->pCallback);

		// create and setup xaudio2 buffer
		this->pBuff = new XAUDIO2_BUFFER_ALIAS();
		assert(this->pBuff);

		// Set the Buffer info...
		*this->pBuff = { 0 };	  // zeros out the complete structure
		this->pBuff->AudioBytes = pWave->GetRawBuffSize();  //buffer containing audio data
		this->pBuff->pAudioData = pWave->GetRawBuffer();  //size of the audio buffer in bytes
		assert(pWave->GetRawBuffer());

		this->pBuff->Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer
		this->pBuff->LoopCount = 0;


		// Get XAudio2 from manager
		IXAudio2* pXAudio2 = AudioSystemMan::GetXAudio2();
		assert(pXAudio2);

		// Create Source Voice
		this->pSourceVoice = nullptr;
		AudioSystemMan::CreateSourceVoice(this->pSourceVoice, this->pWave->GetWfx(), this->pCallback);

		// Submit it
		AudioSystemMan::SubmitSourceBuffer(this->pSourceVoice, (XAUDIO2_BUFFER*)this->pBuff);
	}
	return lock;
}

Handle::Status Voice::Set(VoiceID _id, WaveData* _pWave, IXAudio2VoiceCallback* _pCallback)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// set id
		this->id = _id;

		// Set the wave pointer
		assert(_pWave);
		this->pWave = _pWave;

		// Create a voice callback
		this->pCallback = _pCallback;
		assert(this->pCallback);

		// create and setup xaudio2 buffer
		this->pBuff = new XAUDIO2_BUFFER_ALIAS();
		assert(this->pBuff);

		// Set the Buffer info...
		*this->pBuff = { 0 };	  // zeros out the complete structure
		this->pBuff->AudioBytes = pWave->GetRawBuffSize();  //buffer containing audio data
		this->pBuff->pAudioData = pWave->GetRawBuffer();  //size of the audio buffer in bytes
		assert(pWave->GetRawBuffer());

		this->pBuff->Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer
		this->pBuff->LoopCount = 0;


		// Get XAudio2 from manager
		IXAudio2* pXAudio2 = AudioSystemMan::GetXAudio2();
		assert(pXAudio2);

		// Create Source Voice
		this->pSourceVoice = nullptr;
		AudioSystemMan::CreateSourceVoice(this->pSourceVoice, this->pWave->GetWfx(), this->pCallback);

		// Submit it
		AudioSystemMan::SubmitSourceBuffer(this->pSourceVoice, (XAUDIO2_BUFFER*)this->pBuff);
	}
	return lock;
}

Voice::~Voice()
{
	// ------------------------------------------------------------------------
	//   Handle is invalidated automatically - through ~handle() destructor
	// ------------------------------------------------------------------------
	this->Clear();

	// check "this" and input
	assert(Handle::ValidateHandle(this->handle) == Handle::Status::SUCCESS);
}

Handle::Status Voice::Start()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		AudioSystemMan::SetCurrentVoice(this, AudioSystemMan::GetCurrentPan());
		AudioSystemMan::StartVoice(this->pSourceVoice);
	}
	return lock;
}

Handle::Status Voice::StartStereo()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		AudioSystemMan::SetCurrentVoice(this);
		AudioSystemMan::StartVoice(this->pSourceVoice);
	}

	return lock;
}

Handle::Status Voice::Stop()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		AudioSystemMan::StopSound(this->pSourceVoice);
	}
	return lock;
}

Handle::Status Voice::SetVolume(float snd_vol)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		AudioSystemMan::SetVolume(this->pSourceVoice, snd_vol);
	}
	return lock;
}

Handle::Status Voice::SetPanning(const float pan)
{
	UNUSED_VAR(pan);

	return Handle::Status::SUCCESS;
}

Handle::Status Voice::PanMiddle()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		AudioSystemMan::ChangePan(*AudioSystemMan::GetMasterVoice(), *this->GetSourceVoice(), 0.0f);
	}

	return lock;
}

Handle::Status Voice::PanRight()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		AudioSystemMan::ChangePan(*AudioSystemMan::GetMasterVoice(), *this->GetSourceVoice(), 1.0f);
	}

	return lock;

}

Handle::Status Voice::PanLeft()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		AudioSystemMan::ChangePan(*AudioSystemMan::GetMasterVoice(), *this->GetSourceVoice(), -1.0f);
	}

	return lock;
}

Handle::Status Voice::GetVoiceId(VoiceID& _id) const
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		_id = this->id;
	}
	return lock;
}

Voice* Voice::GetNextVoice() const
{
	return this->pNextVoice;
}

void Voice::SetNextVoice(Voice* p)
{
	this->pNextVoice = p;
}

const char* Voice::GetStringName()
{
	const char* p = "NOT_FOUND";
	const char* pTmp = p;

	for (int i = 0; i < VoiceTableCount; i++)
	{
		if (this->id == table[i].id)
		{
			pTmp = table[i].pString;
			break;
		}
	}

	return pTmp;
}

WaveData* Voice::GetWave() const
{
	return this->pWave;
}

IXAudio2SourceVoice* Voice::GetSourceVoice() const
{
	return this->pSourceVoice;
}

IXAudio2VoiceCallback* Voice::GetVoiceCallback() const
{
	return this->pCallback;
}

Handle::Status Voice::SetVoiceID(VoiceID _id)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		this->id = _id;
	}
	return lock;
}

void Voice::Clear()
{
	if (this->pSourceVoice)
	{
		// in case it was playing... 
		this->pSourceVoice->Stop();

		// Voice was initialized in XAudio2... so its destroyed there
		this->pSourceVoice->DestroyVoice();
	}
	this->pSourceVoice = nullptr;

	delete this->pBuff;
	this->pBuff = nullptr;

	// New warning C5205 warning... problem its in <xaudio2.h>
	free(this->pCallback);
	this->pCallback = nullptr;
}

Handle::Status Voice::Wash()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// Wash - clear the entire hierarchy
		DLink::Clear();

		// Sub class clear
		this->Clear();
	}
	return lock;
}

Handle::Status Voice::Dump()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// Dump - Print contents to the debug output window
		Trace::out("   Name: %s (%p) \n", this->GetStringName(), this);
	}
	return lock;
}

// --- End of File ---





