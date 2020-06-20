#include "Demo3.h"
#include "TimeEventMan.h"

void Demo3()
{
	// remove table completley before starting demo
	if (!Snd::isTableEmpty())
	{
		Snd::KillActiveSnds();
	}
	

	Demo3_0* pDemo3_0 = new Demo3_0();
	assert(pDemo3_0);

	Demo3_1* pDemo3_1 = new Demo3_1();
	assert(pDemo3_1);

	Demo3_2* pDemo3_2 = new Demo3_2();
	assert(pDemo3_2);

	Demo3_3* pDemo3_3 = new Demo3_3();
	assert(pDemo3_3);

	Demo3_4* pDemo3_4 = new Demo3_4();
	assert(pDemo3_4);

	Demo3_5* pDemo3_5 = new Demo3_5();
	assert(pDemo3_5);

	Demo3_6* pDemo3_6 = new Demo3_6();
	assert(pDemo3_6);

	Demo3_7* pDemo3_7 = new Demo3_7();
	assert(pDemo3_7);

	Demo3_8* pDemo3_8 = new Demo3_8();
	assert(pDemo3_8);

	Demo3_9* pDemo3_9 = new Demo3_9();
	assert(pDemo3_9);

	// Add to Timer Man
	TimeEventMan::Add(pDemo3_0, 0 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo3_1, 1 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo3_2, 2 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo3_3, 3 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo3_4, 4 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo3_5, 5 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo3_6, 6 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo3_7, 7 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo3_8, 8 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo3_9, 12 * Time(Duration::TIME_ONE_SECOND));


}
