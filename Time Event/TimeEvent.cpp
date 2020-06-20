#include "TimeEvent.h"
#include "TimeEventMan.h"
#include "Time.h"

TimeEvent::TimeEvent()
{
	this->id = ID::Uninitialized;
	this->pCommand = nullptr;
	this->triggerTime = Time(Duration::TIME_ZERO);
	this->deltaTime = Time(Duration::TIME_ZERO);
}

TimeEvent::~TimeEvent()
{
	delete this->pCommand;
}

void TimeEvent::SetID(const TimeEvent::ID _id)
{
	this->id = _id;
}

TimeEvent::ID TimeEvent::GetID() const
{
	return this->id;
}

Time TimeEvent::GetTriggerTime() const
{
	return this->triggerTime;
}

void TimeEvent::Process()
{
	// make sure the command is valid
	assert(this->pCommand != nullptr);

	// fire it off
	pCommand->execute();
}

void TimeEvent::Set(Command* _pCommand, Time deltaTimeToTrigger)
{
	assert(_pCommand);
	this->pCommand = _pCommand;

	this->deltaTime = deltaTimeToTrigger;

	this->triggerTime = TimeEventMan::GetTimeCurrent() + this->deltaTime;
}

void TimeEvent::Dump()
{
	int ms = Time::quotient(this->GetTriggerTime(), Time(Duration::TIME_ONE_MILLISECOND));

	Trace::out("   Name: %d (%p) %f s\n", this->GetID(), this, ms / 1000.0f);
}

void TimeEvent::Wash()
{
	// Wash - clear the entire hierarchy
	DLink::Clear();

	// Sub class clear
	this->Clear();
}

void TimeEvent::Clear()
{
	this->id = TimeEvent::Uninitialized;
	delete this->pCommand;
	this->pCommand = nullptr;

	this->triggerTime = Time(Duration::TIME_ZERO);
	this->deltaTime = Time(Duration::TIME_ZERO);
}












