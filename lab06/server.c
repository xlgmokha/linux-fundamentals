#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <syslog.h>
#include <time.h>

static void daemonize(void)
{
	int i;

	/* fork once to go into the background */
	switch(fork())
	{
		case 0: break; /* child */
		case -1: exit(1); /* error */
		default: exit(0); /* parent */
	}

	/* get a new process group/session, no controlling terminal */
	if(setsid()<0) exit(1);

	/* change the file mode mask */
	umask(0);

	/* close all descriptors */
	for (i=sysconf(_SC_OPEN_MAX);i>=0;--i) close(i);

	/* run in a specific directory */
	chdir("/");

	/* redirect stdio */
	open ("/dev/null",O_RDWR);
	(void) dup(0);
	(void) dup(0);

	/* we are now a daemon */
}

void hup_handler(int x)
{
	syslog(LOG_DAEMON | LOG_INFO, "Server received SIGHUP at %d\n", time(0));
	signal(SIGHUP, hup_handler);
}

int main()
{
	daemonize();
	if (signal(SIGHUP, hup_handler) == SIG_ERR) {
		syslog(LOG_DAEMON | LOG_INFO, "Server failed to install signal handler\n");
	}

	while(1) {
		sleep(1);
	}
}
