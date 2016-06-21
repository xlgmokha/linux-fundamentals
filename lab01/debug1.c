#include <stdio.h>

int *a;

void a_badidea(void);

int main(int argc, char *argv[])
{
	int x=5;

	int y;
	int z = 16;
	
	a_badidea();
	
	printf("Hello World! x=%d, y=%d\n", x,y);
	
	return(0);
}

void a_badidea (void)
{
	int z = 16;
	*a = z;
}
