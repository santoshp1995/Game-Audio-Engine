#include "FileQuitCommand.h"
#include "FileMan.h"


FileQuitCommand::FileQuitCommand()
	: FileCommand()
{

}

void FileQuitCommand::execute()
{
	FileMan::SetQuit();
}

