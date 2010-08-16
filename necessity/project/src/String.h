#ifndef String_h
#define String_h

#include "Defs.h"

/* Makes a new string: */
String NewStr(const char * const);  /* Forgot C had a const. */

/* Deletes a string: */
void DelStr(String);

/* returns the length of a string: */
uint LenStr(const String const);

#endif
