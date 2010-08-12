#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "Api.h"

void Test( int x, int y, int lnum, bool polarity ); 
#define EQ(X, Y)  Test( ( int )X, ( int )Y, __LINE__, true  )
#define NEQ(X, Y) Test( ( int )X, ( int )Y, __LINE__, false )


typedef struct Coords_t * Coords;
typedef struct Coords_t
{
	uint x;
	uint y;
};

void killerfoo(Pointer ACoord)
{
	printf("killerfoo: free(%p)\n", ACoord);
	Coords tmp=(Coords) ACoord;
	printf("freeing the coords (%d, %d)! \t", tmp->x, tmp->y);
	fflush(stdout);
	free(ACoord); // should free the coords
	printf("\n");
}

#define MAXCOUNT 100 

void MassTestThing()
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

void TestStr() 
{
	CommentLine("Test String");
	EQ ( 1, 1 );
	NEQ( 1, 232 );
	char * testphrase = "Hello world.";
	char * str = String( testphrase );
	NEQ( strlen( str ), 0 );
	NEQ( LenStr( str ), 0 );
	EQ ( strlen( str ), LenStr( str ) );
	EQ ( strcmp( testphrase, str ), 0 );
	NEQ( str, NULL );
	DelStr( str );
	char * tmp = ( char * )malloc( sizeof( char )*strlen( str ) ); 
	sprintf( tmp, "%s", testphrase );
	char * buf = String( tmp );
	EQ ( strcmp( buf, testphrase ), 0 );
}

UFO CompareIntThings(const Thing const T1, const Thing const T2)
{
	int one = (int)GetThingData(T1);
	int two = (int)GetThingData(T2); 

	if      (one < two) return(LT);
	else if (one > two) return(GT);
	else return(EQ);
}

void TestList()
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
	CharBuf s1, s2;
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

void TestASM()
{
	CommentLine("TestASM");
	println("testing asm");
	printf("ESP: %p\n", GetESP());
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
	if (ThingCmp(X, item) != 0) printf("error in retr hash"); 
	//asm("int3");

}


int main( int argc, char * argv[] )
{
	printf("Starting tests\n");	
	printf( "%s\n", __FILE__ );
	//TestStr();	
	//MassTestThing(); 
	//TestList();
	//TestASM();
	TestHash();
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
