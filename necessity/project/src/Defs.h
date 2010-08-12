#ifndef Defs_h
#define Defs_h

#define MAXCOL 80

typedef unsigned int uint;

typedef char * CharBuf;
typedef void * Pointer;

typedef enum Boolean_t { FALSE, TRUE } BOOLEAN;	/* Boolean */ 
typedef enum Ufo_t { LT = -1 , EQ = 0, GT = 1, UFOERR } UFO;	/* <=> */

void (*PureSideEffect)();

#endif
