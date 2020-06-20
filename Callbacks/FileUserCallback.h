#ifndef FILE_USER_CALLBACK_H
#define FILE_USER_CALLBACK_H

#include "SndID.h"


class FileUserCallback
{
public:
	FileUserCallback() = default;
	FileUserCallback(const FileUserCallback&) = delete;
	FileUserCallback& operator= (const FileUserCallback&) = delete;
	~FileUserCallback() = default;

	void Set(const SndId _id);
	void Execute();

private:
	// class data
	SndId id;
};


#endif