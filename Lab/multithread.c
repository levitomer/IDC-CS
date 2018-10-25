#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_OF_THREADS 100000

/* Let us create a global variable to change it in threads*/
int g = 0;
int array[100000];

/* The function to be executed by all threads*/
void *MyThreadFunc(void *vargp)
{
	/* Store the value argument passed to this thread*/
	int *myid = (int *) vargp;
	
	array[*(int *)vargp] = *(int *)vargp;
	 
	/* Let us create a static variable to observe its changes*/
	static int s = 0;
	 
	/* Change static and global variables*/
	++s; ++g;
	 
	/* Print the argument, static and global variables*/
/*	printf("Thread ID: %d, Static: %d, Global: %d\n", *myid, ++s, ++g);*/
	printf("array[%d] = %d\n", array[*(int *)vargp], *myid);
	
	return (NULL);
}


int main()
{
	size_t i = 0;
	pthread_t thread_id;

	for(i = 0; i < NUM_OF_THREADS; ++i)
	{
		pthread_create(&thread_id, NULL, MyThreadFunc, (void *)&i);
	}
	
	/*do some tasks unrelated to result*/
	for(i = 0; i < NUM_OF_THREADS; ++i) 
	{
/*		printf("Thread Joined!\n");*/
		pthread_join(thread_id, NULL);
	}
	
	return (0);
}
