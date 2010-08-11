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
}

#define MAXCOUNT 100 

void MassTestThing()
{
	uint i=0;
	uint   addrs[MAXCOUNT];
	Thing things[MAXCOUNT];
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

void StrTests() 
{
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

#define TOSTRINGINTTHINGSBUF 80
CharBuf ToStringIntThings(const Thing const T)
{
	char buf[TOSTRINGINTTHINGSBUF];
	int i = (int)GetThingData(T);
	// Bad coding but we're going to say 80 is max here.
	snprintf((char*)&buf, TOSTRINGINTTHINGSBUF, "%d", i);
	return(String(buf));
}

void ListTest()
{
	int i;
	Thing T;
	List L = NewList();
	DelList(L);
	printf("deleted empty list\n");
	L = NewList();
	Thing things[MAXCOUNT];
	for (i=0; i<MAXCOUNT; i++)
	{
		T = NewThing(INTEGER, 
			     (Pointer) i, 
			     NULL,  // no need for dtor 
			     CompareIntThings,  
			     NULL,  // no need to copy 
			     ToStringIntThings);
		things[i]=T;
		//printf("made: >>%s<<\n", ThingToString(T));
		InsItemList(L, T);
	}
	//asm("int3");
	for (i=0; i<MAXCOUNT; i++)
	{
		if (strcmp(ThingToString(things[i]), 
			  ThingToString(GetItemList(L, things[i]))) != 0)
		{
			printf("*** no match\n");
			printf("%s ",ThingToString(things[i]));
			printf("!= %s\n", ThingToString(GetItemList(L, things[i])));
		}
	}
	DelList(L);
	fflush(stdout);
	printf("Done ListTest(), write DelItemList next time!\n");
}

void TestASM()
{
	CommentLine();
	println("testing asm");
	printf("ESP: %p\n", GetESP());
}


int main( int argc, char * argv[] )
{
	printf("Starting tests\n");	
	printf( "%s\n", __FILE__ );
	StrTests();	
	MassTestThing();
	ListTest();
	TestASM();
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
