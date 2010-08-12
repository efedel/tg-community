#include <stdio.h>
#include <string.h>

#include "Defs.h"

Pointer GetESP() { asm("mov %esp, %eax"); }

void CommentLine(const CharBuf s) 
{
	int i=0;
	int len=0; 
	CharBuf pre = "/* ";
	CharBuf end = " */";
	printf("%s", pre);
	if (s != NULL) 
	{
		len = strlen(s)+1; /* for the extra space after the word */
		printf("%s ", s);
	}
	/* trying to get out of the habit of writing for loops, since 
	 * for is out, and foreaches are in */
	while (i++ < (MAXCOL-(strlen(pre)+strlen(end)+len))) printf("-");
	printf("%s\n", end);
}

void println(CharBuf cstr)
{
	printf("%s\n", cstr);
}
