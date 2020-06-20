#ifndef SET_PANNING_COMMAND_H
#define SET_PANNING_COMMAND_H

#include "Command.h"
#include "SndMan.h"

class SetPanningCommand : public Command
{
public:
	SetPanningCommand() = delete;
	SetPanningCommand(const SetPanningCommand&) = delete;
	SetPanningCommand& operator= (const SetPanningCommand&) = delete;
	~SetPanningCommand();

	SetPanningCommand(SndId _id, Snd* _pSnd, float _pan);

	virtual void execute() override;

private:
	SndId id;
	Snd* pSnd;
	float pan;
};


#endif