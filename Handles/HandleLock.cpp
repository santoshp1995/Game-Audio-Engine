
#include "HandleMan.h"
#include "Handle.h"

Handle::Lock::Lock(const Handle& h)
	: handle(h)
{
	this->status = Handle::AquireResource(handle);
}

Handle::Lock::~Lock()
{
	if (this->status == Handle::Status::SUCCESS)
	{
		this->status = Handle::ReleaseResource(handle);
	}
}

// boolean operator
Handle::Lock::operator bool() const
{
	return (this->status == Handle::Status::SUCCESS);
}

// conversion operator
Handle::Lock::operator Handle::Status() const
{
	return this->status;
}