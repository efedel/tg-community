#ifndef Api_h
#define Api_h

/* Basic Definitions -------------------------------------------------------- */
typedef unsigned int uint;

typedef void * Pointer;
typedef char * CharBuf;

typedef enum Boolean_t { FALSE, TRUE } BOOLEAN; /* Boolean */
typedef enum Ufo_t { LT = -1 , EQ = 0, GT = 1, UFOERR } UFO;          /* <=> */

/* The Thing ---------------------------------------------------------------- */

/* The user is to create a thing, and supply it a destructor and a type */

/* these might be expounded upon: 
 * TODO: there should be a good way to make this user definable. */
typedef enum Vartype_t
{
	SPECIAL,
	WORD,
        POINTER
} 
VARTYPE;

typedef struct  Thing_t * Thing;
typedef void    (*Dtor)(Pointer P);
typedef UFO     (*CompFN)(const Thing const T1, const Thing const T2);
typedef Thing   (*CopyFN)(const Thing const from);
typedef CharBuf (*StrFN) (const Thing const T);
struct Thing_t
{
        VARTYPE type;    // has the type of data encoded
        Pointer data;    // void pointer, cast to an int, char, whatnot.
        Dtor dtor;       // function pointer supplied to be called to delete
                         // assumes that we delete the entire datum as well 
                         // not just the data
        CompFN comp;     // what to use for comparisons
        CopyFN copy;     // copy ctor
        StrFN  toString; // converts to a string for easy debugging
};

/* after this there should only be 4 functions the user needs, everything else
 * is under the hood. */

/* getters */
Pointer GetThingData(Thing const T);
VARTYPE GetThingType(const Thing const T); 
/* not needed 
Dtor    GetThingDtor(const Thing const T);
*/

/* TODO this is just here temporarily, we probably can abstract this away */
Thing NewThing(const VARTYPE vartype, 
	       const Pointer const data, 
	       const Dtor    const destructor, 
	       const CompFN  const compare,
	       const CopyFN  const copy,
	       const StrFN   const toString);

void  DelThing(Thing const self);                                   // dtor 

/* oerations */
UFO     ThingCmp(const Thing const T1, const Thing const T2); 	/* compare */
Thing   ThingCopy(const Thing const from);	 		/* copy */	
CharBuf ThingToString(const Thing const T); 			/* toString */

/* Pairs -------------------------------------------------------------------- */

/* Linked List -------------------------------------------------------------- */
typedef struct ListNode_t * ListNode;
struct ListNode_t
{ 
	Thing t; 
	ListNode next;
};

typedef struct List_t * List;
struct List_t 
{ 
	uint size; 
	ListNode top; 
	ListNode end;
};

List NewList();                         	     	/* list ctor */
void DelList(List const X);             		/* list dtor */
List  ListIns(List const L, const Thing const T); 	/* list insert */
Thing ListGet(List const L, const Thing const T); 	/* list find item */
Thing ListRm(List const L, const Thing const T);	/* NOT IMPLEMENTED YET*/

/* Hash Table --------------------------------------------------------------- */
#define MAXLISTS 4095 
typedef int (*HashFN)(const Thing const T);
typedef struct Hash_t * Hash;
struct Hash_t
{
	List lists[MAXLISTS];
	HashFN hasher;
};

Hash NewHash(const HashFN const HFN);			/* hash ctor */
void DelHash(Hash const H);				/* hash dtor */

Hash  HashIns(Hash const self, 
	      const Thing const key, 
	      const Thing const item);	   /* insert */
Thing HashGet(const Hash const self, const Thing const key); /* get */	
Thing HashRm(Hash const self, const Thing const T);	   /* remove */

/* String Operations -------------------------------------------------------- */
char * 		String( const char * );
void 		DelStr( char * );
unsigned int 	LenStr( char * );

/* Word Thing --------------------------------------------------------------- */
Thing Word(const int i);
int   IntWord(Thing T);
char  CharWord(Thing T);

/* Easter Eggs -------------------------------------------------------------- */
/* probably take this out after debuggine */
Pointer GetESP();
void CommentLine();
void println(CharBuf cstr);


#endif
