#ifndef String_h
#define String_h

#include "Defs.h"

/* Makes a new string: */
CharBuf String(const CharBuf);  /* Forgot C had a const. */

/* Deletes a string: */
void DelStr( CharBuf );

/* returns the length of a string: */
uint LenStr( CharBuf );

#endif
