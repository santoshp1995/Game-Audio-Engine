#ifndef STOP_COMMAND_H
#define STOP_COMMAND_H

#include "Command.h"
#include "Voice.h"
#include "Snd.h"

class StopCommand : public Command
{
public:
	StopCommand(Voice* voice);
	StopCommand(SndId _id, Snd* _pSnd);
	
	void execute() override;

	~StopCommand();


private:
	Voice* pVoice;
	SndId id;
	Snd* pSnd;
};


#endif
