#ifndef TIME_EVENT_MAN_H
#define TIME_EVENT_MAN_H

#include "Manager.h"
#include "Command.h"
#include "TimeEvent.h"
#include "Timer.h"


class TimeEventMan : public Manager
{
private:
	TimeEventMan(int reserveNum = 3, int reserveGrow = 1);
	TimeEventMan(const TimeEventMan&) = delete;
	TimeEventMan& operator = (const TimeEventMan&) = delete;
	TimeEventMan() = delete;
	~TimeEventMan();

public:
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();

	static TimeEvent* Add(Command* pCommand, Time deltaTimeToTrigger);
	static TimeEvent* Find(TimeEvent::ID event_id);
	static Time GetTimeCurrent();

	static void Remove(TimeEvent* pNode);
	static void Dump();

	static void Update();

protected:
	virtual DLink* DerivedCreateNode() override;
	virtual bool DerivedCompare(DLink* pLinkA, DLink* pLinkB) override;
	virtual void DerivedWash(DLink* pLink) override;
	virtual void DerivedDumpNode(DLink* pLink) override;
	virtual void DerivedDestroyNode(DLink* pLink) override;

private:
	static TimeEventMan* GetInstance();

	// manager data
	static TimeEventMan* pInstance;
	TimeEvent* pNodeCompare;
	Time mCurrentTime;
	Timer GameTime;
};


#endif