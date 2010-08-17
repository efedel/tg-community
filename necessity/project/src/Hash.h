#ifndef Hash_h
#define Hash_h

#define MAXLISTS 4095

typedef int (*HashFN)(const Thing const T);
typedef struct Hash_t * Hash;
struct Hash_t
{
	List lists[MAXLISTS];
	HashFN hasher;
};

Hash NewHash(const HashFN const HFN);
void DelHash(Hash const H);

Hash  HashIns(Hash const self, 
	      const Thing const key, 
	      const Thing const item);
Thing HashGet(const Hash const self, const Thing const key);
Thing HashRm(Hash const self, const Thing const T);

#endif