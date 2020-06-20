
#include "Command.h"
#include "Voice.h"
#include "Snd.h"

class PanLeftCommand : public Command
{
public:
	PanLeftCommand() = delete;
	PanLeftCommand(const PanLeftCommand&) = delete;
	PanLeftCommand& operator= (const PanLeftCommand&) = delete;
	~PanLeftCommand();

	PanLeftCommand(Voice* voice);
	PanLeftCommand(SndId _id, Snd* _pSnd);

	void execute() override;

private:
	Voice* pVoice;
	SndId id;
	Snd* pSnd;

};
