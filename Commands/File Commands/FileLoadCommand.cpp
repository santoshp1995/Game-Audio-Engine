#include "ThreadHelper.h"
#include "FileLoadCommand.h"
#include "WaveDataMan.h"

FileLoadCommand::FileLoadCommand(const char* const _pWaveName, WaveDataID name, FileUserCallback* pFileCB)
	: pFileUserCallback(pFileCB),
	waveID(name),
	pWaveName(_pWaveName)
{
}

void FileLoadCommand::execute()
{
	Trace::out("%s AFileLoad: \n  callback:%p, \n  waveID:%x, \n  wavename:%s \n", ThreadHelper::GetThreadName(), pFileUserCallback, waveID, pWaveName);

	WaveDataMan::Add(pWaveName, waveID, pFileUserCallback);

}


