#include "XAudio2Wrapper.h"
#include "AudioSystemMan.h"
#include "PlayList.h"
#include "VoiceMan.h"


PlayList::PlayList()
	:
	pScript(nullptr),
	pVoice(nullptr),
	id(SndId::Uninitialized),
	handle()
{
}

PlayList::~PlayList()
{
	assert(Handle::ValidateHandle(this->handle) == Handle::Status::SUCCESS);
}

Handle::Status PlayList::Set(SndId snd_id, VoiceID voice_id, WaveDataID wave_id)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->id = snd_id;

		this->pVoice = VoiceMan::Add(voice_id, wave_id);

		assert(this->pVoice);
	}

	return lock;

}

Handle::Status PlayList::GetID(SndId& _id) const
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		_id = this->id;
	}

	return lock;

}

Handle::Status PlayList::SetID(SndId _id)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->id = _id;
	}

	return lock;
}

Handle::Status PlayList::Wash()
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

Handle::Status PlayList::Dump()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// Dump - Print contents to the debug output window
		Trace::out("   Name: %d (%p) \n", this->id, this);
	}
	return lock;
}

Handle::Status PlayList::Play()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		assert(this->id != SndId::Uninitialized);
		assert(this->pVoice);

		this->pVoice->Start();
	}

	return lock;
}

Handle::Status PlayList::PlayStereo()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		assert(this->id != SndId::Uninitialized);
		assert(this->pVoice);

		this->pVoice->StartStereo();
	}

	return lock;
}

Handle::Status PlayList::PanMiddle()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		assert(this->id != SndId::Uninitialized);
		assert(this->pVoice);

		this->pVoice->PanMiddle();
	}

	return lock;
}

Handle::Status PlayList::PanRight()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		assert(this->id != SndId::Uninitialized);
		assert(this->pVoice);

		this->pVoice->PanRight();
	}

	return lock;
}

Handle::Status PlayList::PanLeft()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		assert(this->id != SndId::Uninitialized);
		assert(this->pVoice);

		this->pVoice->PanLeft();
	}

	return lock;
}

Handle::Status PlayList::SetVolume(const float vol)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		assert(this->id != SndId::Uninitialized);
		assert(this->pVoice);

		this->pVoice->SetVolume(vol);
	}

	return lock;
}

Handle::Status PlayList::SetPanning(const float pan)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		assert(this->id != SndId::Uninitialized);
		assert(this->pVoice);

		this->pVoice->SetPanning(pan);
	}

	return lock;
}

Handle::Status PlayList::Stop()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		assert(this->id != SndId::Uninitialized);
		assert(this->pVoice);

		this->pVoice->Stop();
	}

	return lock;
}

Handle::Status PlayList::SndEnd()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		assert(this->id != SndId::Uninitialized);
		assert(this->pVoice);

		// stop voice if not already stopped
		this->pVoice->Stop();

		// now remove it off the active list
		VoiceMan::Remove(this->pVoice);
	}
	return lock;
}

void PlayList::Clear()
{
	this->pVoice = nullptr;

	// Command pattern
	this->pScript = nullptr;

	this->id = SndId::Uninitialized;

}














