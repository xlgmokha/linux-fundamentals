#include <signal.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

#define RATE	5	/* 5 Hz */

int count = 0;

void alarm_handler(int x) {
	count++;
	if ((count > 0) && ((count % 10) == 0)) {
		printf("Number of timer callbacks: %d\n", count);
	}
	signal(SIGALRM, alarm_handler);
}

int main()
{
	/* define the initial and interval to run at 5 hz */
	struct timeval initial  = {0, ???/RATE};
	struct timeval interval = {0, ???/RATE};
	struct itimerval t;

	t.it_value = initial;
	t.it_interval = interval;

	/* install a signal handler for SIGALRM and start timer ticking */

	/* use the count variable to terminate after 10 seconds */

	exit(0);
}
