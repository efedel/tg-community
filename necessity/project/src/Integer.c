//#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Thing.h"
#include "Defs.h"
#include "Integer.h"

/* raw integer classes */

/* maybe for release we make this a bool */
static void IntegerCheck(const Thing const T)
{
	assert(GetThingType(T)==INTEGER);
}

static UFO IntegerUFO(const Thing const T1, const Thing const T2)
{
	int x, y;
	IntegerCheck(T1);
	IntegerCheck(T2);

	x = (int)GetThingData(T1);
	y = (int)GetThingData(T2);

	if (x<y) return(LT);
	else if (x>y) return (GT);
	else return(EQ);
}

static Thing IntegerCopy(const Thing const from)
{
	IntegerCheck(from);
	return(Integer((int)GetThingData(from)));
}

#define LARGESTINTLEN 32
/* i hate constants, but 64 bit ints convert to length 20 bits + sign */
static CharBuf IntegerToString(const Thing const T)
{
	int i = (int)GetThingData(T);
	char buf[LARGESTINTLEN];
	snprintf((char*)&buf, LARGESTINTLEN, "%d", i);
	return(String(buf));
}

Thing 	Integer(const int i)
{
	Thing self = NewThing(INTEGER, 
			      (Pointer) i, 
			      NULL,  /* no need for dtor on simple one */
			      IntegerUFO, 
			      IntegerCopy,
			      IntegerToString);
	return(self);
}
