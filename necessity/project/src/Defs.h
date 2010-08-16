#ifndef Defs_h
#define Defs_h

#define MAXCOL 80

/* these are the two exceptions to the caps/naming conventions
 * mainly because they are used so often that making them 'feel'
 * like sta C will flow better */
typedef unsigned int uint;

typedef char * String;
typedef void * Pointer;

typedef enum Ufo_t { LT = -1 , EQ = 0, GT = 1, UFOERR } UFO;	/* <=> */

void (*PureSideEffect)();

#endif
