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

typedef struct Thing_t * Thing;
typedef void (*Dtor)(Pointer P);
struct Thing_t
{
	VARTYPE type;	// has the type of data encoded
	Pointer data;	// void pointer, cast to an int, char, whatnot.
	Dtor dtor;	// function pointer supplied to be called to delete
			// assumes that we delete the entire datum as well 
			// not just the data
};


Thing NewThing(const Pointer data, const VARTYPE vartype, const Dtor const destructor);	// ctor
void  DelThing(Thing const T);					// dtor	

/* getters */
Pointer GetData(const Thing const T); 
VARTYPE GetType(const Thing const T); 
Dtor    GetDtor(const Thing const T);
/* setters */
void SetData(Thing T, Pointer d); 
void SetType(Thing T, VARTYPE vt); 
void SetDtor(Thing T, Dtor fn);  

#endif 
