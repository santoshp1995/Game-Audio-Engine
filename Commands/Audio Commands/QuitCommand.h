#ifndef QUIT_COMMAND_H
#define QUIT_COMMAND_H

#include "Command.h"
#include "Snd.h"

class QuitCommand : public Command
{
public:
	QuitCommand() = delete;
	QuitCommand(const QuitCommand&) = delete;
	QuitCommand& operator= (QuitCommand&) = delete;
	~QuitCommand() = default;

	QuitCommand(SndId id, Snd* pSnd);

	virtual void execute() override;

private:
	// data
	SndId id;
	Snd* pSnd;

};


#endif