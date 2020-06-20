#include "Demo4.h"
#include "TimeEventMan.h"

void Demo4()
{
	// remove table completley before starting demo
	if (!Snd::isTableEmpty())
	{
		Snd::KillActiveSnds();
	}


	Demo4_0* pDemo4_0 = new Demo4_0();
	assert(pDemo4_0);

	Demo4_1* pDemo4_1 = new Demo4_1();
	assert(pDemo4_1);

	TimeEventMan::Add(pDemo4_0, 0 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo4_1, 3.5f * Time(Duration::TIME_ONE_SECOND));
}
