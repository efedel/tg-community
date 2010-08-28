#include <stdio.h>
#include <stdbool.h>
/* TODO: figure out a way to "throw exceptions" instead of using this assert
 * although since this is a fairly simple data type this should not be an 
 * issue. */
#include <assert.h>
#include "Thing.h"
#include "Defs.h"
#include "Word.h"

/* 
 * There really is no good way for this.  We can't return any value that 
 * wouldn't be a valid one.  It would be nice to throw an * exception but 
 * we cannot.
 */
static void AssertTypeWord(Thing T) { assert(TypeCheck(T, WORD) == true); }

int  IntWord(Thing T)
{
	AssertTypeWord(T);
	return((int)GetThingData(T));
}

char CharWord(Thing T)
{
	AssertTypeWord(T);
	return((char)(((int)GetThingData(T)) % 255));
}
/* raw integer classes */
static UFO WordUFO(const Thing const T1, const Thing const T2)
{
	int x, y; 
	AssertTypeWord(T1);
	AssertTypeWord(T2);	

	x = (int)GetThingData(T1);
	y = (int)GetThingData(T2);

	if (x<y) return(LT);
	else if (x>y) return (GT);
	else return(EQ);
}

static Thing WordCopy(const Thing const from)
{
	AssertTypeWord(from);
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

