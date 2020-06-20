#ifndef ASYNC_FILE_LOAD_H
#define ASYNC_FILE_LOAD_H

#include "FileLoadCommand.h"
#include "FileUserCallback.h"
#include "WaveData.h"

class AsyncFileLoad : public FileCommand
{
public:
	AsyncFileLoad() = delete;
	AsyncFileLoad(const AsyncFileLoad&) = delete;
	AsyncFileLoad& operator= (const AsyncFileLoad&) = delete;
	~AsyncFileLoad() = default;


	AsyncFileLoad(const char* const pWaveName, WaveDataID name);
	virtual void execute() override;

private:
	void privLoadBuffer(const char* const pWaveName, WAVEFORMATEXTENSIBLE*& pWfx, RawData*& pRawBuff, unsigned int RawBuffSize);
	unsigned int privGetBuffSize(const char* const pWaveName);

public:
	WaveDataID waveID;
	const char* const	pWaveName;

};


#endif