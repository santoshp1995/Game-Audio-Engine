#include "ThreadHelper.h"
#include "XAudio2Wrapper.h"
#include "AudioSystemMan.h"
#include "WaveData.h"
#include "FileMan.h"
#include "AsyncFileLoad.h"
#include "SndMan.h"
#include "GFileUserCallback.h"

WaveData::WaveData()
	:
	pRawBuff(nullptr),
	rawBuffSize(0),
	handle(),
	pWfx(nullptr),
	waveId(WaveDataID::UNITILIZED),
	waveStatus(WaveData::Status::UNINITIALIZED),
	pFileUserCallback(nullptr),
	pFileName("UNITILIZED")
{
}

WAVEFORMATEXTENSIBLE* WaveData::GetWfx() const
{
	return this->pWfx;
}

void WaveData::GetWaveID(WaveDataID& _id) const
{
	_id = this->waveId;
}

unsigned int WaveData::GetRawBuffSize() const
{
	return this->rawBuffSize;
}

RawData* WaveData::GetRawBuffer()
{
	return pRawBuff;
}

char* WaveData::GetWaveName()
{
	return pFileName;
}

WaveData::Status WaveData::GetStatus() const
{
	return this->waveStatus;
}

void WaveData::Clear()
{
	// This method... is used in wash to reuse the wave

	// reset fmt
	delete this->pWfx;
	this->pWfx = nullptr;

	delete[] this->pRawBuff;
	this->pRawBuff = nullptr;

	//Wave Data ID
	this->waveId = WaveDataID::UNITILIZED;

	char* pWaveName = "	Uninitialized";
	this->SetName(pWaveName);

}



void WaveData::SetName(const char* const pWaveName)
{
	assert(pWaveName);
	memset(this->pFileName, 0x0, this->size);

	// Quick hack to trim the string before '/
	unsigned int len = strlen(pWaveName);

	const char* pEnd = pWaveName + len;
	const char* pStart = pEnd;

	while (pStart != pWaveName)
	{
		if (*pStart == '/')
		{
			pStart++;
			break;
		}
		pStart--;
	}

	// At this point we have a trimmed name
	strcpy_s(this->pFileName, this->size, pStart);
}


Handle::Status WaveData::Set(const char* const pWaveName, WaveDataID id, FileUserCallback* pFileUserCB)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		assert(pWaveName);

		// Filled when async completed
		this->pWfx = nullptr;
		this->rawBuffSize = 0;
		this->pRawBuff = nullptr;

		this->waveId = id;
		this->waveStatus = WaveData::Status::ASYNC_LOADING;
		this->pFileUserCallback = pFileUserCB;

		this->SetName(pWaveName);

		// Start Async load
		CircularData* pOut = FileMan::GetFileInQueue();
		assert(pOut);

		Command* pCmd = new AsyncFileLoad(pWaveName, waveId);
		assert(pCmd);

		pOut->PushBack(pCmd);
	}
	return lock;
}


Handle::Status WaveData::SetID(WaveDataID id)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		this->waveId = id;
	}

	return lock;
}

Handle::Status WaveData::Dump()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		//Print contents to the debug output window
		Trace::out("   Name: 0x%x (%p) %s\n", this->waveId, this, this->pFileName);
	}

	return lock;
}

Handle::Status WaveData::Wash()
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		// Wash - Clear the entire hierarchy
		DLink::Clear();

		// sub class clear 
		this->Clear();
	}

	return lock;
}

Handle::Status WaveData::Completed(WAVEFORMATEXTENSIBLE* _pWfx, unsigned int _rawBuffSize, RawData* _pRawBuff)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		Trace::out("%s Wave::Completed: \n  waveID:%x, \n  pWfx:%p, \n  rawBuffSize:0x%x, \n  pRawBuff:%p\n",
			ThreadHelper::GetThreadName(), this->waveId, _pWfx, _rawBuffSize, _pRawBuff);

		assert(_pWfx);
		this->pWfx = _pWfx;

		assert(_rawBuffSize > 0);
		this->rawBuffSize = _rawBuffSize;

		assert(_pRawBuff);
		this->pRawBuff = _pRawBuff;

		this->waveStatus = WaveData::Status::READY;


		// Is there a File Callback?
		if (this->pFileUserCallback)
		{
			//// Start Async load
			//CircularData* pOut = SndMan::GetGameInQueue();
			//assert(pOut);

			//Command* pCmd = new GFileUserCallback(this->waveId, this->pFileUserCallback);
			//assert(pCmd);

			//pOut->PushBack(pCmd);

		}
	}
	return lock;
}


WaveData::~WaveData()
{
	delete this->pWfx;
	delete[] this->pRawBuff;	
}
















