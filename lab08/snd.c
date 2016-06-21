#include "stdio.h"
#include "stdlib.h"
#include "mqueue.h" /* this header file is required */
#include "sys/stat.h"
#include "string.h"
#include "time.h"

#define MAX_CHAR 127
#define STR_SIZE 100

void give_string(char *);

int main (void)
{
	int status = 0;
	/* declare a message queue variable */

	char *sent_msg;
	struct mq_attr attr;
	
	/* open the message queue for writing.  don't forget to check the return value */
	
	sent_msg = (char *) malloc (100);
	if (NULL == sent_msg)
	{
		perror("malloc");
		exit(1);
	}
	
	/* give_string(sent_msg); this function generates a random string */
	/* you can use this or just send your own string */
	
	/* get the message queue attribute structure */

	/* send a message */
	
	free(sent_msg);
	
	status = mq_close(analyze_q);
	
	return(0);
}


void give_string(char *result)
{
	int j = 0;
	int i = 0;

	srand((unsigned)time(NULL));
	
	for (i=0;i<100;i++)
	{
		result[i] = (char) (1 + (int) (MAX_CHAR * (rand() / (RAND_MAX + 1.0))) );
	}
	
}

