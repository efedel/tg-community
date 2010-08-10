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



#endif
