#ifndef List_h
#define List_h

#include "Thing.h"

/* List Node ---------------------------------------------------------------- */
typedef struct ListNode_t * ListNode;
struct ListNode_t
{
	Thing t;
	ListNode next;
};

/* List --------------------------------------------------------------------- */
typedef struct List_t * List;
struct List_t 
{
	uint size;
	ListNode top;
	ListNode end;
};

/* List ops */
List NewList();                                         /* list ctor */
void DelList(List const X);                             /* list dtor */
List  ListIns(List const L, const Thing const T);       /* list insert */
Thing ListGet(List const L, const Thing const T);       /* list find item */
Thing ListRm(List const L, const Thing const T);       /* NOT IMPLEMENTED YET*/

#endif
