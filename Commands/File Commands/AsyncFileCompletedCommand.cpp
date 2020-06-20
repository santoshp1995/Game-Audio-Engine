#include "ThreadHelper.h"
#include "AsyncFileCompletedCommand.h"
#include "WaveDataMan.h"

AsyncFileCompletedCommand::AsyncFileCompletedCommand(WaveDataID _waveID, WAVEFORMATEXTENSIBLE* _pWfx, unsigned int _rawBuffSize, RawData* _pRawBuff)
	:
	waveID(_waveID), pWfx(_pWfx), rawBuffSize(_rawBuffSize), pRawBuff(_pRawBuff)
{
}

void AsyncFileCompletedCommand::execute()
{
	Trace::out("%s AAsyncFileCompleted: \n  waveID:%x, \n  pWfx:%p, \n  rawBuffSize:0x%x, \n  pRawBuff:%p\n",
		ThreadHelper::GetThreadName(), waveID, pWfx, rawBuffSize, pRawBuff);

	WaveData* pWave = WaveDataMan::Find(waveID);
	assert(pWave);

	pWave->Completed(this->pWfx, this->rawBuffSize, this->pRawBuff);

}


