#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Defs.h"
#include "Thing.h"
#include "List.h"
#include "Hash.h"

/* This data structure is a composite data structure,  made up of the List 
 * datastructure.  It effectively uses the existing framework. */ 

/* standard key item pair */
typedef struct HashKeyPair_t * HashKeyPair;
struct HashKeyPair_t
{
	Thing Key;
	Thing Item;
};

/* setters */
static HashKeyPair SetHashKeyPairItem(const HashKeyPair const kp, 
		                      const Thing const item) 
{ 
	kp->Item = item; 
	return(kp); 
}

static HashKeyPair SetHashKeyPairKey (const HashKeyPair const kp,
				      const Thing const key)
{
	kp->Key = key; 
	return(kp); 
}

/* getters */
static Thing GetHashKeyPairItem(const HashKeyPair const kp){ return(kp->Item); }
static Thing GetHashKeyPairKey (const HashKeyPair const kp){ return(kp->Key); }

static HashKeyPair NewHashKeyPair(const Thing const key, const Thing const item)
{
	HashKeyPair self = (HashKeyPair)malloc(sizeof(struct HashKeyPair_t)); 
	return(SetHashKeyPairItem(SetHashKeyPairKey(self, key), item));
}

/* this has to fit the Thing's dtor sig of void fn(pointer) */
static void DelHashKeyPair(Pointer const kp)
{
	SetHashKeyPairKey ((HashKeyPair)kp, NULL);
	SetHashKeyPairItem((HashKeyPair)kp, NULL);
	free(kp);
}

/* we really only use this for the == function */
static UFO UFOHashKeyPair(const Thing T1, const Thing T2)
{
	/* Get T1's , T2's HashKeyPair
	 * Get hkp1's hkp2's Key
	 * run their equiv */
	HashKeyPair hkp1 = (HashKeyPair)GetThingData(T1);
	HashKeyPair hkp2 = (HashKeyPair)GetThingData(T2);
	Thing key1       = GetHashKeyPairKey(hkp1);
	Thing key2	 = GetHashKeyPairKey(hkp2);
	return(ThingCmp(key1, key2));	
	// uncommend the following when you've debugged it
	/*
	return(ThingCmp(
			GetHashKeyPairKey((HashKeyPair)GetThingData(T1))
			GetHashKeyPairKey((HashKeyPair)GetThingData(T2)))); */
}

/* this is to print out a hash key pair */
static String StringHashKeyPair(const Thing const T)
{
	int len = 0;
	HashKeyPair hkp = (HashKeyPair)GetThingData(T);
	/* remember to delete these */
	String key  = ThingToString(GetHashKeyPairKey(hkp));
	String item = ThingToString(GetHashKeyPairItem(hkp));
	len = LenStr(key) + LenStr(item) + strlen("(=>)");
	char buf[len];
	snprintf("(%s=>%s)", len, key, item);
	DelStr(key);
	DelStr(item);
	return(NewStr(buf));
}

// TODO: resize

static List  GetBuckets(const Hash const self, const uint index) 
{ 
	if (self->Lists[index]) return(self->Lists[index]); 
		/* we haven't made a new list yet */
	else return(self->Lists[index]=NewList());
}
static HashFN GetHasher(const Hash const self) { return(self->Hasher); }

static void SetBuckets(Hash const self, const uint index, const List const L) 
{
	self->Lists[index] = L;
}

static void SetHasher(Hash const self, const HashFN const f) { self->Hasher=f; }

/* very simple and stupid hash function, there are probably better */
static uint SimpleHasher(const Thing const T)
{
	uint x=(uint) T; // get the pointer value
	return(x%MAXLISTS);
}

Hash NewHash(const HashFN const f)
{
	int i;
	Hash self = (Hash)malloc(sizeof(struct Hash_t));
	/* lazy load */
	
	/* we set GetLists to check to see if the Lists[index] exists
	 * if not we make a new one. */
	for (i=0; i<MAXLISTS; i++) SetBuckets(self, i, NULL);
	
	//for(i=0; i < MAXLISTS; i++) SetBuckets(self, i, NewList());
	//if (f == NULL) SetHasher(self, SimpleHasher);
	SetHasher(self, (f == NULL) ? SimpleHasher : f);
	return(self);
}

void DelHash(Hash const X) 
{
	int i;
	for(i=0; i < MAXLISTS; i++) DelList(GetBuckets(X, i));
}

/* refactor */
/* TODO: Thingify should be THE INTERFACE. if every "class" has an impl of
 * Thingify, it will make sure they all have the right fns defined.  I can
 * see why stroussoup called this an "abstract" class. */
static Thing ThingifyHKP(HashKeyPair hkpair) 
{
	return(NewThing(POINTER, 
			hkpair, 
			DelHashKeyPair, 
			UFOHashKeyPair, 
			NULL, 
			StringHashKeyPair));
}

static Thing ThingToKey(Thing T) 
{ 
	return(ThingifyHKP(NewHashKeyPair(T, NULL))); 
} 

Thing HashGet(const Hash const self, const Thing const KeyThing)
{
	Thing ret = NULL;
	//return(ListGet(GetBuckets(self, GetHasher(self)(T)), T));
	//HashFN F = GetHasher(self);
	//List L = GetBuckets(self, F(key));
	//return(ListTop(GetBuckets(self, GetHasher(self)(key))));
	
	/* get the bucket list */
	/* we need to make a tmp key, because of the invariant that 
	 * we can only compare 2 Thigns of the same type it has to 
	 * be a HKP, but we can have the item NULL */
	/* do NOT inline this you need to DELETE it later */
	Thing    tmpbucket = ThingToKey(KeyThing);

	List l         = GetBuckets(self, GetHasher(self)(KeyThing));
	/* don't bother to check if the list is size 0 */
	if (GetListSize(l)) 
	{ 
		Thing tmp      = ListGet(l, tmpbucket);
		// TODO this line is unsafe; we should have a check
		HashKeyPair kp = (HashKeyPair)GetThingData(tmp);
		ret = (GetHashKeyPairItem(kp)); 
	}
	/* cleanup: delete the tmpbucket and the tmpkey */
	DelThing(tmpbucket); /* the Thing dtor will call the  HKP dtor. */
	return(ret);
}


/* TODO: you can probably refactor the code so that GetBuckets takes in 
 * HashIns, HashGet or HashRm function  but not right now.*/
Hash HashIns(Hash const self, 
	     const Thing const key,
	     const Thing const item) 
{
	/* check to see if it's not in there already */
	/* key + item -> key item pair */
	HashKeyPair kptmp = NewHashKeyPair(key, item);
	uint ndx = GetHasher(self)(key);
	List l = GetBuckets(self, ndx);
	/* we could do cool tricks here with trying to queue up
	 * multiple items for one key, but for right now we're going
	 * to follow the C++ standard, where insert destroys items
	 * on the same key */
	if (GetListSize(l) != 0) 
	{
		DelList(l); /* if we've got a list on there already, kill it */
		l = NewList(); /* make new one and assign to that bucket index */
		SetBuckets(self, ndx, l);
	}
	/* insert the encapsulated thing into the list */	
	ListIns(l, ThingifyHKP(kptmp));
	return(self);
}

/* TODO: 
 * two things to refactor here: HashRm, HashIns, and HashGet are probably all
 * the same; just need to pass a function in to get them to work */
/* second thing is we want a function that takes in a Thing as a key and 
 * returns a Thing that holds a HashKeyPair */

Thing HashRm(Hash const self, const Thing const KeyThing)
{
	Thing ret = NULL;
	/* DO NOT INLINE THIS BECAUSE YOU NEED TO DELETE IT LATER */
	Thing    tmpbucket = ThingToKey(KeyThing);
	List l             = GetBuckets(self, GetHasher(self)(KeyThing));
	if (GetListSize(l))
	{
		Thing tmp  = ListRm(l, tmpbucket);
		HashKeyPair kp = (HashKeyPair)GetThingData(tmp);
		ret = (GetHashKeyPairItem(kp));
	}
	DelThing(tmpbucket);
	return(ret);
}


