#ifndef Thing_h
#define Thing_h

#include <stdbool.h>

#include "Defs.h"
#include "String.h"

typedef enum Vartype_t
{ 
	SPECIAL, /* unused */ 
	WORD,
	POINTER
}
VARTYPE;

typedef struct Thing_t * Thing;
typedef void   (*Dtor)(Pointer P);
typedef UFO    (*CompFN)(const Thing const T1, const Thing const T2);
typedef Thing  (*CopyFN)(const Thing const from);
typedef String (*StrFN) (const Thing const T);
struct Thing_t
{
	VARTYPE Type;	 // has the type of data encoded
	Pointer Data;	 // void pointer, cast to an int, char, whatnot.
	Dtor Dtor;	 // function pointer supplied to be called to delete
			 // assumes that we delete the entire datum as well 
			 // not just the data
	CompFN Comp;	 // what to use for comparisons
	CopyFN Copy;     // copy ctor
	StrFN  ToString; // converts to a string for easy debugging
};

/* No other good place to put this. */
bool TypeCheck(const Thing const, const VARTYPE);

/* general API for the thing: */
Thing NewThing(const VARTYPE vartype, 
	       const Pointer const data, 
	       const Dtor    const destructor,
	       const CompFN  const compare,
	       const CopyFN  const copy,
	       const StrFN   const toString);	// ctor

void  DelThing(Thing const T);		        // dtor	

/* getters */
Pointer GetThingData(Thing const T); 
VARTYPE GetThingType(const Thing const T); 

/* I dont think these are needed for the general world 
Dtor    GetThingDtor(const Thing const T);
CompFN  GetThingComp(const Thing const T); 
CopyFN  GetThingCopy(const Thing const T); 
StrFN  GetThingToStr(const Thing const T);
*/

/* setters */
/* not needed for the general world
void SetThingType(Thing const T, const VARTYPE vt); 
void SetThingData(Thing const T, const Pointer const d); 
void SetThingDtor(Thing const T, const Dtor const fn);  
void SetThingComp(Thing const T, const CompFN  const fn);
*/

/* operations */
UFO    ThingCmp(const Thing const T1, const Thing const T2);
Thing  ThingCopy(const Thing const from);
String ThingToString(const Thing const T);

/* just a shorthand for determining if two Things are the same it is NOT
 * a compare function */
bool 	SameThing(const Thing const T1, const Thing const T2);

// TODO:
// default "Things" for integer, float, char, etc.
// make the function names for this Integer(int X); Char(int c), so forth

#endif 
