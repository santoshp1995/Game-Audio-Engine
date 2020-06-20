#include "FileUserCallback.h"
#include "SndMan.h"

void FileUserCallback::Set(const SndId _id)
{
	this->id = _id;
}

void FileUserCallback::Execute()
{
	Trace::out("------------------------------\n");
	Trace::out("  FileUserCallback() \n");
	Trace::out("------------------------------\n");
	Trace::out("     Play(%d)\n", this->id);

	Snd* pSndC;
	pSndC = SndMan::Add(this->id);
	assert(pSndC);

	// Vol & Pan
	assert(pSndC->SetVolume(0.50f) == Handle::Status::SUCCESS);
	assert(pSndC->PanMiddle() == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndC->Play() == Handle::Status::SUCCESS);


	Trace::out("------------------------------\n");
}