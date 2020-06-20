#include "Manager.h"
#include "SndID.h"
#include "ASnd.h"

class ASndMan : public Manager
{
private:
	ASndMan(int reserveNum = 3, int reserveGrow = 1);
	ASndMan(const ASndMan&) = delete;
	ASndMan& operator = (const ASndMan&) = delete;
	ASndMan() = delete;
	~ASndMan();

public:
	// static methods
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();

	static ASnd* Add(SndId snd_id);
	static ASnd* Find(SndId snd_id);

	static void Remove(ASnd* pNode);
	static void Dump();

	static void SetQuit();
	static bool IsQuit();

	// override abstract methods
protected:
	virtual DLink* DerivedCreateNode() override;
	virtual bool DerivedCompare(DLink* pLinkA, DLink* pLinkB) override;
	virtual void DerivedWash(DLink* pLink) override;
	virtual void DerivedDumpNode(DLink* pLink) override;
	virtual void DerivedDestroyNode(DLink* pLink) override;

private:
	static ASndMan* GetInstance();

	// data
	static ASndMan* pInstance;
	ASnd* pNodeCompare;
	bool QuitFlag;

};
