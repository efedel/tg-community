#ifndef Api_h
#define Api_h

/* Basic Definitions -------------------------------------------------------- */
typedef unsigned int uint;
typedef char * String;

typedef void * Pointer;


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

typedef struct Thing_t * Thing;
typedef void   (*Dtor)(Pointer);
typedef UFO    (*CompFN)(const Thing const, const Thing const);
typedef Thing  (*CopyFN)(const Thing const from);
typedef String (*StrFN) (const Thing const);
struct Thing_t
{
        VARTYPE type;    // has the type of data encoded
        Pointer data;    // void pointer, cast to an int, char, whatnot.
        Dtor dtor;       // function pointer supplied to be called to delete
                         // assumes that we delete the entire datum as well 
                         // not just the data
        CompFN comp;     // what to use for comparisons
        CopyFN copy;     // copy ctor
        StrFN  toString; // converts to a String for easy debugging
};

/* after this there should only be 4 functions the user needs, everything else
 * is under the hood. */

/* getters */
Pointer GetThingData(Thing const);
VARTYPE GetThingType(const Thing const); 
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

void  DelThing(Thing const);                                   // dtor 

/* operations */
UFO     ThingCmp(const Thing const T1, const Thing const T2); 	/* compare */
Thing   ThingCopy(const Thing const from);		 	/* copy */	
String  ThingToString(const Thing const); 			/* toString */

/* Linked List -------------------------------------------------------------- */
typedef struct ListNode_t * ListNode;
struct ListNode_t
{ 
	Thing T; 
	ListNode Next;
	ListNode Prev;
};

typedef struct List_t * List;
struct List_t 
{ 
	uint Size; 
	ListNode Top; 
	ListNode End;
	ListNode Recent;
};

List NewList();                         	     	/* list ctor */
void DelList(List const);	             		/* list dtor */
List  ListIns(List const, const Thing const); 		/* list insert */
Thing ListGet(List const, const Thing const); 		/* list find item */
Thing ListRm(List const, const Thing const);		/* list remove item */
uint  GetListSize(const List const);		        /* list size */

/* Hash Table --------------------------------------------------------------- */
#define MAXLISTS 4095 
typedef int (*HashFN)(const Thing const);
typedef struct Hash_t * Hash;
struct Hash_t
{
	List Lists[MAXLISTS];
	HashFN Hasher;
};

Hash NewHash(const HashFN const);			/* hash ctor */
void DelHash(Hash const);				/* hash dtor */

Hash  HashIns(Hash const, 				/* insert */
	      const Thing const key, 	   		/* this is the  key */
	      const Thing const item);	   		/* this is the item */
Thing HashGet(const Hash const, const Thing const key); /* get */	
Thing HashRm(Hash const, const Thing const key);	/* remove */

/* String Operations -------------------------------------------------------- */
String 		NewStr( const char * );
void 		DelStr( String );
unsigned int 	LenStr( const String const );
String SubStr(const String const, const uint start, const uint end);

/* Word Thing --------------------------------------------------------------- */
Thing Word(const int);
int   IntWord(Thing);
char  CharWord(Thing);

/* Registers ---------------------------------------------------------------- */
Pointer GetEAX();
Pointer GetEBX(); 
Pointer GetECX(); 
Pointer GetEDX(); 
Pointer GetESI(); 
Pointer GetEDI(); 

Pointer GetESP(); 
Pointer GetEBP(); 
//Pointer GetEIP(); // TODO this needs more work

Pointer GetCS(); 
Pointer GetDS(); 
Pointer GetSS(); 
Pointer GetES(); 

/* Easter Eggs -------------------------------------------------------------- */
/* probably take this out after debuggine */
void CommentLine();
void println(String);

uint Fibonacci(int);


#endif
