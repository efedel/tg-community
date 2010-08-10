#ifndef Thing_h
#define Thing_h

#include "Defs.h"

typedef enum Vartype_t
{
	CHAR,
	FLOAT,
	INTEGER,
	POINTER
} 
VARTYPE;

typedef struct  Thing_t * Thing;
typedef void    (*Dtor)(Pointer P);
typedef UFO     (*CompFN)(const Thing const T1, const Thing const T2);
typedef Thing   (*CopyFN)(Thing const to, const Thing const from);
typedef CharBuf (*StrFN) (const Thing const T);
// copy constructor?
struct Thing_t
{
	VARTYPE type;	 // has the type of data encoded
	Pointer data;	 // void pointer, cast to an int, char, whatnot.
	Dtor dtor;	 // function pointer supplied to be called to delete
			 // assumes that we delete the entire datum as well 
			 // not just the data
	CompFN comp;	 // what to use for comparisons
	CopyFN copy;     // copy ctor
	StrFN  toString; // converts to a string for easy debugging
};


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
Dtor    GetThingDtor(const Thing const T);

/* setters */
void SetThingType(Thing const T, const VARTYPE vt); 
void SetThingData(Thing const T, const Pointer const d); 
void SetThingDtor(Thing const T, const Dtor const fn);  
void SetThingComp(Thing const T, const CompFN  const fn);

#endif 
