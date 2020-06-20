#ifndef G_FILE_USER_CALLBACK_H
#define G_FILE_USER_CALLBACK_H

#include "GCommand.h"
#include "WaveData.h"

class GFileUserCallback : public GCommand
{
public:
	GFileUserCallback() = delete;
	GFileUserCallback(const GFileUserCallback&) = delete;
	GFileUserCallback& operator= (const GFileUserCallback&) = delete;
	~GFileUserCallback() = default;

	GFileUserCallback(WaveDataID name, FileUserCallback* pFileCB = nullptr);


	virtual void execute() override;

private:

public:
	// data
	FileUserCallback* pFileCB;
	WaveDataID wave_id;
};

#endif