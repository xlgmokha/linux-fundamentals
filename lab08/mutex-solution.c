/* Example code to demonstrate behavior of multi-core, threaded application
 *
 * Written by:  Mike Anderson
 *              The PTR Group, Inc.
 *              mike@theptrgroup.com
 *
 * License: GPLv2
 *
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#ifndef	TRUE
#define	TRUE	1
#define	FALSE	0
#endif


pthread_mutex_t mutex_fix;		/* protect the critical region */

pthread_t looperThId;
pthread_t conflictThId;

volatile int value1;
volatile int value2;
volatile int counter = 0;
volatile int bTimeToExit = FALSE;

int bUseMutex = FALSE;		/* The "s" option */


/* Conflict thread */
void *conflictTh(void *arg)
{
	int same;
	unsigned long loopCount = 0;
	struct timespec sleep_time = {
		.tv_sec = 0,
		.tv_nsec = 7 * 1000 * 1000,
	};

	while (!bTimeToExit) {
		if (bUseMutex) {
			pthread_mutex_lock(&mutex_fix);
		}

		same = (value1 == value2);
		if (!same)
			printf("\nHey! value1 = %d, value2 = %d\n", value1,
			       value2);

		loopCount++;
		if ((loopCount % 1000) == 0) {
			printf("\nConflict thread Counter = %lu \n", loopCount);
			fflush(stdout);
			counter = 0;
		}

		if (bUseMutex) {
			pthread_mutex_unlock(&mutex_fix);
		}

		/* Sleep for 7ms */
		nanosleep(&sleep_time, NULL);
	}
	
	return NULL;
}

/* Main loop thread */
void *looperTh(void *arg)
{
	int counterTemp;
	struct timespec sleep_time = {
		.tv_sec = 0,
		.tv_nsec = 13 * 1000 * 1000,
	};


	/* give the conflict thread a chance to start */
	sleep(1);

	while (!bTimeToExit) {
		if (bUseMutex) {
			pthread_mutex_lock(&mutex_fix);
		}

		value1 = counter;
		value2 = counter;
		counterTemp = counter++;

		if (bUseMutex) {
			pthread_mutex_unlock(&mutex_fix);
		}

		if ((counterTemp % 1000000) == 0) {
			printf("Main loop counter = %d \r", counterTemp);
			fflush(stdout);

			/* Sleep for 13ms */
			nanosleep(&sleep_time, NULL);
		}
	}
	
	return NULL;
}

/* Ctrl-C Signal Handler */
void gotCtrlC(int sig)
{
	printf("\nGot Ctrl-C! Shutting down...\n");

	bTimeToExit = TRUE;
}

void print_usage(char *program)
{
	fprintf(stderr, "Usage: %s [options]\n%s", program,
		"-h This help\n"
		"-s (Use mutex to enforce synchronization)\n");
}

void parse_options(int argc, char *argv[])
{
	int c;

	opterr = 0;		/* get opt stuff */

	while ((c = getopt(argc, argv, "hs")) != -1) {
		switch (c) {
		case 's':
			bUseMutex = TRUE;
			break;
		case '?':
			if (isprint(optopt))
				fprintf(stderr, "Unknown option '-%c'.\n",
					optopt);
			else
				fprintf(stderr,
					"Unknown option character '\\x%x'.\n",
					optopt);
			/*FALLTHRU*/
		case 'h':
		default:
			print_usage(argv[0]);
			exit(EXIT_SUCCESS);
		}
	}

	printf("Options in effect:\n");
	if (bUseMutex)
		printf("    Thread synchronization using mutexes is in effect \n");
	else
		printf("    Mutex-based thread synchronization is off \n");
}

int main(int argc, char *argv[])
{
	int res;

	/* Parse the command line arguments */
	parse_options(argc, argv);

	printf("\nUse ^C to exit application...\n");

	/* Set up the ^C signal handler so we can shut down cleanly */
	(void)signal(SIGINT, gotCtrlC);

	/* Go ahead and initialize the mutex in case we need it */
	res = pthread_mutex_init(&mutex_fix, NULL);
	if (res != 0) {
		perror("Mutex initialization failed");
		exit(EXIT_FAILURE);
	}

	/* Create the main loop thread */
	res = pthread_create(&looperThId, NULL, looperTh, NULL);
	if (res != 0) {
		perror("Main loop thread creation failed");
		exit(EXIT_FAILURE);
	}


	/* Create the conflict thread */
	res = pthread_create(&conflictThId, NULL, conflictTh, NULL);
	if (res != 0) {
		perror("Conflict thread creation failed");
		exit(EXIT_FAILURE);
	}

	printf("\nMain is waiting for threads to finish...\n");
	res = pthread_join(conflictThId, NULL);
	if (res != 0) {
		perror("Thread join with conflictTh() failed");
		exit(EXIT_FAILURE);
	}
	res = pthread_join(looperThId, NULL);
	if (res != 0) {
		perror("Thread join with looperTh() failed");
		exit(EXIT_FAILURE);
	}

	printf("Threads joined -- exiting main\n");
	pthread_mutex_destroy(&mutex_fix);

	return EXIT_SUCCESS;
}
