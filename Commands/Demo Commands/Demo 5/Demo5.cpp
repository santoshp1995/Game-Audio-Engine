#include "Demo5.h"
#include "TimeEventMan.h"

void Demo5()
{

	Demo5_0* pDemo5_0 = new Demo5_0();
	assert(pDemo5_0);

	Demo5_1* pDemo5_1 = new Demo5_1(pDemo5_0->pGFileCB, pDemo5_0->pSndA);
	assert(pDemo5_1);

	Demo5_2* pDemo5_2 = new Demo5_2();
	assert(pDemo5_2);
	

	TimeEventMan::Add(pDemo5_0, 0 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo5_1, 25 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(pDemo5_2, 60 * Time(Duration::TIME_ONE_SECOND));
}