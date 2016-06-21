#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

volatile pthread_t   running;
volatile int         thread_switches;
volatile int         done = 0;

void * thread(void *x)
{
	pthread_t self = pthread_self();
	long long self_count = 0;
	long long avg = 0;
	int       avg_calculations = 0;

	/* let all threads start */
	sleep(1);

	while(1) {
		if (running == self) {   /* still this thread running */
			self_count++;
			/*
			 * Safety net -- when running high priority we can prevent
			 * main() from running and stopping the program.
			 */
			if (self_count > 100000000) break;
		} else {                 /* just switched to this thread */
			running = self;
			thread_switches++;

			if(self_count)
			{
				/* Re-calculate average */
				avg *= avg_calculations;
				avg += self_count;
				avg_calculations++;
				avg /= avg_calculations;
			}

			/*
			 * Another safety net
			 */
			if (done || (thread_switches > 300)) break;

			self_count = 1;
		}
	}
	printf("Thread %d exiting, average count between switches = %lld, self_count = %lld\n",
		*(int *)x, avg, self_count);
	pthread_exit((void*) 0);
}

int main(void)
{
	void *status;
	pthread_attr_t  attr;
	pthread_t       t1, t2;
	struct sched_param  param;
	int one=1;
	int two=2;

	/* Add your scheduler setup logic here */

	if (pthread_create(&t1, &attr, thread, &one)) exit(1);
	if (pthread_create(&t2, &attr, thread, &two)) exit(1);

	sleep(10);  /* let program run 10 seconds */
	done = 1;
	pthread_join(t1, &status);
	pthread_join(t2, &status);
	printf("Total thread switches: %d\n", thread_switches);
	exit(0);
}
