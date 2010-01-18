// TaggedString.c
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef char * CharBuf;
typedef unsigned int uint;

uint get_len( void * rawbuf ) { return( ( uint ) rawbuf ); }

CharBuf get_buf( void * rawbuf )
{
	return( ( CharBuf ) rawbuf + sizeof( uint ) );
}

uint LenTagStr( CharBuf bstr ) 
{
	uint * tmp = (uint *) ( bstr - sizeof( uint ) );
	return *tmp;
}

CharBuf NewTagStr( const CharBuf rawstr ) 
{
	uint len = strlen( rawstr );
	void * rawbuf = malloc( sizeof( int ) + ( sizeof( char ) * len ) );
	uint * metadata = (uint *) rawbuf;
	*metadata = len;
	CharBuf buf = get_buf( rawbuf );
	strncpy( buf, rawstr, len );
	return buf;
}

void DelTagStr( CharBuf tagstr ) 
{
	free( tagstr - sizeof ( uint ) );		
}
