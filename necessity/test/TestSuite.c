#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "Api.h"

void Test( int x, int y, int lnum, bool polarity ); 
#define EQ(X, Y)  Test( ( int )X, ( int )Y, __LINE__, true  )
#define NEQ(X, Y) Test( ( int )X, ( int )Y, __LINE__, false )

#define MAXCOUNT 100

typedef struct Coords_t * Coords;
typedef struct Coords_t
{
	uint x;
	uint y;
};

void killerfoo(Pointer ACoord)
{
	printf("killerfoo: ");
	Coords tmp=(Coords) ACoord;
	printf("free(%p)\n", ACoord);
	//printf("freeing the coords (%d, %d)! \t", tmp->x, tmp->y);
	fflush(stdout);
	free(ACoord); // should free the coords
}

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
		foo->x=555, foo->y=MAXCOUNT-i;
		things[i] = NewThing((Pointer) foo, POINTER, killerfoo);
		addrs[i]  = (uint)foo;
		printf("(%d, %d)\n", ((Coords)GetData(things[i]))->x, 
				     ((Coords)GetData(things[i]))->y);
	}
	for (i = 0; i < MAXCOUNT; i++)
	{
		printf("deleting arr[%d]\n", i);
		if (addrs[i] == (uint)GetData(things[i])) 
		{ 
			printf("%p: %d is ok\n", (void*)addrs[i], i); 
		}
		if (GetType(things[i])==POINTER) { printf("found a pointer\n"); }
		DelThing(things[i]);
	}
}

int main( int argc, char * argv[] )
{
	
	printf("Starting tests\n");	
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
	printf( "%s\n", __FILE__ );
	char * tmp = ( char * )malloc( sizeof( char )*strlen( str ) ); 
	sprintf( tmp, "%s", testphrase );
	char * buf = String( tmp );
	EQ ( strcmp( buf, testphrase ), 0 );

	MassTestThing();
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
