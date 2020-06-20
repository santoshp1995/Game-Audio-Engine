#include "GUserCallback.h"
#include "ThreadHelper.h"

GUserCallback::GUserCallback(UserCallback* _pUserCallback)
	:pUserCB(_pUserCallback)
{
	assert(this->pUserCB);
}

void GUserCallback::execute()
{
	Trace::out("%s GUserCallback: \n  callback:%p \n", ThreadHelper::GetThreadName(), this->pUserCB);
	this->pUserCB->OnStreamEnd();

	delete this->pUserCB;
}

