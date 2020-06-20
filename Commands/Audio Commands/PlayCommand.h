#ifndef PLAY_COMMAND
#define PLAY_COMMAND

#include "Command.h"
#include "Voice.h"

class PlayCommand : public Command
{

public:
	PlayCommand(Voice* voice);
	void execute() override;


	~PlayCommand();



private:
	Voice* voice;
	

};


#endif