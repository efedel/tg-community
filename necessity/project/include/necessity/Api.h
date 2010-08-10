#ifndef Api_h
#define Api_h

/* Basic Definitions -------------------------------------------------------- */
typedef unsigned int uint;

typedef void * Pointer;
typedef char * CharBuf;

typedef enum Boolean_t { FALSE, TRUE } BOOLEAN; /* Boolean */
typedef enum Ufo_t { LT, EQ, GT } UFO;          /* <=> */

/* The Thing ---------------------------------------------------------------- */

/* The user is to create a thing, and supply it a destructor and a type */

/* these might be expounded upon: 
 * TODO: there should be a good way to make this user definable. */
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
struct Thing_t
{
        VARTYPE type;   // has the type of data encoded
        Pointer data;     // void pointer, cast to an int, char, whatnot.
        Dtor dtor;      // function pointer supplied to be called to delete
                        // assumes that we delete the entire datum as well 
                        // not just the data
};

/* getters */
Pointer GetThingData(Thing const T);
VARTYPE GetThingType(const Thing const T); 
Dtor    GetThingDtor(const Thing const T);

/* TODO this is just here temporarily, we probably can abstract this away */
Thing NewThing(const VARTYPE vartype, 
	       const Pointer const data, 
	       const Dtor    const destructor, 
	       const CompFN  const compare,
	       const CopyFN  const copy,
	       const StrFN   const toString);

void  DelThing(Thing const self);                                        // dtor 

/* Pairs -------------------------------------------------------------------- */

/* Linked List -------------------------------------------------------------- */

/* Hash Table --------------------------------------------------------------- */

/* String Operations -------------------------------------------------------- */
char * 		String( const char * );
void 		DelStr( char * );
unsigned int 	LenStr( char * );

#endif
