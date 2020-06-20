#ifndef CREATE_SND_COMMAND_H
#define CREATE_SND_COMMAND_H

#include "Command.h"
#include "Snd.h"

class CreateSndCommand : public Command
{
public:
	CreateSndCommand()= delete;
	CreateSndCommand(const CreateSndCommand&) = delete;
	CreateSndCommand& operator= (const CreateSndCommand&) = delete;
	~CreateSndCommand() = default;

	CreateSndCommand(SndId id, Snd* pSnd, UserCallback* pUserCallback = nullptr);

	virtual void execute() override;

private:
	SndId id;
	Snd* pSnd;
	UserCallback* pUserCallback;
};



#endif

