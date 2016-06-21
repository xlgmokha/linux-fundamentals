#include "stdio.h"
#include "stdlib.h"
#include "mqueue.h"
#include "sys/stat.h"
#include "string.h"
#include "signal.h"
#include "setjmp.h"

int msg_analyze (char *);

int main (void)
{
	int status = 0;
	
	mqd_t analyze_q;
	struct mq_attr attr =
	{
			.mq_flags = 0,
			.mq_maxmsg = 10,
			.mq_msgsize = 100,
	};
	
	char recd_msg[100];
	
	/* create message queue ptr_q */
	analyze_q = mq_open("/analyze_q",O_RDONLY|O_CREAT,S_IWUSR|S_IRUSR, &attr);
	if (0 > analyze_q)
	{
		perror("mq_open");
		exit(1);
	}
	
	while (1)
	{

		status = mq_receive(analyze_q,(void *)&recd_msg[0],100,NULL);
	
		status = msg_analyze(recd_msg);
		
	}
	
	status = mq_close(analyze_q);
	status = mq_unlink("/analyze_q");
	
	return(0);
}

int msg_analyze (char *msg)
{
	int status = 0;
	int msg_len = 0;
	int ndigit = 0;
	int nlower = 0;
	int nupper = 0;
	int nother = 0;
	
	int i;
	
	status = msg_len = strlen(msg);
	
	for (i=0;i<msg_len;i++)
	{
		if ('0' <= msg[i] && '9' >= msg[i])
			++ndigit;
		else
		if ('a' <= msg[i] && 'z' >= msg[i])
			++nlower;
		else
		if ('A' <= msg[i] && 'Z' >= msg[i])
			++nupper;
		else
			++nother;
	}
	
	printf("\n\nThe message:\n\n\"%s\"\n\nhas %d characters,\n", msg, msg_len);
	printf("of which %d are digits,\n", ndigit);
	printf("%d are lowercase characters,\n", nlower);
	printf("%d are uppercase characters,\n", nupper);
	printf("and %d are white space or punctuation.\n", nother);
	
	return(0);
}

