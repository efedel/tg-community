#include <stdio.h>
#include <stdlib.h>
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
void SetThingType(Thing const T,  const VARTYPE vt)       { T->type = vt; }
void SetThingData(Thing const T,  const Pointer const d)  { T->data = d; }
void SetThingDtor(Thing const T,  const Dtor    const fn) { T->dtor = fn; }
void SetThingComp(Thing const T,  const CompFN  const fn) { T->comp = fn; }
void SetThingCopy(Thing const to, const CopyFN  const fn) { to->copy = fn; }
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
	SetThingCopy (self, compare);
	SetThingToStr(self, toString);
	return(self);					
}

void  DelThing(Thing const self)
{
	Dtor fn = GetThingDtor(self); 	// get the Dtor
	printf("DelThing: %p\n", GetThingData(self));
	if (fn) fn(GetThingData(self)); 	// call the Dtor on the data
	free(self);
}


/* toString */
CharBuf ThingToString(Thing T) 
{
	StrFN F = GetThingToStr(T);
	return F(T);
}

#if 0
UFO   ThingCmp(const Thing const T1, const Thing const T2);
{
	
}
#endif

