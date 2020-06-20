#include "Demo1.h"
#include "TimeEventMan.h"

void Demo1()
{
	// PLAY 101 -- FIDDLE
	// PAN CENTER, VOLUME 70%
	Demo1A_0* pDemo1A_0 = new Demo1A_0();
	assert(pDemo1A_0);

	// PLAY 101 -- FIDDLE
	// PAN LEFT,VOLUME 70%
	Demo1A_1* pDemo1A_1 = new Demo1A_1();
	assert(pDemo1A_1);

	// PLAY 101 -- FIDDLE
	// PAN RIGHT, VOLUME 70%
	Demo1A_2* pDemo1A_2 = new Demo1A_2();
	assert(pDemo1A_2);

	// PLAY 102 -- BASSOON
	// PAN LEFT TO RIGHT
	Demo1B_0* pDemo1B_0 = new Demo1B_0();
	assert(pDemo1B_0);

	// PLAY 102 -- BASSOON
	// PAN RIGHT TO LEFT
	Demo1B_1* pDemo1B_1 = new Demo1B_1();
	assert(pDemo1B_1);

	// PLAY 103 -- OBOE2
	// VOLUME 0 TO 100
	Demo1C_0* pDemo1C_0 = new Demo1C_0();
	assert(pDemo1C_0);

	// PLAY 103 -- OBOE2
	// VOLUME 100 TO 0
	Demo1C_1* pDemo1C_1 = new Demo1C_1();
	assert(pDemo1C_1);

	// PLAY 104 -- SONG A and PLAY 104 -- SONG B
	// PAN LEFT RIGHT RESPECTIVLEY
	Demo1D_0* pDemo1D_0 = new Demo1D_0();
	assert(pDemo1D_0);

	Demo1D_1* pDemo1D_1 = new Demo1D_1(pDemo1D_0->pSndA);
	assert(pDemo1D_1);

	Demo1D_2* pDemo1D_2 = new Demo1D_2(pDemo1D_0->pSndA);
	assert(pDemo1D_2);

	Demo1D_3* pDemo1D_3 = new Demo1D_3(pDemo1D_0->pSndA);
	assert(pDemo1D_3);

	Demo1D_4* pDemo1D_4 = new Demo1D_4(pDemo1D_0->pSndB);
	assert(pDemo1D_4);

	// Sound Instancing ---

	// Sound A -- PLay 102 Bassoon
	Demo1E_0* pDemo1E_0 = new Demo1E_0();
	assert(pDemo1E_0);

	// Sound B -- Play 102 Bassoon
	Demo1E_1* pDemo1E_1 = new Demo1E_1();
	assert(pDemo1E_1);

	// Sound C -- Play 102 Bassoon
	Demo1E_2* pDemo1E_2 = new Demo1E_2();
	assert(pDemo1E_2);

	// Sound D -- Play 102 Bassoon
	Demo1E_3* pDemo1E_3 = new Demo1E_3(pDemo1E_0->pSndA, pDemo1E_1->pSndB, pDemo1E_2->pSndC);
	assert(pDemo1E_3);

	// Add Timer Events
	TimeEventMan::Add(pDemo1A_0, 0 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo1A_1, 3 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo1A_2, 6 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo1B_0, 10 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo1B_1, 15 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo1C_0, 20 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo1C_1, 25 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo1D_0, 30 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo1D_1, 35 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo1D_2, 38 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo1D_3, 60 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo1D_4, 72 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo1E_0, 80 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo1E_1, 80.5f * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo1E_2, 81 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo1E_3, 81.5f * Time(Duration::TIME_ONE_SECOND));
}