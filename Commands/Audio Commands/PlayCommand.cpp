#include "PlayCommand.h"
#include "VoiceMan.h"
#include "AudioSystemMan.h"

PlayCommand::PlayCommand(Voice* pVoice)
{	
	this->voice = pVoice;
}

void PlayCommand::execute()
{
	this->voice->Start();

	//delete this;
}

PlayCommand::~PlayCommand()
{
//	delete this->voice;
}



