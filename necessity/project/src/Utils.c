#include <stdio.h>
#include <string.h>

#include "Defs.h"

Pointer GetEAX() { asm("mov %eax, %eax"); }
Pointer GetEBX() { asm("mov %ebx, %eax"); }
Pointer GetECX() { asm("mov %ecx, %eax"); }
Pointer GetEDX() { asm("mov %edx, %eax"); }
Pointer GetESI() { asm("mov %esi, %eax"); }
Pointer GetEDI() { asm("mov %edi, %eax"); }
Pointer GetESP() { asm("mov %esp, %eax"); }
Pointer GetEBP() { asm("mov %ebp, %eax"); }
//Pointer GetEIP() { asm("mov %eip, %eax"); }
Pointer GetCS() { asm("mov %cs, %eax"); } 
Pointer GetDS() { asm("mov %ds, %eax"); } 
Pointer GetSS() { asm("mov %ss, %eax"); } 
Pointer GetES() { asm("mov %es, %eax"); } 

#if 0
// TODO look at this later.
// I hate magic numbers but really, what register name > 32-11 chars?
#define GETREGMAXBUF 32 
Pointer GetReg(const char * const regname) 
{
	uint len = strlen(regname);
	if (len < 2 || len > 3) return(NULL); // error, what register is this?
	char buf[GETREGMAXBUF];
	snprintf(buf, GETREGMAXBUF, "mov %%%s, %%eax", regname);
	printf("%s\n", buf);
	asm(buf);
	return NULL;
}
#endif

void CommentLine(const char * const s) 
{
	int i=0;
	int len=0; 
	const char * const pre = "/* ";
	const char * const end = " */";
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

void println(const char * const cstr)
{
	printf("%s\n", cstr);
}

int Fibonacci(int n) 
{
	int i;
	int tmp[2];
	if (n <= 0) return(0);
	tmp[1]=1; // n=1     3
	tmp[0]=2; // n=2     
	for (i=3; i<=n; i++) tmp[i%2] = tmp[i%2] + tmp[(i-1)%2];
	return tmp[n%2];
}

