#ifndef FILE_LOAD_COMMAND_H
#define FILE_LOAD_COMMAND_H

#include "FileCommand.h"
#include "FileUserCallback.h"
#include "WaveData.h"

class FileLoadCommand : public FileCommand
{
public:
	FileLoadCommand() = delete;
	FileLoadCommand(const FileLoadCommand&) = delete;
	FileLoadCommand& operator= (const FileLoadCommand&) = delete;
	~FileLoadCommand() = default;

	FileLoadCommand(const char* const pWaveName, WaveDataID name, FileUserCallback* pFileCB = nullptr);
	virtual void execute() override;

private:
	FileUserCallback* pFileUserCallback;
	WaveDataID waveID;
	const char* const	pWaveName;

};


#endif