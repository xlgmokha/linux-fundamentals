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
	struct timeval initial  = {0, 1000000/RATE};
	struct timeval interval = {0, 1000000/RATE};
	struct itimerval t;

	t.it_value = initial;
	t.it_interval = interval;
	if (signal(SIGALRM, alarm_handler) != SIG_ERR) {
		if (!setitimer(ITIMER_REAL, &t, 0)) {
			/* Perform other tasks waiting for our SIGALRMs */
			while(count <= 50) {
				;
			}
		}
	}
	exit(0);
}
