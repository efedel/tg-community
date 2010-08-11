#include <stdlib.h>
#include "Defs.h"
#include "Thing.h"
#include "List.h"
#include "Hash.h"

// TODO: resize

static List  GetBuckets(Hash self, uint index) { return(self->lists[index]); }
static HashFN GetHasher(Hash self) { return(self->hasher); }

static void SetHasher (Hash self, HashFN f) { self->hasher=f; }

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
	while (i++ < MAXLISTS) self->lists[i] = NewList();
	if (f == NULL) SetHasher(self, SimpleHasher);
	return(self);
}

void DelHash(Hash const X) 
{
	int i=0;
	while (i++ < MAXLISTS) DelList(GetBuckets(X, i));
}

Hash HashIns(Hash const self, const Thing const T) 
{
	ListIns(GetBuckets(self, GetHasher(self)(T)), T);
	return(self);
}

Thing HashGet(const Hash const self, const Thing const T)
{
	return(ListGet(GetBuckets(self, GetHasher(self)(T)), T));
}

Thing HashRem(Hash const self, const Thing const T)
{
	return(ListRem(GetBuckets(self, GetHasher(self)(T)), T));
}


