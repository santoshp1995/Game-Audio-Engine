#ifndef SET_VOLUME_COMMAND_H
#define SET_VOLUME_COMMAND_H

#include "Command.h"
#include "Voice.h"
#include "Snd.h"

class SetVolumeCommand : public Command
{
public:
	SetVolumeCommand() = delete;
	SetVolumeCommand(const SetVolumeCommand&) = delete;
	SetVolumeCommand operator= (const SetVolumeCommand&) = delete;
	~SetVolumeCommand();

	// TODO REMOVE THIS
	SetVolumeCommand(Voice* voice, float volume);
	
	
	SetVolumeCommand(SndId _id, Snd* _pSnd, const float _vol);


	void execute() override;


private:
	Voice* pVoice;
	SndId id;
	Snd* pSnd;
	float vol;
};


#endif