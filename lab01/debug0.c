#include <stdio.h>
#include <string.h>
int *a;

int main(int argc, char *argv[])
{
	int x=5;
	int y;
	
	sleep(4);
	
	y = atoi(argv[1]);
	
	printf("Hello World! x=%d, y=%d\n", x,y);
	
	return(0);
}

