#ifndef PAN_MIDDLE_COMMAND
#define PAN_MIDDLE_COMMAND

#include "Command.h"
#include "Voice.h"
#include "Snd.h"

class PanMiddleCommand : public Command
{

public:
	PanMiddleCommand() = delete;
	PanMiddleCommand(const PanMiddleCommand&) = delete;
	PanMiddleCommand& operator= (const PanMiddleCommand&) = delete;
	~PanMiddleCommand();

	PanMiddleCommand(Voice* voice);
	PanMiddleCommand(SndId _id, Snd* _pSnd);


	void execute() override;

	



private:
	Voice* pVoice;
	SndId id;
	Snd* pSnd;
};


#endif