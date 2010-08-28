#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "Defs.h"

/* internal use only -------------------------------------------------------- */
//static uint get_len(void * rawbuf) { return((uint)rawbuf); }

static char * ConvertToChars(void * rawbuf)
{
	return((char *)rawbuf + sizeof(uint));
}

/* String operations. ------------------------------------------------------- */

String NewStr(const char * const rawstr) 
{
	uint len = strlen(rawstr);
	/* strlen doesn't take into account the trailing /0 */
	uint real_len = len + 1;
	void * rawbuf = malloc(sizeof(int) + (sizeof(char) * real_len));
	uint * metadata = (uint *) rawbuf;
	*metadata = len; /* like strlen we ignore '\0' */
	char * buf = ConvertToChars(rawbuf);
	/* but of course strncpy, strcpy copies the \0 as well */
	strncpy(buf, rawstr, real_len);
	buf[real_len] = '\0';
	return buf;
}

void DelStr(String tagstr) 
{
	free(tagstr - sizeof(uint));		
}

uint LenStr(const String const bstr) 
{
	uint * tmp = (uint *)(bstr - sizeof(uint));
	return *tmp;
}

/* takes in a string, returns a substring of that string */
String SubStr(const String const str, const uint start, const uint end)
{
	char * tmpbuf = NULL;
	const char * tmp = str;	
	String ret;
	uint count = start;
	uint len = 1 + 1 + (end - start);  // len = end - str + 1 + '\0' 
	tmpbuf = (char *)malloc(sizeof(char)*len);
	while (count <= end) 
	{
		tmpbuf[count] = tmp[count];
		count++;
	}
	tmpbuf[len] = '\0'; // null term.
	ret = NewStr(tmpbuf);	
	free(tmpbuf);
	return(ret);
}
