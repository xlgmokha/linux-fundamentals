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
        // print addresses of stack, BSS, data, heap segments

	// for extra credit, print the address of the code segment
	while (1) {
		sleep(10);
	}
}
