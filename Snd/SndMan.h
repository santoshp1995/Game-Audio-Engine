#ifndef SND_MAN_H
#define SND_MAN_H

#include "Manager.h"
#include "SndID.h"
#include "Snd.h"
#include "CircularData.h"

class SndMan : public Manager
{
private:
	SndMan(int reserveNum = 3, int reserveGrow = 1);
	SndMan(const SndMan&) = delete;
	SndMan& operator = (const SndMan&) = delete;
	SndMan() = delete;
	~SndMan();

public:
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();

	//static Snd* Add(SndId snd_id, SndPriority snd_priority = 0);
	static Snd* Add(SndId snd_id, UserCallback* pCallback = nullptr, SndPriority snd_priority = 0);
	static Snd* Find(SndId snd_id);

	static void Remove(Snd* pNode);
	static void Dump();

	static void Quit(SndId snd_id);


	static CircularData* GetAudioInQueue();
	static CircularData* GetGameInQueue();

protected:
	virtual DLink* DerivedCreateNode() override;
	virtual bool DerivedCompare(DLink* pLinkA, DLink* pLinkB) override;
	virtual void DerivedWash(DLink* pLink) override;
	virtual void DerivedDumpNode(DLink* pLink) override;
	virtual void DerivedDestroyNode(DLink* pLink) override;

private:
	static SndMan* GetInstance();

	// manager data
	static SndMan* pInstance;
	Snd* pNodeCompare;
	CircularData* pAudioInQueue;
	CircularData* pGameInQueue;



};


#endif