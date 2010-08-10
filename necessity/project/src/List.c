#include <stdlib.h>
#include <assert.h>
#include "List.h"
#include "Thing.h"

/* node getter */
static Thing 	GetListNodeThing(ListNode const N) 	{ return(N->t); } 
static ListNode	GetListNodeNext(const ListNode const N) { return(N->next); }

/* node setter */
static void SetListNodeThing(ListNode const N, const Thing const T) { N->t = T; } 
static ListNode SetListNodeNext (ListNode const N, const ListNode const LN) 
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
	if (GetListNodeNext(X) != NULL) 
	{
		DelListNode(GetListNodeNext(X));
	}
	DelThing(GetListNodeThing(X));
	free(X);
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
	ListNode pad = NewListNode(NewThing(0, INTEGER, NULL));
	SetListTop (self, pad);
	SetListEnd (self, pad);
	SetListSize(self, 0);
	return(self);
}

void DelList(List const X)		/* list dtor */
{
	DelListNode(GetListTop(X));	
	free(X);	
}

List InsItemList(List const L, const Thing const T)
{
	SetListEnd(L, SetListNodeNext(GetListEnd(L), NewListNode(T)));
	return(L);
}

List DelItemList(List const L, const Thing const T) 
{
	//TODO
	return(L);
}

// TODO List iterator



