//#include <stdlib.h>
#include <stdio.h>
#include "Thing.h"
#include "Defs.h"
#include "Word.h"

int  IntWord(Thing T)
{
	TypeCheck(T, WORD);
	return((int)GetThingData(T));
}

char CharWord(Thing T)
{
	TypeCheck(T, WORD);
	return((char)(((int)GetThingData(T)) % 255));
}
/* raw integer classes */
static UFO WordUFO(const Thing const T1, const Thing const T2)
{
	int x, y;
	TypeCheck(T1, WORD);
	TypeCheck(T2, WORD);

	x = (int)GetThingData(T1);
	y = (int)GetThingData(T2);

	if (x<y) return(LT);
	else if (x>y) return (GT);
	else return(EQ);
}

static Thing WordCopy(const Thing const from)
{
	TypeCheck(from, WORD);
	return(Word((int)GetThingData(from)));
}

#define LARGESTINTLEN 32
/* i hate constants, but 64 bit ints convert to a number that is 
 * length 20 char + sign, make it the nearest power of 2 above 20 */
static String WordToString(const Thing const T)
{
	int i = (int)GetThingData(T);
	char buf[LARGESTINTLEN];
	snprintf((char*)&buf, LARGESTINTLEN, "%d", i);
	return(NewStr(buf));
}

Thing 	Word(const int i)
{
	Thing self = NewThing(WORD, 
			      (Pointer) i, 
			      NULL,  /* no need for dtor on simple one */
			      WordUFO, 
			      WordCopy,
			      WordToString);
	return(self);
}

