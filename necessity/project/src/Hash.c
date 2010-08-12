#include <stdlib.h>
#include "Defs.h"
#include "Thing.h"
#include "List.h"
#include "Hash.h"

// TODO: resize

static List  GetBuckets(const Hash const self, const uint index) 
{ 
	return(self->lists[index]); 
}
static HashFN GetHasher(const Hash const self) { return(self->hasher); }

static void SetBuckets(Hash const self, const uint index, const List const L) 
{
	self->lists[index] = L;
}

static void SetHasher (Hash const self, const HashFN const f) { self->hasher=f; }

/* very simple and stupid hash function, there are probably better */
static uint SimpleHasher(const Thing const T)
{
	int x=(uint) T; // get the pointer value
	return(x%MAXLISTS);
}

Hash NewHash(const HashFN const f)
{
	int i=0;
	Hash self = (Hash)malloc(sizeof(struct Hash_t));
	while (i++ < MAXLISTS) SetBuckets(self, i, NewList());
	if (f == NULL) SetHasher(self, SimpleHasher);
	return(self);
}

void DelHash(Hash const X) 
{
	int i=0;
	while (i++ < MAXLISTS) DelList(GetBuckets(X, i));
}

Hash HashIns(Hash const self, 
	     const Thing const key,
	     const Thing const item) 
{
	ListIns(GetBuckets(self, GetHasher(self)(key)), item);
	return(self);
}

Thing HashGet(const Hash const self, const Thing const key)
{
	//return(ListGet(GetBuckets(self, GetHasher(self)(T)), T));
	//HashFN F = GetHasher(self);
	//List L = GetBuckets(self, F(key));
	return(ListTop(GetBuckets(self, GetHasher(self)(key))));
}

Thing HashRm(Hash const self, const Thing const T)
{
	return(ListRm(GetBuckets(self, GetHasher(self)(T)), T));
}


