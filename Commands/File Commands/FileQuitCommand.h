#ifndef FILE_QUIT_COMMAND_H
#define FILE_QUIT_COMMAND_H

#include "FileCommand.h"

class FileQuitCommand : public FileCommand
{
public:
	FileQuitCommand(const FileQuitCommand&) = delete;
	FileQuitCommand& operator= (const FileQuitCommand&) = delete;
	~FileQuitCommand() = default;

	FileQuitCommand();

	virtual void execute() override;

};

#endif