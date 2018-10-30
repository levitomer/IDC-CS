/*C program to solve race condition between two threads via flags*/
#include <stdio.h>
#include <pthread.h>

static void *Producer(void *param);

static void *Consumer(void *param);

/*the producer signals the consumer*/
int signal = 0;

int count = 0;

int main(void)
{
	pthread_t consumer;
	pthread_t producer;
	
	/*create two threads to work simultaniously*/
	pthread_create(&consumer, NULL, Producer, NULL);
	pthread_create(&producer, NULL, Consumer, NULL);
	
	/*join their resources to avoid termination*/
	pthread_join(consumer, NULL);
	pthread_join(producer, NULL);
	
	return (0);
}

static void *Producer(void *param)
{
	/*start running*/
	while(1)
	{
	
		while (!signal)
		{
			printf("Input: %d\t", count++);
			/*signal to consumer*/
			signal = 1;
		}
	
	sleep(1);
	
	}
	
	
	return (NULL);
}

static void *Consumer(void *param)
{
	/*start running*/
	while(1)
	{
		/*check the signal and output*/
		while (signal)
		{
			printf("Output: %d\n", count);
			signal = 0;
		}
	
	sleep(1);
	}

	
	return (NULL);
}

