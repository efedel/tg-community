#include <stdio.h>
#include <string.h>

#include "Defs.h"

Pointer GetESP() { asm("mov %esp, %eax"); }

void CommentLine() 
{
	int i=0;
	CharBuf pre = "/* ";
	CharBuf end = " */";
	printf("%s\n", pre);
	/* trying to get out of the habit of writing for loops, since 
	 * for is out, and foreaches are in */
	while (i++ < (MAXCOL-(strlen(pre)+strlen(end)))) printf("-");
	printf("%s\n", end);
}

void println(CharBuf cstr)
{
	printf("%s\n", cstr);
}
