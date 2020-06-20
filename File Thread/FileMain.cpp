#include "ThreadHelper.h"
#include "FileMan.h"
#include "FileMain.h"



void FileMain()
{
	ThreadHelper::DebugBegin(1);

	while (!FileMan::IsQuit())
	{
		Command* pCmd = nullptr;

		// Any commands to process?
		if (FileMan::GetFileInQueue()->PopFront(pCmd) == true)
		{
			assert(pCmd);
			pCmd->execute();

			// Commands are instantly killed after execution
			// todo... recycle commands

			delete pCmd;
		}


		//	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	ThreadHelper::DebugEnd(1);
}