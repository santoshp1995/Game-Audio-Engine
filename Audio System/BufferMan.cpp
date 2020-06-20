#include "BufferMan.h"

BufferMan* BufferMan::privGetInstance()
{
	static BufferMan buffMan;
	return &buffMan;
}

BufferMan::BufferMan()
{
	
}

BufferMan::~BufferMan()
{
	
}

void BufferMan::Create()
{
	BufferMan* pMan = BufferMan::privGetInstance();
	assert(pMan);
}

void BufferMan::Destroy()
{
	BufferMan* pMan = BufferMan::privGetInstance();
	assert(pMan);
	
	
}

void BufferMan::LoadBuffer(const char* pFileName, WAVEFORMATEXTENSIBLE& wfx, XAUDIO2_BUFFER& buffer)
{
	//--------------------------------------------------------
	// zero out wfx and the buffer
	//--------------------------------------------------------

	wfx = { 0 };    // zeros out the complete structure
	buffer = { 0 };	  // zeros out the complete structure

	// -------------------------------------------------------
	// Open File
	// -------------------------------------------------------

	HANDLE hFile = CreateFile(pFileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		Trace::out("Wow: CreateFile %x\n", (unsigned int)GetLastError());
		assert(0);
	}

	// -------------------------------------------------------
	// Seek to Beginning of file
	// -------------------------------------------------------

	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
	{
		assert(0);
	}

	// -------------------------------------------------------
	// Find and load specific Chunks
	// -------------------------------------------------------

	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	DWORD filetype;

	// Scan to the RIFF and load file type
	FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
	ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);

	// Make sure its not in the compressed format, WAVE format is uncompressed
	if (filetype != fourccWAVE)
	{
		assert(false);
	}

	// Read the FMT: format
	FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
	ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);

	// Scan to the DATA chunk, read the size, allocate buffer of that size
	FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);

	BYTE* pDataBuffer = new BYTE[dwChunkSize];
	assert(pDataBuffer != 0);

	// Fill the data...
	ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);

	// Set the Buffer info...
	buffer.AudioBytes = dwChunkSize;  //buffer containing audio data
	buffer.pAudioData = pDataBuffer;  //size of the audio buffer in bytes

	buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer
	buffer.LoopCount = 0;

	// Close File
	CloseHandle(hFile);
}









