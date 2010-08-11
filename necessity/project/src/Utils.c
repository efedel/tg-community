#include <stdio.h>
#include <string.h>

#include "Defs.h"

Pointer GetESP() { asm("mov %esp, %eax"); }

void CommentLine() 
{
	int i;
	CharBuf pre = "/* ";
	CharBuf end = " */";
	printf("%s\n", pre);
	for (i=0; i<(MAXCOL-(strlen(pre)+strlen(end))); i++) 
	{
		printf("-");
	}

	printf("%s\n", end);

}

void println(CharBuf cstr)
{
	printf("%s\n", cstr);
}
