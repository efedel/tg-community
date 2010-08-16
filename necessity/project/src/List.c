#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "List.h"
#include "Thing.h"

/* node getter */
static Thing 	GetListNodeThing(ListNode const N) 	
{ 
	if (N) return(N->t); 	// because FindListNode can return NULL 
	else return(NULL);	// we need to catch it here.	 
} 
static ListNode	GetNextListNode(const ListNode const N) 
{ 
	if (N) return(N->next); // because FindListNode can return NULL
	else return(NULL);	// we need to catch it here
}

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
	SetNextListNode(self, NULL);
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

/* this can return NULL!*/
/* we screen for SPECIAL because that is the type for the cheat node
 * at the start of the list */
static ListNode FindListNode(const ListNode const N, const Thing const T)
{
	ListNode next	   = GetNextListNode(N);
	bool IsLastNode = next == NULL;
	bool FoundNode  = 
		(GetThingType(T) != SPECIAL) &&
		(ThingCmp(T, GetListNodeThing(N)) == EQ); 

	if (FoundNode) return(N); /* you found it! party on! */
	else if (IsLastNode) return(NULL); /* still not found: at the end  */
	else return(FindListNode(next, T));
}

/* list ops */

/* getters */
static ListNode GetListTop (const List const L) { return(L->top); }
static ListNode GetListEnd (const List const L) { return(L->end); }
static uint   	GetListSize(const List const L) { return(L->size); }

/* setters */
static void SetListTop (List const L, const ListNode const N) { L->top  = N; }
static void SetListEnd (List const L, const ListNode const N) { L->end  = N; }
static void SetListSize(List const L, const uint sz)          { L->size = sz; }

List NewList()  			/* list ctor */
{
	List self = (List)malloc(sizeof(struct List_t));
	/* Pad the top of the list with a fake node that contains 
	 * some rudimentary non important info for the list */
	ListNode pad = NewListNode(NewThing(SPECIAL, self, 
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
List ListIns(List const L, const Thing const T)
{
	SetListEnd(L, SetNextListNode(GetListEnd(L), NewListNode(T)));
	SetListSize(L, GetListSize(L) + 1);
	return(L);
}

/* Fetch an item */
/* this returns the item or NULL if not found */
Thing ListGet(List const L, const Thing const T) 
{
	return(GetListNodeThing(FindListNode(GetListTop(L), T)));
}

/* returns NULL if list is empty */
/* remember we have to skip over the fake node of the list */
Thing ListTop(const List const L)
{
	return((GetListSize(L) == 0) 
		? NULL 
		: GetListNodeThing(GetNextListNode(GetListTop(L))));
}

/* returns NULL if list is empty */
Thing ListEnd(const List const L)
{
	return((GetListSize(L) == 0) ? NULL : GetListNodeThing(GetListEnd(L)));
}

// TODO: impl this!
#include <stdio.h>
Thing ListRm(List const L, const Thing const T) 
{
	//TODO
	printf("***I hope you remembered to write this function.\n");
	return(NULL);
}

// TODO List iterator



