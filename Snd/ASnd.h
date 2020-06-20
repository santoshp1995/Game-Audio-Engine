#ifndef A_SND_H
#define A_SND_H

#include "DLink.h"
#include "SndID.h"
#include "Handle.h"
#include "PlayList.h"

class UserCallback;
class Snd;


class ASnd : public DLink
{
public:
	ASnd();
	ASnd(const ASnd&) = delete;
	ASnd& operator= (const ASnd&) = delete;
	~ASnd();

	Handle::Status SetSndID(SndId snd_id);
	void GetSndId(SndId& snd_id) const;

	Handle::Status Set(SndId snd_id);

	Handle::Status Dump();
	Handle::Status Wash();

	// --- Commands ---
	Handle::Status Play();
	Handle::Status PlayStereo();
	Handle::Status PanMiddle();
	Handle::Status PanRight();
	Handle::Status PanLeft();
	Handle::Status SetVolume(const float vol);
	Handle::Status SetPanning(const float pan);
	Handle::Status Stop();
	Handle::Status SndEnd();
	void SetSnd(Snd* pSnd);
	Snd* GetSnd() const;


private:
	void Clear();

	// TODO make private
public:
	SndId id;
	PlayList* pPlayList;
	Snd* pSnd;
	Handle handle;
	UserCallback* pCallback;
};


#endif
