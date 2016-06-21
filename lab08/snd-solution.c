#include "stdio.h"
#include "stdlib.h"
#include "mqueue.h"
#include "sys/stat.h"
#include "string.h"
#include "time.h"

#define MAX_CHAR 127
#define STR_SIZE 100

void give_string(char *);

int main (void)
{
	int status = 0;
	mqd_t analyze_q;
	char *sent_msg;
	struct mq_attr attr;
	
	analyze_q = mq_open("/analyze_q", O_WRONLY, S_IRUSR|S_IWUSR, NULL);
	if (0 > analyze_q)
	{
		perror("mq_open");
		exit(1);
	}
	
	sent_msg = (char *) malloc (100);
	if (NULL == sent_msg)
	{
		perror("malloc");
		exit(1);
	}
	
	give_string(sent_msg);
	
	status = mq_getattr(analyze_q,&attr);
	status = mq_send(analyze_q,(void *)&sent_msg[0],attr.mq_msgsize,(unsigned)NULL);
	
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

