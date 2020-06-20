#ifndef ASYNC_FILE_COMPLETED_COMMAND_H
#define ASYNC_FILE_COMPLETED_COMMAND_H

#include "FileCommand.h"
#include "FileUserCallback.h"
#include "WaveData.h"

class AsyncFileCompletedCommand : public FileCommand
{
public:
	AsyncFileCompletedCommand() = delete;
	AsyncFileCompletedCommand(const AsyncFileCompletedCommand&) = delete;
	AsyncFileCompletedCommand& operator= (const AsyncFileCompletedCommand&) = delete;
	~AsyncFileCompletedCommand() = default;

	AsyncFileCompletedCommand(WaveDataID waveID, WAVEFORMATEXTENSIBLE* pWfx, unsigned int rawBuffSize, RawData* pRawBuff);

	virtual void execute() override;

private:
	WaveDataID			waveID;
	WAVEFORMATEXTENSIBLE* pWfx;
	unsigned int rawBuffSize;
	RawData* pRawBuff;
};


#endif