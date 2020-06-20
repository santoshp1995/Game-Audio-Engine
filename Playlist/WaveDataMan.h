#ifndef WAVE_DATA_MAN_H
#define WAVE_DATA_MAN_H

#include "WaveData.h"
#include "Manager.h"
#include "FileUserCallback.h"

class WaveDataMan : public Manager
{
private:
	WaveDataMan(int reserveNum = 3, int reserveGrow = 1);
	WaveDataMan(const WaveDataMan&) = delete;
	WaveDataMan& operator = (const WaveDataMan&) = delete;
	WaveDataMan() = delete;
	~WaveDataMan();
	

public:
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();
	
	static WaveData* Add(const char* const pFileName, WaveDataID id, FileUserCallback* pFileUserCB = nullptr);
	static WaveData* Find(const WaveDataID id);

	static void Remove(WaveData* pNode);
	static void Dump();

protected:
	// override abstract methods
	virtual DLink* DerivedCreateNode() override;
	virtual bool DerivedCompare(DLink* pLinkA, DLink* pLinkB) override;
	virtual void DerivedWash(DLink* pLink) override;
	virtual void DerivedDumpNode(DLink* pLink) override;
	virtual void DerivedDestroyNode(DLink* pLink) override;

private:
	static WaveDataMan* GetInstance();

	// manager data
	static WaveDataMan* pInstance;
	WaveData* pNodeCompare;
};


#endif
