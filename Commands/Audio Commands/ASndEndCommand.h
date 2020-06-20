#ifndef A_SND_END_COMMAND_H
#define A_SND_END_COMMAND_H

#include "Command.h"
#include "Snd.h"

class ASndEndCommand : public Command
{
public:
	ASndEndCommand() = delete;
	ASndEndCommand(const ASndEndCommand&) = delete;
	ASndEndCommand& operator= (const ASndEndCommand&) = delete;
	~ASndEndCommand() = default;


	ASndEndCommand(SndId _id, Snd* _pSnd);


	virtual void execute() override;

private:
	SndId id;
	Snd* pSnd;

};


#endif
