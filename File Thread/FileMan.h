#ifndef FILE_MAN_H
#define FILE_MAN_H

#include "Handle.h"
#include "WaveData.h"
#include "CircularData.h"

class FileUserCallback;

class FileMan
{
public:

private:
	FileMan(const FileMan&) = delete;
	FileMan& operator= (const FileMan&) = delete;
	FileMan();
	~FileMan();


public:
	static Handle::Status Add(const char* const pWaveName, WaveDataID name, FileUserCallback* pFileCB = nullptr);
	static CircularData* GetFileInQueue();
	static WaveData::Status GetStatus(const WaveDataID id);
	static void SetQuit();
	static bool IsQuit();
	static void Quit();

private:
	static FileMan* GetInstance();

	CircularData* poFileInQueue;
	bool QuitFlag;
	Handle handle;
};

#endif 
