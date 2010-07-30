#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "TaggedString.h"

void Test( int x, int y, int lnum, bool polarity ); 
#define EQ(X, Y)  Test( ( int )X, ( int )Y, __LINE__, true  )
#define NEQ(X, Y) Test( ( int )X, ( int )Y, __LINE__, false )

int main( int argc, char * argv[] )
{
	printf("Starting tests\n");	
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
	printf( "%s\n", __FILE__ );
	char * tmp = ( char * )malloc( sizeof( char )*strlen( str ) ); 
	sprintf( tmp, "%s", testphrase );
	char * buf = NewStr( tmp );
	EQ ( strcmp( buf, testphrase ), 0 );
	//TS_substring_p?
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
