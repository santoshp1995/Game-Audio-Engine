#ifndef TIME_EVENT_H
#define TIME_EVENT_H

#include "DLink.h"
#include "Command.h"
#include "Time.h"

class TimeEvent : public DLink
{
public:
	enum ID
	{
		Demo1_A = 0x66660000,
		Demo1_B,
		Demo1_C,
		Uninitialized
	};

public:
	TimeEvent();
	TimeEvent(const TimeEvent&) = delete;
	TimeEvent& operator = (const TimeEvent&) = delete;
	~TimeEvent();


	void SetID(const TimeEvent::ID id);
	TimeEvent::ID GetID() const;

	Time GetTriggerTime() const;
	void Process();

	void Set(Command* pCommand, Time deltaTimeToTrigger);

	void Dump();
	void Wash();

private:
	// helper functions
	void Clear();

	Command* pCommand;
	ID id;
	Time triggerTime;
	Time deltaTime;

};


#endif