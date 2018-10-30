 #include <stdlib.h> /* malloc, free */
#include <assert.h>

#include "slist.h"	/* slist framework */
#include "queue.h"

struct queue_st
{
    slist_node_t *head; /* head dummy */
    slist_node_t *tail; /* tail dummy */
};

queue_t *QueueCreate(void)
{
	slist_node_t *dummy = NULL;

	queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
	if (NULL == queue)
	{
		return (NULL);
	}

	dummy = SListCreateAndInitNode(NULL, NULL);
	if(NULL == dummy)
	{
		return (NULL);
	}

	queue->head = dummy;
	queue->tail = dummy;

	return (queue);
}

size_t QueueSize(const queue_t *queue)
{
	assert(queue != NULL);

	return (SListCount(queue->head) - 1);
}

int QueueIsEmpty(const queue_t *queue)
{
	assert(queue != NULL);

	return (NULL == (queue->head)->next);
}

int QueueEnqueue(queue_t *queue, void *data)
{
	slist_node_t *new_node = NULL;

	assert(queue != NULL);

	new_node = SListCreateAndInitNode((void *)data, NULL);
	if (NULL == new_node)
	{
		return (1);
	}

	new_node = SListInsert(queue->tail, new_node);
	/* coronate tail to be the dummy again */
	queue->tail = new_node->next;

	return (0);
}

/*
+ Return NULL when queue underflows
*/
void *QueueDequeue(queue_t *queue)
{
	void *head_data = NULL;

	assert(queue != NULL);

	/* Handle underflow */
	if (QueueIsEmpty(queue))
	{
		return (NULL);
	}

	head_data = (queue->head)->data;
	free(SListRemove(queue->head));

	if (QueueIsEmpty(queue))
	{
		queue->tail = queue->head;
	}

	return (head_data);
}

/*
Returns NULL if queue empty
O(n)
*/
void *QueuePeek(const queue_t *queue)
{
	if (NULL == queue)
	{
		return (NULL);
	}

	return ((queue->head)->data);
}

/* Append 'from' queue to 'to' queue */
void QueueAppend(queue_t *dest, queue_t *src)
{
	slist_node_t *tmp = NULL;

	assert(src != NULL);
	assert(dest != NULL);

	if (QueueIsEmpty(dest))
	{
		/* swap tails */
		tmp = dest->tail;
		dest->tail = src->tail;
		src->tail = tmp;

		/* swap heads */
		tmp = dest->head;
		dest->head = src->head;
		src->head = tmp;
	}
	else if (!QueueIsEmpty(src))
	{
		/* concatanate src's head to dest's tail */
		(dest->tail)->next = src->head;
		tmp = SListRemove(dest->tail);
		dest->tail = src->tail;

		/* preserve dest's dummy to be src's new dummy */
		src->tail = tmp;
		src->head = tmp;
		tmp->next = NULL;
		tmp->data = NULL;
	}

	return;
}

/*
O(n)
*/
void QueueDestroy(queue_t *queue)
{
	SListFreeAll(queue->head);

	free(queue);
	queue = NULL;

	return;
}
