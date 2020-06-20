#include "GFileUserCallback.h"
#include "ThreadHelper.h"
#include "SndMan.h"

GFileUserCallback::GFileUserCallback(WaveDataID _name, FileUserCallback* _pFileCB)
	: wave_id(_name), pFileCB(_pFileCB)
{
	assert(this->pFileCB);
}

void GFileUserCallback::execute()
{
	Trace::out("%s GFileUserCallback: \n  waveID:%x,\n  callback:%p \n", ThreadHelper::GetThreadName(), this->wave_id, this->pFileCB);
	this->pFileCB->Execute();

	delete this->pFileCB;
}