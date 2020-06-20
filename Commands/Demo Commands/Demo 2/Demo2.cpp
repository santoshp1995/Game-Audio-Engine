#include "Demo2.h"
#include "TimeEventMan.h"

void Demo2()
{
	Demo2_0* pDemo2_0 = new Demo2_0();
	assert(pDemo2_0);

	TimeEventMan::Add(pDemo2_0, 0 * Time(Duration::TIME_ONE_SECOND));



}