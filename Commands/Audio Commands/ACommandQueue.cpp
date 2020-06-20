#include "ACommandQueue.h"
#include "SndMan.h"
#include "ASnd.h"
#include "SndID.h"
#include "ASndEndCommand.h"
#include "ASndMan.h"

void ACommandQueue::SndEnd(ASnd* pASnd)
{
	CircularData* pOut = SndMan::GetAudioInQueue();
	assert(pOut);

	SndId id;
	assert(pASnd);

	pASnd->GetSndId(id);
	//assert(status == Handle::Status::SUCCESS);

	Snd* pSnd = pASnd->GetSnd();
	assert(pSnd);

	Command* pCommand = new ASndEndCommand(id, pSnd);
	assert(pCommand);

	pOut->PushBack(pCommand);

	Trace::out("ACommandQueue: SndEnd\n");
}
