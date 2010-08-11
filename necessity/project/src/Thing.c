#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Thing.h"
#include "Defs.h"

/* getters */
VARTYPE GetThingType(const Thing const T) { return T->type; }
Pointer GetThingData(Thing const T)       { return T->data; }
Dtor    GetThingDtor(const Thing const T) { return T->dtor; }
CompFN  GetThingComp(const Thing const T) { return T->comp; }
CopyFN  GetThingCopy(const Thing const T) { return T->copy; }
StrFN  GetThingToStr(const Thing const T) { return T->toString; }


/* setters */
void SetThingType (Thing const T, const VARTYPE vt)       { T->type = vt; }
void SetThingData (Thing const T, const Pointer const d)  { T->data = d; }
void SetThingDtor (Thing const T, const Dtor    const fn) { T->dtor = fn; }
void SetThingComp (Thing const T, const CompFN  const fn) { T->comp = fn; }
void SetThingCopy (Thing const T, const CopyFN  const fn) { T->copy = fn; }
void SetThingToStr(Thing const T, const StrFN   const fn) { T->toString = fn; } 


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
UFO   ThingCmp(const Thing const T1, const Thing const T2)
{
	CompFN F1 = GetThingComp(T1);
	CompFN F2 = GetThingComp(T2);
	if (F1 == F2) return(F1(T1, T2));
	else return(UFOERR);
}

/* toString */
CharBuf ThingToString(const Thing const T) 
{
	StrFN F = GetThingToStr(T);
	return F(T);
}

/* copy */
Thing 	ThingCopy(const Thing to, const Thing from)
{
	CopyFN F1 = GetThingCopy(to);
	CopyFN F2 = GetThingCopy(from);
	if (F1 == F2) return(F1(to, from));
	else return NULL;
}
