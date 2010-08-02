#ifndef Datum_h
#define Datum_h

#include "Defs_h"

void *toString()

struct Datum
{
	Thing self;
	uint id;
	Thing data;
	PureSideEffect toString;	
}

#endif 
