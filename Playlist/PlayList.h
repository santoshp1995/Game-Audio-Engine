#ifndef PLAY_LIST_H
#define PLAY_LIST_H

#include "Handle.h"
#include "DLink.h"
#include "WaveData.h"
#include "SndID.h"
#include "Voice.h"


class PLScript
{
	// future implementation
	// command pattern
};


class PlayList : public DLink
{
public:
	// Big Four
	PlayList();
	PlayList(const PlayList&) = delete;
	PlayList& operator = (const PlayList&) = delete;
	virtual ~PlayList();

	Handle::Status Set(SndId snd_id, VoiceID voice_id, WaveDataID wave_id);
	Handle::Status GetID(SndId&) const;
	Handle::Status SetID(SndId);
	Handle::Status Wash();
	Handle::Status Dump();


	// --- Commands --- //
	Handle::Status Play();
	Handle::Status PlayStereo();
	Handle::Status PanMiddle();
	Handle::Status PanRight();
	Handle::Status PanLeft();
	Handle::Status SetVolume(const float vol);
	Handle::Status SetPanning(const float pan);
	Handle::Status Stop();
	Handle::Status SndEnd();

private:
	void Clear();

public:
	// public for now
	// class data
	PLScript* pScript;
	Voice* pVoice;
	SndId id;
	Handle handle;

};


#endif