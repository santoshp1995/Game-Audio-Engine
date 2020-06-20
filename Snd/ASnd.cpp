#include "ASnd.h"
#include "PlaylistMan.h"
#include "SndMan.h"
#include "ASndMan.h"
#include "UserCallback.h"
#include "VoiceMan.h"

ASnd::ASnd()
	:id(SndId::Uninitialized),
	pPlayList(nullptr),
	pSnd(nullptr),
	handle(),
	pCallback(nullptr)
{
}

ASnd::~ASnd()
{
	this->Clear();
}

Handle::Status ASnd::SetSndID(SndId snd_id)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->id = snd_id;
	}

	return lock;
}

void ASnd::GetSndId(SndId& snd_id) const
{
	snd_id = this->id;
}

Handle::Status ASnd::Set(SndId snd_id)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->pPlayList = PlayListMan::Add(snd_id);
		this->id = snd_id;

		this->pSnd = nullptr;
	}
	return lock;
}

Handle::Status ASnd::Dump()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// Dump - Print contents to the debug output window
		Trace::out("   Name: %d (%p) \n", this->id, this);
	}
	return lock;
}

Handle::Status ASnd::Wash()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		DLink::Clear();

		// Sub class clear
		this->Clear();
	}
	return lock;
}

Handle::Status ASnd::Play()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		assert(this->id != SndId::Uninitialized);
		assert(this->pPlayList);

		// kick the can
		this->pPlayList->Play();
	}

	return lock;
}

Handle::Status ASnd::PlayStereo()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		assert(this->id != SndId::Uninitialized);
		assert(this->pPlayList);

		// kick the can
		this->pPlayList->PlayStereo();
	}

	return lock;
}

Handle::Status ASnd::PanMiddle()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		assert(this->id != SndId::Uninitialized);
		assert(this->pPlayList);

		// kick the can
		this->pPlayList->PanMiddle();

	}

	return lock;
}

Handle::Status ASnd::PanRight()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		assert(this->id != SndId::Uninitialized);
		assert(this->pPlayList);

		// kick the can
		this->pPlayList->PanRight();
	}

	return lock;
}

Handle::Status ASnd::PanLeft()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		assert(this->id != SndId::Uninitialized);
		assert(this->pPlayList);

		// kick the can
		this->pPlayList->PanLeft();
	}

	return lock;
}

Handle::Status ASnd::SetVolume(const float vol)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		assert(this->id != SndId::Uninitialized);
		assert(this->pPlayList);

		// kick the can
		this->pPlayList->SetVolume(vol);
	}

	return lock;
}

Handle::Status ASnd::SetPanning(const float pan)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		assert(this->id != SndId::Uninitialized);
		assert(this->pPlayList);

		// kick the can
		this->pPlayList->SetPanning(pan);
	}

	return lock;
}

Handle::Status ASnd::Stop()
{
	this->pPlayList->Stop();

	// HACK FOR NOW -- CHANGE LATER
	return Handle::Status::SUCCESS;
}

Handle::Status ASnd::SndEnd()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		assert(this->id != SndId::Uninitialized);
		assert(this->pPlayList);

		Trace::out("--------- Snd end() --------------\n");

		// UserCallback?
		if (this->pCallback)
		{
			// HaCK ALERT7
			char* pName = this->pPlayList->pVoice->GetWave()->GetWaveName();
			assert(pName);

			this->pCallback->Set(this->pSnd, pName);
			this->pCallback->OnStreamEnd();
		}


		// Playlist (which will deal with Voice)
		pPlayList->SndEnd();

		// Snd needs to be alerted
		assert(this->pSnd);
		this->pSnd->RemoveFromPriorityTable();
		this->pSnd->SetASnd(nullptr);
		SndMan::Remove(this->pSnd);

		// ASndMan - remove from the active list
		this->pSnd = nullptr;
		ASndMan::Remove(this);

		Snd::PrintPriorityTable();

	}
	return lock;
}

void ASnd::SetSnd(Snd* _pSnd)
{
	assert(_pSnd);

	this->pSnd = _pSnd;
}

Snd* ASnd::GetSnd() const
{
	return this->pSnd;
}

void ASnd::Clear()
{
	this->id = SndId::Uninitialized;
	
	// remove the play list
	if (this->pPlayList)
	{
		PlayListMan::Remove(this->pPlayList);
		this->pPlayList = nullptr;
	}

	delete this->pCallback;
	this->pCallback = nullptr;

	this->pSnd = nullptr;

}



