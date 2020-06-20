#include "HandleMan.h"
#include "Handle.h"

Handle::Handle()
{
	//Activate
	const Status status = HandleMan::ActivateHandle(this->id, this->index);
	assert(status == Status::SUCCESS);
}

Handle::~Handle()
{
	// Invalidate handle;
	HandleMan::InvalidateHandle(*this);
}

Handle::ID Handle::GetID() const
{
	return this->id;
}

Handle::Index Handle::GetIndex() const
{
	return this->index;
}

Handle::Status Handle::ValidateHandle(const Handle& handle)
{
	return HandleMan::ValidateHandle(handle);
}

Handle::Status Handle::InvalidateHandle(const Handle& handle)
{
	return HandleMan::InvalidateHandle(handle);
}

Handle::Status Handle::AquireResource(const Handle& handle)
{
	return HandleMan::AquireResource(handle);
}

Handle::Status Handle::ReleaseResource(const Handle& handle)
{
	return HandleMan::ReleaseResource(handle);
}

