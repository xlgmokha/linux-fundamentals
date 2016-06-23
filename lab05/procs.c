#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int global;

int main()
{
	if (fork()) {          /* only the 1st parent enters here */
		fork();        /* ...to fork() a 2nd child...     */
	}

	/* All 3 processes (parent and children) run the following */

	global = getpid();     /* set to a process-specific value */
	sleep(1);
	printf("PID is %d, global = %d\n", getpid(), global);
}
