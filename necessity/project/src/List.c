#include <stdlib.h>
#include <assert.h>
#include "List.h"
#include "Thing.h"

/* node getter */
static Thing 	GetListNodeThing(ListNode const N) 	{ return(N->t); } 
static ListNode	GetNextListNode(const ListNode const N) { return(N->next); }

/* node setter */
static void SetListNodeThing(ListNode const N, const Thing const T) { N->t = T; } 
static ListNode SetNextListNode (ListNode const N, const ListNode const LN) 
{ 
	N->next = LN; 
	return LN;
}

static ListNode NewListNode(const Thing const T) 		/* node ctor */
{
	ListNode self = (ListNode)malloc(sizeof(struct ListNode_t));
	SetListNodeThing(self, T);
	return(self);
}

static void DelListNode(ListNode const X) 			/* node dtor */
{
	if (GetNextListNode(X) != NULL) 
	{
		DelListNode(GetNextListNode(X));
	}
	DelThing(GetListNodeThing(X));
	SetNextListNode(X, NULL);
	free(X);
}

/* node ops 
 * these are basically helper functions for the list ops */
static ListNode FindListNode(const ListNode const N, const Thing const T)
{
	ListNode next	   = GetNextListNode(N);
	BOOLEAN IsLastNode = next == NULL;
	BOOLEAN FoundNode  = ThingCmp(T, GetListNodeThing(N)) == EQ;

	if (FoundNode) return(N); /* you found it! party on! */
	else if (IsLastNode) return(NULL); /* still not found: at the end  */
	else return(FindListNode(next, T));
}

/* list ops */

/* getters */
static ListNode GetListTop (const List const L) { return(L->top); }
static ListNode GetListEnd (const List const L) { return(L->end); }
static uint 	GetListSize(const List const L) { return(L->size); }

/* setters */
static void SetListTop (List const L, const ListNode const N) { L->top  = N; }
static void SetListEnd (List const L, const ListNode const N) { L->end  = N; }
static void SetListSize(List const L, const uint sz)          { L->size = sz; }

List NewList()  			/* list ctor */
{
	List self = (List)malloc(sizeof(struct List_t));
	/* Pad the top of the list with a fake node that contains 
	 * some rudimentary non important info for the list */
	ListNode pad = NewListNode(NewThing(INTEGER, self, 
				            NULL, NULL, NULL, NULL));
	SetListTop (self, pad);
	SetListEnd (self, pad);
	SetListSize(self, 0);
	return(self);
}

void DelList(List const X)		/* list dtor */
{
	SetListSize(X, 0);
	DelListNode(GetListTop(X));	
	free(X);	
}

/* List Insertion  */
List InsItemList(List const L, const Thing const T)
{
	SetListEnd(L, SetNextListNode(GetListEnd(L), NewListNode(T)));
	SetListSize(L, GetListSize(L) + 1);
	return(L);
}

/* Fetch an item */
Thing GetItemList(List const L, const Thing const T) 
{
	return(GetListNodeThing(FindListNode(GetListTop(L), T)));
}

// TODO: impl this!
List DelItemList(List const L, const Thing const T) 
{
	//TODO
	return(L);
}

// TODO List iterator



