#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "Defs.h"

uint get_len(void * rawbuf) { return((uint)rawbuf); }

String get_buf(void * rawbuf)
{
	return((String)rawbuf + sizeof(uint));
}

uint LenStr(const String const bstr) 
{
	uint * tmp = (uint *)(bstr - sizeof(uint));
	return *tmp;
}

String NewStr(const char * const rawstr) 
{
	uint len = strlen(rawstr);
	void * rawbuf = malloc(sizeof(int) + (sizeof(char) * len));
	uint * metadata = (uint *) rawbuf;
	*metadata = len;
	String buf = get_buf(rawbuf);
	strncpy(buf, rawstr, len);
	return buf;
}

void DelStr(String tagstr) 
{
	free(tagstr - sizeof(uint));		
}
