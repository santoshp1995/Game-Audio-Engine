#ifndef PAN_RIGHT_COMMAND_H
#define PAN_RIGHT_COMMAND_H

#include "Command.h"
#include "Voice.h"
#include "Snd.h"

class PanRightCommand : public Command
{
public:
	PanRightCommand() = delete;
	PanRightCommand(const PanRightCommand&) = delete;
	PanRightCommand& operator= (const PanRightCommand&) = delete;
	~PanRightCommand();

	PanRightCommand(Voice* voice);
	PanRightCommand(SndId _id, Snd* _pSnd);

	void execute() override;

	

private:
	Voice* pVoice;
	SndId id;
	Snd* pSnd;
};


#endif