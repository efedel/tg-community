#include <stdlib.h>
#include <stdbool.h>
#include "Defs.h"
//#include "String.h"
#include "Thing.h"

/* this is for the typechecking */
/* maybe for release we make this a bool */         
bool TypeCheck(const Thing const T, const VARTYPE type ) 
{ 
	return(GetThingType(T)==type);
}

/* getters */
VARTYPE GetThingType(const Thing const T) { return T->Type; }
Pointer GetThingData(Thing const T)       { return T->Data; }
Dtor    GetThingDtor(const Thing const T) { return T->Dtor; }
CompFN  GetThingComp(const Thing const T) { return T->Comp; }
CopyFN  GetThingCopy(const Thing const T) { return T->Copy; }
StrFN  GetThingToStr(const Thing const T) { return T->ToString; }


/* setters */
void SetThingType (Thing const T, const VARTYPE vt)       { T->Type = vt; }
void SetThingData (Thing const T, const Pointer const d)  { T->Data = d; }
void SetThingDtor (Thing const T, const Dtor    const fn) { T->Dtor = fn; }
void SetThingComp (Thing const T, const CompFN  const fn) { T->Comp = fn; }
void SetThingCopy (Thing const T, const CopyFN  const fn) { T->Copy = fn; }
void SetThingToStr(Thing const T, const StrFN   const fn) { T->ToString = fn; } 


Thing NewThing(const VARTYPE vartype, 
	       const Pointer const data, 
	       const Dtor    const destructor,
	       const CompFN  const compare,
	       const CopyFN  const copy, 
	       const StrFN   const toString) 
{
	Thing self;
	self = (Thing)malloc(sizeof(struct Thing_t));
	SetThingData (self, data);		
	SetThingType (self, vartype);
	SetThingDtor (self, destructor);
	SetThingComp (self, compare);
	SetThingCopy (self, copy); 
	SetThingToStr(self, toString);
	return(self);					
}

/* Design note, i typoed this once to say SetThingCopy(self, compare).  Earlier
 * I had thought about making the functions just pointers into an array of
 * Pointer and we could index into it to get the function with the cast.
 * this would have caused all sorts of grief with the typo I had. This is why
 * altho it would shrink the codebase down a little, I am having seperate 
 * decls for each function and not Pointer vftable[MAXFN] and indexes mapping
 * to dtor, comp, copy, tostr. Sorry, it's not as elegant as lisp.*/

//#include <stdio.h>
#include <string.h>
void  DelThing(Thing const self)
{
	Dtor fn = GetThingDtor(self); 	// get the Dtor
	// printf("DelThing: %p\n", GetThingData(self));
	if (fn) fn(GetThingData(self)); 	// call the Dtor on the data
	// TODO: when totally done, remove this and #include <string.h>
	// only here for ddd so we can "see" the free
	memset(self, 0, sizeof(struct Thing_t)); // debugging purposes only (DDD)
	free(self);
}


/* TODO: These scream "refactor me" but how to do in a intelligent way?
 * */

/* comparision between 2 things */
UFO    ThingCmp(const Thing const T1, const Thing const T2)
{
	CompFN F1 = GetThingComp(T1);
	CompFN F2 = GetThingComp(T2);

	if (F1 == F2) return(F1(T1, T2));
	else return(UFOERR);
}

bool 	SameThing(const Thing const T1, const Thing const T2)
{
	return(ThingCmp(T1, T2) == EQ);
}

/* toString */
String ThingToString(const Thing const T) 
{ 
	StrFN F = GetThingToStr(T);
	return F(T);
}

/* copy */
Thing  ThingCopy(const Thing const from)
{
	/* get the copy function  and then apply it to yourself */
	return(GetThingCopy(from)(from));
}

