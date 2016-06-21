#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int global;

void * thread(void *joiner)
{
	void *status;

	global = pthread_self();
	sleep(1);
	printf("Parent PID is %d, TID is %d, global = %d\n",
		getppid(), pthread_self(), global);

	if (joiner) {
		if (pthread_join((pthread_t)joiner, &status)) {
			exit(1);
		}
	}

	pthread_exit((void*) 0);
}

int main(void)
{
	void           *status;
	int             x;
	pthread_attr_t  attr;
	pthread_t       curr_thr_id;
	pthread_t       prev_thr_id;

	if (pthread_attr_init(&attr)) {
		exit(1);
	}
	if (pthread_attr_setschedpolicy(&attr, SCHED_RR)) {
		exit(1);
	}

	/* Start 3 threads */
	prev_thr_id = 0;
	for (x=0; x<3; x++) {
		if (pthread_create(&curr_thr_id, &attr, thread, (void*)prev_thr_id)) {
			exit(1);
	        }
		prev_thr_id = curr_thr_id;
	}

	/* Join last thread */
	pthread_join(curr_thr_id, &status);
}
