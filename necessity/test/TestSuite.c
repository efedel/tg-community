#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "Api.h"

void Test( int x, int y, int lnum, bool polarity ); 
#define EQ(X, Y)  Test( ( int )X, ( int )Y, __LINE__, true  )
#define NEQ(X, Y) Test( ( int )X, ( int )Y, __LINE__, false )

typedef uint (*MapUintToUintFN)(uint);

typedef struct Coords_t * Coords;
typedef struct Coords_t
{
	uint x;
	uint y;
};

static void killerfoo(Pointer ACoord)
{
	printf("killerfoo: free(%p)\n", ACoord);
	Coords tmp=(Coords) ACoord;
	printf("freeing the coords (%d, %d)! \t", tmp->x, tmp->y);
	fflush(stdout);
	free(ACoord); // should free the coords
	printf("\n");
}

#define MAXCOUNT 100 

static void MassTestThing()
{
	uint i=0;
	uint   addrs[MAXCOUNT];
	Thing things[MAXCOUNT];
	CommentLine("Test Things en masse.");
	printf("MassTestThing()\n");
	Coords foo;
	for (i = 0; i < MAXCOUNT; i++)
	{
		foo=(Coords)malloc(sizeof(struct Coords_t));	
		printf("new coords %p\n", (void*)foo);
		foo->x=i, foo->y=MAXCOUNT-i;
		things[i] = NewThing(POINTER, 
				     (Pointer) foo, 
				     killerfoo, 
				     NULL, 
				     NULL, 
				     NULL);
		addrs[i]  = (uint)foo;
		printf("(%d, %d)\n", ((Coords)GetThingData(things[i]))->x, 
				     ((Coords)GetThingData(things[i]))->y);
	}
	for (i = 0; i < MAXCOUNT; i++)
	{
		printf("deleting arr[%d]\n", i);
		if (addrs[i] == (uint)GetThingData(things[i])) 
		{ 
			printf("%p: %d is ok\n", (void*)addrs[i], i); 
		}
		if (GetThingType(things[i])!=POINTER) { printf("error not a pointer\n"); }
		DelThing(things[i]);
	}
}

static void TestStr() 
{
	CommentLine("Test String");
	EQ ( 1, 1 );
	NEQ( 1, 232 );
	char * testphrase = "Hello world.";
	char * str = NewStr( testphrase );
	NEQ( strlen( str ), 0 );
	NEQ( LenStr( str ), 0 );
	EQ ( strlen( str ), LenStr( str ) );
	EQ ( strcmp( testphrase, str ), 0 );
	NEQ( str, NULL );
	DelStr( str );
	char * tmp = ( char * )malloc( sizeof( char )*strlen( str ) ); 
	sprintf( tmp, "%s", testphrase );
	String buf = NewStr( tmp );
	EQ ( strcmp( buf, testphrase ), 0 );
}

static UFO CompareIntThings(const Thing const T1, const Thing const T2)
{
	int one = (int)GetThingData(T1);
	int two = (int)GetThingData(T2); 

	if      (one < two) return(LT);
	else if (one > two) return(GT);
	else return(EQ);
}

static void TestList()
{
	int i;
	Thing T;
	List L = NewList();
	DelList(L);
	CommentLine("Test List");
	printf("deleted empty list\n");
	L = NewList();
	Thing things[MAXCOUNT];
	for (i=0; i<MAXCOUNT; i++)
	{
		T = Word(i);
		things[i]=T;
		//printf("made: >>%s<<\n", ThingToString(T));
		ListIns(L, T);
	}
	//asm("int3");
	String s1, s2;
	for (i=0; i<MAXCOUNT; i++)
	{
		// seperate assignments are NECESSARY because if i assign
		// inline with strcmp(ThingToString ... ) they will never 
		// get deleted and it will be a memory leak!!
		s1 = ThingToString(things[i]);
		s2 = ThingToString(ListGet(L, things[i]));
		if (strcmp(s1, s2) != 0)
		{
			printf("*** no match\n");
			printf("%s ",ThingToString(things[i]));
			printf("!= %s\n", ThingToString(ListGet(L, things[i])));
		}
		DelStr(s1); // sigh, there is no real way around this.
		DelStr(s2); 
	}
	DelList(L);
	fflush(stdout);
	printf("Done ListTest(), write ListRem next time!\n");
}

static void TestASM()
{
	CommentLine("TestASM");
	println("testing asm");
	printf("Accumulator EAX: %p\n", GetEAX());
	printf("Base        EBX: %p\n", GetEBX());
	printf("Counter     ECX: %p\n", GetECX());
	printf("Data        EDX: %p\n", GetEDX());

	printf("src str ndx ESI: %p\n", GetESI());
	printf("dst str ndx EDI: %p\n", GetEDI());

	printf("stack top   ESP: %p\n", GetESP());
	printf("frame base  EBP: %p\n", GetEBP());
//	printf("insn ptr    EIP: %p\n", GetEIP());

	printf("code segment CS: %p\n", GetCS());
	printf("stack        SS: %p\n", GetSS());

	printf("data segment DS: %p\n", GetDS());
	printf("data segment ES: %p\n", GetES());


}

static void AddAnswer(Hash const H, const uint key, const uint item)
{
	HashIns(H, Word(key), Word(item));
}

static int FactHasher(const Thing const T)
{
	return((IntWord(T))%MAXLISTS);
}

static uint LookupAnswer(Hash const H, const uint x)
{
	Thing wx  = Word(x);
	Thing ans = HashGet(H, wx);
	//if (ans) printf("Found answer!\n");
	return((ans) ? (uint)IntWord(ans) : 0);
}

static uint Factorial(Hash const H, const uint n)
{
	int ans;
	if (n==0) return 1;
	else 
	{
		ans = LookupAnswer(H, n);
		if (!ans) 
		{
			ans = n * Factorial(H, n-1);
			AddAnswer(H, n, ans);
		}
		return ans;
	}
	return 0;
}

static uint FactCheck(uint n)
{
	if (n==0) return 1;
	else return(n*FactCheck(n-1));
}


bool TestCheckBufferWithFunction(const uint * const arr, 
				    uint size,  
				    MapUintToUintFN fn)
{
	// let fn be the correct function; not the thing we are testing
	uint i;
	uint y=0;
	for (i=0; i<size; i++) 
	{
		y = fn(i);
		if (arr[i] != y) 
		{
			printf("Error where f(%d) = %d, should be %d\n", 
				i, arr[i], y);
			return(false);
		}
	}
	return(true);
}

#define TESTFACTORIALMAX 14
void TestFactorial()
{
	uint c;
	uint checkbuff[14];
	//const uint * const here = checkbuff;
	Hash H = NewHash(FactHasher);
	for (c=0; c<TESTFACTORIALMAX; c++) 
	{
		checkbuff[c] = Factorial(H, c);
		//printf("%d\n", Factorial(H, c));
	}
	//asm("int3");
	if (TestCheckBufferWithFunction(checkbuff, 
				TESTFACTORIALMAX,
				FactCheck) == false) printf ("test failed.\n");
	DelHash(H);
}

void TestHash()
{
	Thing key  = Word(7);
	Thing item = Word(11);
	Thing X;
	CommentLine("Testing Hashtable");
	Hash H = NewHash(NULL);
	
	HashIns(H, key, item);
	//BAD CODE: if (IntWord(HashGet(H, key)) != 11) 
	//{ printf("no match!\n"); }
	//HashGet can return NULL!
	X = HashGet(H, key);	
	if (ThingCmp(X, item) != EQ) printf("error in retr hash"); 
	DelHash(H);
	//asm("int3");
	printf("Basic insert/retrieve in hash table done.\n");

}

// not mine:
static uint FibCheck(uint n) { 
        if (n <= 0) { 
                return 0; 
        } else if (n <= 2) { 
                return n; 
        } else { 
                return Fibonacci(n - 1) + Fibonacci(n - 2); 
        }
}

#define TESTFIBITERMAX 40
static void TestFibiter() 
{
	uint checkbuff[TESTFIBITERMAX];
	checkbuff[0]=0;
	checkbuff[1]=1;
	checkbuff[2]=2;
	CommentLine("Testing Fib");
	int c;
	for (c=0; c<TESTFIBITERMAX; c++) 
	{
		checkbuff[c] = Fibonacci(c);
		//printf("fib(%d)=%d\n", c, checkbuff[c]);
	}
	for (c=3; c<TESTFIBITERMAX; c++)
		if (checkbuff[c] != (checkbuff[c-1] + checkbuff[c-2])) 
			printf("Issue with fib(%d) = %d\n", c, checkbuff[c]);
	if (TestCheckBufferWithFunction(checkbuff, TESTFIBITERMAX,
				FibCheck) == false) printf ("test failed.\n");
}



int main( int argc, char * argv[] )
{
	printf("Starting tests\n");	
	printf( "%s\n", __FILE__ );
	TestStr();	
	MassTestThing(); 
	TestList();
	TestASM();
	TestHash();
	TestFactorial();
	TestFibiter();
	return -0;
}

void Test( int x, int y, int lnum, bool polarity )   
{ 
	char buf[1024];
	bzero( &buf, 1024 );
	bool result = ( x == y ? true : false ); 
	
	if ( polarity != result ) 
	{ 
		sprintf( ( char * )&buf, "test fail at line %d\n", lnum ); 
		perror( buf );
	}
}
