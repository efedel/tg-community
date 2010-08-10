#ifndef Defs_h
#define Defs_h

#define MAXCOL 80

typedef unsigned int uint;

typedef char * CharBuf;
typedef void * Pointer;

typedef enum Boolean_t { FALSE, TRUE } BOOLEAN;	/* Boolean */ 
typedef enum Ufo_t { LT, EQ, GT } UFO;		/* <=> */

void (*PureSideEffect)();

#endif
