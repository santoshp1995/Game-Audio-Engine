#include "QuitCommand.h"
#include "ASndMan.h"

QuitCommand::QuitCommand(SndId _id, Snd* _pSnd)
	: 
	id(_id), pSnd(_pSnd)
{
}

void QuitCommand::execute()
{
	ASndMan::SetQuit();
}


