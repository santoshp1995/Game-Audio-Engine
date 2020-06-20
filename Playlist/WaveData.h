#ifndef WAVE_DATA_H
#define WAVE_DATA_H

#include "XAudio2Wrapper.h"
#include "VoiceCallback.h"
#include "Handle.h"
#include "DLink.h"
#include "FileUserCallback.h"

typedef unsigned char RawData;

enum class WaveDataID
{
	UNITILIZED,
	FIDDLE,
	BASSOON,
	OBOE2,
	SONGA,
	SONGB,
	INTRO,
	A,
	AtoB,
	B,
	BtoC,
	C,
	CtoA,
	END,
	COMA,
	DIAL,
	MOON_PATROL,
	SEQUENCE,
	DONKEY,
	ELECTRO,
	ALARM,
	BEETHOVEN
};


class WaveData : public DLink
{
public:

	enum class Status
	{
		READY,
		ASYNC_LOADING,
		UNINITIALIZED
	};

	static const unsigned int NAME_SIZE = 256;

	// big 4
	WaveData();
	WaveData(const WaveData&) = delete;
	const WaveData& operator=(const WaveData&) = delete;
	virtual ~WaveData();

	Handle::Status Set(const char* const pWaveName, WaveDataID id, FileUserCallback* pFileUserCB);
	Handle::Status SetID(WaveDataID id);
	void GetWaveID(WaveDataID&) const;
	Handle::Status Dump();
	Handle::Status Wash();

	Handle::Status Completed(WAVEFORMATEXTENSIBLE* pWfx, unsigned int rawBuffSize, RawData* pRawBuff);

	// getters
	WAVEFORMATEXTENSIBLE* GetWfx() const;
	unsigned int GetRawBuffSize() const;
	RawData* GetRawBuffer();
	char* GetWaveName();
	WaveData::Status GetStatus() const;


	// file size
	static const unsigned int size = 220;


private:
	void Clear();
	void SetName(const char* const pFileName);

private:
	RawData* pRawBuff;
	unsigned int  rawBuffSize;
	Handle handle;
	WAVEFORMATEXTENSIBLE* pWfx;
	WaveDataID waveId;
	Status waveStatus;
	FileUserCallback* pFileUserCallback;
	char pFileName[size];

};


#endif
