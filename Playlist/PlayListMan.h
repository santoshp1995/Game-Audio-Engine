#ifndef PLAY_LIST_MAN
#define PLAY_LIST_MAN

#include "Manager.h"
#include "PlayList.h"


class PlayListMan : public Manager
{
private:
	PlayListMan(int reserveNum = 3, int reserveGrow = 1);
	PlayListMan(const PlayListMan&) = delete;
	PlayListMan& operator = (const PlayListMan&) = delete;
	PlayListMan() = delete;
	~PlayListMan();

public:
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();
	static PlayList* Add(SndId snd_id);
	static PlayList* Find(SndId id);
	static void Remove(PlayList* pNode);
	static void Dump();

protected:
	virtual DLink* DerivedCreateNode() override;
	virtual bool DerivedCompare(DLink* pLinkA, DLink* pLinkB) override;
	virtual void DerivedWash(DLink* pLink) override;
	virtual void DerivedDumpNode(DLink* pLink) override;
	virtual void DerivedDestroyNode(DLink* pLink) override;

private:
	static PlayListMan* GetInstance();

	// manager data
	static PlayListMan* pInstance;
	PlayList* pNodeCompare;

};



#endif