#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define Q_SIZE 10

typedef struct queue_st
{
	char m_queue[Q_SIZE];
	size_t m_elements_in_q;
	size_t m_first_element;
}queue_t;

/*push char into queue array*/
int push_char(queue_t *queue, char input);

/*pop a char from queue array*/
void pop_char(queue_t *queue);

int main(void)
{
	char *str = "t";
	
	queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
	if (NULL == queue)
	{
		return (1);
	}
	
	queue->m_elements_in_q = 0;
	queue->m_first_element = 0;
	
	while (*str)
	{
		push_char(queue, *str++);
		
		printf("%s\n", queue->m_queue);
	}
	
	while (queue->m_elements_in_q > 0)
	{
		pop_char(queue);
		printf("%s\n", queue->m_queue);
	}
	
	return (0);
}


int push_char(queue_t *queue, char input)
{
	assert(queue != NULL);
	
	if (queue->m_elements_in_q == Q_SIZE)
	{
		return (1);
	}
	
	queue->m_queue[(queue->m_first_element + 
			queue->m_elements_in_q) % 
			Q_SIZE] = input;
	++queue->m_elements_in_q;
	
	return (0);
}


void pop_char(queue_t *queue)
{
	if (0 == queue->m_elements_in_q)
	{
		return;
	}
	
	queue->m_queue[queue->m_first_element] = 0;
	queue->m_first_element = (queue->m_first_element + 1) % Q_SIZE;
	--queue->m_elements_in_q;
	
	return;
}

