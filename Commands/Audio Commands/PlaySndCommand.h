#ifndef PLAY_SND_COMMAND_H
#define PLAY_SND_COMMAND_H

#include "Command.h"
#include "Snd.h"

class PlaySndCommand : public Command
{
public:
	PlaySndCommand() = delete;
	PlaySndCommand(const PlaySndCommand&) = delete;
	PlaySndCommand& operator=(const PlaySndCommand&) = delete;
	~PlaySndCommand();

	PlaySndCommand(SndId id, Snd* pSnd);

	virtual void execute() override;


private:
	// command data
	SndId id;
	Snd* pSnd;
};


#endif