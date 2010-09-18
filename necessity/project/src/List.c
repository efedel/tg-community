#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
#include "Thing.h"

/* node getter */
static Thing 	GetListNodeThing(ListNode const N) 	
{ 
	if (N) return(N->T); 	// because FindListNode can return NULL 
	else return(NULL);	// we need to catch it here.	 
} 
static ListNode	GetNextListNode(const ListNode const N) 
{ 
	if (N) return(N->Next); // because FindListNode can return NULL
	else return(NULL);	// we need to catch it here
}

static ListNode GetPrevListNode(const ListNode const N)
{
	if (N) return(N->Prev); // N can be null, lets catch it.
	else return(NULL);
}

static List GetListNodeList(const ListNode const N) { return(N->MyList); }

/* node setter */
static ListNode SetListNodeThing(ListNode const N, const Thing const t) 
{ 
	N->T = t; 
	return(N);
} 
static ListNode SetNextListNode (ListNode const N, const ListNode const next) 
{ 
	N->Next = next; 
	return(N);
}
static ListNode SetPrevListNode (ListNode const N, const ListNode const prev) 
{	
	N->Prev = prev;
	return(N);
}

static ListNode SetListNodeList (ListNode const N, const List const L)
{
	N->MyList = L;
	return(N);
}

static ListNode NewListNode(const List L, const Thing const T) 		/* node ctor */
{
	ListNode self = (ListNode)malloc(sizeof(struct ListNode_t));
	SetListNodeList( 
		SetNextListNode(
			SetPrevListNode( 
				SetListNodeThing(self, T), NULL), NULL), L);
	return(self);
}

/* removes only ONE list node, do NOT call this unless you really mean it
 * because you will end up with memory leaks since you will unlink the rest
 * of the list! */
static void DelOneListNode(ListNode const X) { free(X); }

/* need for forward declare these so that ListNodeRm will have them */
static ListNode GetListDummyNode(const List const);
static ListNode GetListTop (const List const); 
static ListNode GetListEnd (const List const); 
static List SetListTop(List const, const ListNode const); 
static List SetListEnd(List const, const ListNode const); 
static ListNode GetListRecent(const List const);
static List ClearListCache(List const);

static Thing ListNodeRm(ListNode const node)
{
	/* get the list, we're going to need it */
	List L  = GetListNodeList(node);
	/* take yourself out of the loop */
	ListNode prev = GetPrevListNode(node);
	ListNode next = GetNextListNode(node);
	/* what if prev is null?  what if next is null? */
	/* tho we are always guaranteed to have a previous because of the
	 * List Implementation hidden SPECIAL node; it's just good form */
	/* if we have a previous set it to the next element */
	if (prev) SetNextListNode(prev, next);
	if (next) SetPrevListNode(next, prev);
	/* clear everything */
	Thing ret=GetListNodeThing(node);
	SetListNodeThing(SetPrevListNode(
				SetNextListNode(node, NULL), NULL), NULL);

	/* we could be deleting the cache, the top or the end. 
	 * we need to check ALL these cases. */
	/* are we deleting the list top? */
	//if (GetListTop(L) == node) SetListTop(L, next);
	if (GetListTop(L) == node) SetListTop(L, 
	/* if we are back to an empty list, set the top back to dummy */
			(GetListSize(L) == 0) ? GetListDummyNode(L) : next);
	/* are we deleting the list end? */
	if (GetListEnd(L) == node) SetListEnd(L, prev);
	/* are we deleting the cache? */
	if (GetListRecent(L) == node) ClearListCache(L);
	
	/* absolutely make sure you are deleting only ONE list node
	 * so call DelOneListNode, not the other function */
	DelOneListNode(node);  // dump the node and return the Thing
	return(ret);
}

/* this needs to be void because it's recursive */
/* this might be a poor choice of words, what this function does is given
 * a ListNode Head, it will delete Head  and all the ListNodes after head.
 * it is not meant to be called by anyone but the List */

/* the reason for this is so that you can delete the REST of a list starting
 * from a node, otherwise you will just leave things hanging.  The only 
 * function that should be calling this is DelList, and of course itself. */
static void DelListNode(ListNode const X) 			/* node dtor */
{
	if (GetNextListNode(X) != NULL) 
	{
		DelListNode(GetNextListNode(X));
	}
	/* take this out, to comply with C++'s design; container are not
	 * responsible for destroying objects on the heap.  Since everything
	 * is on the heap in our case, we will leave it to the user to 
	 * free it up */
	//DelThing(GetListNodeThing(X));
	SetPrevListNode(SetNextListNode(X, NULL), NULL);
	DelOneListNode(X);
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
		(GetThingType(GetListNodeThing(N)) != SPECIAL) &&
		(ThingCmp(T, GetListNodeThing(N)) == EQ); 

	if (FoundNode) return(N); /* you found it! party on! */
	else if (IsLastNode) return(NULL); /* still not found: at the end  */
	else return(FindListNode(next, T));
}

/* list ops */

/* getters */
static ListNode GetListDummyNode (const List const L) { return(L->Dummy); }
static ListNode GetListTop (const List const L) { return(L->Top); }
static ListNode GetListEnd (const List const L) { return(L->End); }
       uint   	GetListSize(const List const L) { return(L->Size); }

static ListNode GetListRecent(const List const L) { return(L->Recent); }

/* setters */
static List SetListDummyNode(List const L,
		             const ListNode const N) { L->Dummy = N; return(L); }
static List SetListTop(List const L, 
		const ListNode const N) { L->Top = N; return(L); }
static List SetListEnd(List const L, 
		const ListNode const N) { L->End = N; return(L); }
static List SetListSize(List const L, 
		const uint sz) { L->Size = sz; return(L); }

/* -------------------------------------------------------------------------- */

static List ClearListCache(List const L) { L->Recent = NULL; return(L); }

/* this is not a setter.  it will not set the Recent to null ever. */
static ListNode CacheListRecent(List const L, const ListNode const N) 
{ 
	/* if we already have a recent and N is null leave it alone */
	if (N) L->Recent = N; 
	return(N);
}

List NewList()  			/* list ctor */
{
	List self = (List)malloc(sizeof(struct List_t));
	/* Pad the top of the list with a fake node that contains 
	 * some rudimentary non important info for the list */
	ListNode pad = NewListNode(self, NewThing(SPECIAL, self, 
				            NULL, NULL, NULL, NULL));
	/* call SetListRecent, not Cache, otherwise you will never 
	 * be able to initialize it.  This wasn't a problem when we used to
	 * bzero every datastructure */
	ClearListCache(
		SetListSize(
			SetListEnd(
				SetListTop(
					SetListDummyNode(self, pad), 
					pad), pad), 0));
	return(self);
}

void DelList(List const X)		/* list dtor */
{
	SetListSize(X, 0);
	DelListNode(GetListDummyNode(X));	
	free(X);	
}
/* List Insertion  */
/* TODO: this should be scrapped and broken down into ListNodeIns and
 * a ListIns that takes a position where things are to be inserted. 
 * default would be at the beginning (for speed) */
List ListIns(List const L, const Thing const T)
{
	int size = GetListSize(L);
	ListNode new = NewListNode(L, T); /* make a new list node with T */
	ListNode end = GetListEnd(L);  /* get end list node, will not be NULL */

	SetPrevListNode(new, end);     /* set the new.prev to be the end */

	/* end might be NULL so we check before we set end.next to us */
	/* end will never be NULL because we have set it to the pad */
	SetNextListNode(end, new); 

	/* if this is the first node in the list, NOT the dummy node, we
	 * set the list top to it.  */
	if (size == 0) SetListTop(L, new);
	SetListEnd(L, new);
	SetListSize(L, size + 1);
	return(L);
}

typedef Thing (*ListGetRefactorFN)(ListNode const N);
/* since both GetListNodeThing and ListNodeRm look like
 * Thing (*foo)(ListNode const N) */
/* refactored this out of ListGet and ListRm */
/* THIS COULD RETURN NULL If the T is not found. */
/* returns NULL if the list is empty */
static Thing ListGetRefactor(List const L, 
			     const Thing const T, 
			     ListGetRefactorFN fn)
{
	/* if the list size is 0 then skip all this */
	if (GetListSize(L) == 0) return(NULL);
	/* check the cache */
	ListNode cache = GetListRecent(L);
	ListNode ret = NULL;
	/* cache can be NULL */
	/* also remember ThingCmp uses return value of EQ, etc */
	if ((cache) && (ThingCmp(T, GetListNodeThing(cache)) == EQ)) 
		ret = cache; 
	/* this next line can return NULL!!! check it!!*/
	else 
		ret = FindListNode(GetListDummyNode(L), T);
	/* checking to see if ret is null */
	if (ret) 
	{
		/* tehcnically not needed but here so that future logics
		 * will not get messed up */
		cache = ret;
		/* if we have a valid return AND we are deleting an node
		 * decrement the size of the list */
		if (fn == ListNodeRm) 
		{
			int listsize = GetListSize(L);	
			listsize -= 1;
			SetListSize(L, listsize);
			/* if the list is all the way back to empty, we need
			 * to reset end so that it points to null otherwise
			 * the list insert will have it point to BADMEM! */
			if (GetListSize(L) == 0) 
			{
				/* set this back to the fake node! */
				SetListEnd(L, GetListDummyNode(L));
				/* remember to set the cache NULL!!! */
				ClearListCache(L);
			}
		}
		/* if we are fetching it not deleting it, we should cache */
		else CacheListRecent(L, ret);
		return(fn(ret));
	}
	else return(NULL);
}

/* Fetch an item */
/* this returns the item or NULL if not found */
Thing ListGet(List const L, const Thing const T) 
{
	return(ListGetRefactor(L, T, GetListNodeThing));
}

/* returns NULL if list is empty */
/* remember we have to skip over the fake node of the list */
Thing ListTop(const List const L)
{
	return((GetListSize(L) == 0) 
		? NULL 
		: GetListNodeThing(GetNextListNode(GetListDummyNode(L))));
}

/* returns NULL if list is empty */
Thing ListEnd(const List const L)
{
	return((GetListSize(L) == 0) ? NULL : GetListNodeThing(GetListEnd(L)));
}

// TODO: impl this!
Thing ListRm(List const L, const Thing const T) 
{
	return(ListGetRefactor(L, T, ListNodeRm));
}

// TODO List iterator, map
