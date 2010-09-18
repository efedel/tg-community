#ifndef List_h
#define List_h

#include "Thing.h"

/* sigh no other good place for this */
typedef struct List_t * List;
/* List Node ---------------------------------------------------------------- */
typedef struct ListNode_t * ListNode;
struct ListNode_t
{
	Thing T;
	ListNode Next;
	ListNode Prev;
	List MyList;
};

/* List --------------------------------------------------------------------- */
struct List_t 
{
	uint Size;
	ListNode Top;
	ListNode Dummy;
	ListNode End;
	ListNode Recent;
};

/* List ops */
List NewList();                                     /* list ctor */
void DelList(List const);                           /* list dtor */
List  ListIns(List const, const Thing const);       /* list insert */
Thing ListGet(List const, const Thing const);       /* list find item */
Thing ListRm (List const, const Thing const);       /* NOT IMPLEMENTED YET*/
uint  GetListSize(const List const);

/* not for API */
Thing ListTop(List const);	// thse can return NULL if the list size
Thing ListEnd(List const);	// is 0

#endif
