#include "stdio.h"
#include "stdlib.h"
#include "mqueue.h" /* this header file is required */
#include "sys/stat.h"
#include "string.h"
#include "signal.h"
#include "setjmp.h"

int msg_analyze (char *);

int main (void)
{
	int status = 0;
	
	/* create the message queue variable */

	/* create and initialize the message queue attribute structure */
	/* don't forget the type for the structure */
	struct "type"  attr =
	{
	};
	
	char recd_msg[100];
	
	/* create message queue analyze_q.  check that the call succeeds */

	/* make the message queue receive call here */	
	
	/* this call analyzes the string received from the queue */
	status = msg_analyze(recd_msg);
		
	/* use the close and unlink calls to make debugging easier */	
	
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

