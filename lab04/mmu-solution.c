#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int bssvar;
int datavar = 99;

int main()
{
	int stackvar;
	char *mallocptr = malloc(100);

	printf("\n");
	printf("Address of bss section var  = 0x%08x\n", (unsigned)&bssvar);
	printf("Address of data section var = 0x%08x\n", (unsigned)&datavar);
	printf("Address of stack var        = 0x%08x\n", (unsigned)&stackvar);
	printf("Address of malloc'd space   = 0x%08x\n", (unsigned)mallocptr);

	while (1) {
		sleep(10);
	}
}
