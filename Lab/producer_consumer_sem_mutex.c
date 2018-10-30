/*C program to mitigate between producer and consumer race condition*/
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#include "dlist.h"

sem_t semaphore;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *Producer(void * param);

void *Consumer(void * param);

int main(void)
{
		pthread_t threads[2];

		dlist_t *dlist = DlistCreate();
		if (NULL == dlist)
		{
			fprintf(stderr, "dlist creation failed.");
			return (1);
		}

    sem_init(&semaphore, 0, 1);

    pthread_create(&threads[0], NULL, Producer, dlist);
    pthread_create(&threads[1], NULL, Consumer, dlist);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    sem_destroy(&semaphore);

		return (0);
}

void *Producer(void *dlist)
{
		int i = 0;

		while(1)
    {
        /*lock the state and give the producer the previlege*/
        pthread_mutex_lock(&mutex);
				/*Add item to queue*/
        printf("Sent %d\t", *(int *)DlistGetData(
																		DlistPushBack((dlist_t *)dlist, &i)));
				++i;
        pthread_mutex_unlock(&mutex);

        /*Signal semaphore*/
        sem_post(&semaphore);
				sleep(1);
    }

		return (NULL);
}

void *Consumer(void *dlist)
{
	while(1)
	{
	    /*wait for signal*/
	    sem_wait(&semaphore);
			/*lock the state and give the consumer the previlege*/
	    pthread_mutex_lock(&mutex);
			/*get the data inserted by the producer*/
			if (DlistIsEmpty((dlist_t *)dlist))
			{
				printf("Received %d\n", *(int *)DlistGetData(DlistPopFront(dlist)));
			}
			/*revert the state */
	    pthread_mutex_unlock(&mutex);

			sleep(1);
	}

	return (NULL);
}
