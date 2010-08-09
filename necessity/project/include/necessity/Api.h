#ifndef Api_h
#define Api_h

/* Basic Definitions -------------------------------------------------------- */

/* The Thing ---------------------------------------------------------------- */
typedef void * Pointer;
typedef enum Vartype_t
{
        CHAR,
        FLOAT,
        INTEGER,
        POINTER
} 
VARTYPE;


typedef struct Thing_t * Thing;
typedef void (*Dtor)(Thing T);
struct Thing_t
{
        VARTYPE type;   // has the type of data encoded
        Pointer data;     // void pointer, cast to an int, char, whatnot.
        Dtor dtor;      // function pointer supplied to be called to delete
                        // assumes that we delete the entire datum as well 
                        // not just the data
};

Pointer GetData(Thing const T);
VARTYPE GetType(const Thing const T); 
Dtor    GetDtor(const Thing const T);



/* TODO this is just here temporarily, we probably can abstract this away */
Thing NewThing(const Pointer data, const VARTYPE vartype, const Dtor const destructor); // ctor
void  DelThing(Thing const self);                                        // dtor 



/* Pairs -------------------------------------------------------------------- */

/* Linked List -------------------------------------------------------------- */

/* Hash Table --------------------------------------------------------------- */

/* String Operations -------------------------------------------------------- */
char * 		String( const char * );
void 		DelStr( char * );
unsigned int 	LenStr( char * );

#endif
