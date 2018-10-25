/*C program to solve producer to N consumers problem by
	1 mutex
	1 semaphore
	1 condition variable
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>

#define CONSUMERS 4

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t is_updated = PTHREAD_COND_INITIALIZER;

/*
 any threads or processes must stop at this point and cannot proceed until 
 all other threads/processes reach this barrier.
*/
pthread_barrier_t barrier;
/*
When the required number of threads have called pthread_barrier_wait() specifying the barrier, the constant PTHREAD_BARRIER_SERIAL_THREAD is returned to one unspecified thread and 0 is returned to each of the remaining threads.
*/
static void *Producer(void *param);
static void *Consumer(void *param);

sem_t sem;
static int p_version = 0;

int main()
{
	int consumer = 0;
	
	pthread_t producer_tid;
	pthread_t consumers_tid[CONSUMERS];
	/*
	The count argument specifies the number of threads that must call pthread_barrier_wait() before any of 
	them successfully return from the call. The value specified by count must be greater than 0. 
	*/
	if (pthread_barrier_init(&barrier, NULL, CONSUMERS))
	{
		fprintf(stderr, "ERROR: barrier init failed");
		
		return (1);
	}
	
	sem_init(&sem, 0, CONSUMERS);
	
	/*CREATING PRODUCERs*/
	pthread_create(&producer_tid, 
			NULL, 
			Producer, 
			NULL);
	
	/*CREATING CONSUMERS*/
	for(consumer = 0; consumer < CONSUMERS; ++consumer)
	{
		pthread_create(&consumers_tid[consumer], 
				NULL, 
				Consumer, 
				NULL);
	}
	
	/*JOIN PRODUCERs*/
	pthread_join(producer_tid, NULL);
	
	/*JOIN CONSUMERs*/
	for (consumer = 0; consumer < CONSUMERS; ++consumer) 
	{
		pthread_join(consumers_tid[consumer], NULL);
	}
	
	pthread_barrier_destroy(&barrier);
	
	return (0);
}

/*
 * Producer 
 */
static void *Producer(void *param)
{
	int consumer = 0;
	(void)param;
	
	while (1)
	{
		/*the producer waits until each costumer will post its version*/
		for (consumer = 0; consumer < CONSUMERS; ++consumer)
		{
			sem_wait(&sem);
		}
		
		printf("Producer id #%lu released v.%d\n", 
			pthread_self(), ++p_version);
		
		pthread_mutex_lock(&lock);
		
		/*call all threads that awaiting to consume the new version*/
		pthread_cond_broadcast(&is_updated);
		
		pthread_mutex_unlock(&lock);
	}
	
	return (NULL);
}

/*
 * Consumer
 */
static void *Consumer(void *param)
{
	int sval = 0;
	static int c_version = 0;
	
	(void)param;

	while (1)
	{
		pthread_mutex_lock(&lock);
		/*each consumer notify the producer*/
		sem_post(&sem);
		
		c_version = p_version;
		
		printf("Consumer id #%lu -> updated to v.%d\n", 
			pthread_self(), c_version);
		
		/*waiting for other consumers to update*/
		pthread_cond_wait(&is_updated, &lock);
		
		pthread_mutex_unlock(&lock);
	}
	
	return (NULL);
}

