#ifndef SND_ID_H
#define SND_ID_H

enum class SndId
{
	Fiddle = 101,
	Bassoon = 102,
	Oboe2 = 103,
	SongA = 104,
	SongB = 105,

	Intro = 201,
	A = 202,
	AtoB = 203,
	B = 204,
	BtoC = 205,
	C = 206,
	CtoA = 207,
	End = 208,

	Coma = 301,

	Dial = 401,
	Moon_Patrol = 402,
	Sequence = 403,
	Donkey = 404,

	Electro = 501,
	Alarm = 502,
	Beethoven = 503,

	Quit,
	Uninitialized = 0x7FFF0000
};


#endif