#include <stdio.h>
#include <stdlib.h>
#include "Thing.h"
#include "Defs.h"


void  SetData(Thing T, Pointer d)  { T->data = d; }
void  SetType(Thing T, VARTYPE vt) { T->type = vt; }
void  SetDtor(Thing T, Dtor fn)    { T->dtor = fn; }

Pointer GetData(Thing const T) 	     { return T->data; }
VARTYPE GetType(const Thing const T) { return T->type; }
Dtor    GetDtor(const Thing const T) { return T->dtor; }

Thing NewThing(const Pointer data, const VARTYPE vartype, const Dtor const destructor) 
{
	Thing self;
	self = (Thing)malloc(sizeof(struct Thing_t));
	SetData(self, data);		
	SetType(self, vartype);
	SetDtor(self, destructor);
	return(self);					
}

void  DelThing(Thing const self)
{
	Dtor fn = GetDtor(self); 	// get the Dtor
	printf("DelThing: %p\n", GetData(self));
	if (fn) fn(GetData(self)); 	// call the Dtor on the data
	//free(self);
}

