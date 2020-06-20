#ifndef BUFFER_MAN_H
#define BUFFER_MAN_H

#include "XAudio2Wrapper.h"

class BufferMan
{

public:
	BufferMan(const BufferMan&) = delete;
	const BufferMan& operator=(const BufferMan&) = delete;
	~BufferMan();

	static void Create();
	static void Destroy();
	static void LoadBuffer(const char* pFileName, WAVEFORMATEXTENSIBLE& wfx, XAUDIO2_BUFFER& buffer);

private:
	static BufferMan* privGetInstance();
	
	BufferMan();

	


};



#endif
