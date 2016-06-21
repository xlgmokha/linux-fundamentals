#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int global;

int main()
{
	/* 
	   Have the parent fork() a child twice
	   Use the return value of fork() to make sure you're the 
	   parent before forking a second child
	*/

	/* Your code here */

	/* All 3 processes (parent and children) run the following */

	global = getpid();     /* set to a process-specific value */
	sleep(1);
	printf("PID is %d, global = %d\n", getpid(), global);
}
