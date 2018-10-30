#ifndef QUEUE_H_
#define QUEUE_H_

#include <stddef.h> /* size_t */

typedef struct queue_st queue_t;

/* Returns pointer to the queue, NULL on failure.
    Note:  must be released by using QueueDestroy. */
queue_t *QueueCreate(void);

void QueueDestroy(queue_t *queue);

/* Get number of elements in the queue. */
size_t QueueSize(const queue_t *queue); 

int QueueIsEmpty(const queue_t *queue);

/* Push new element to the end of the queue.
Returns failure or success */
int QueueEnqueue(queue_t *queue, void *data);

/* Remove element from the head of the queue. */
/* Returns pointer to the removed data, ,  NULL if queue empty */
void *QueueDequeue(queue_t *queue);

/* Returns pointer to next element to be dequeued, ,  NULL if queue empty  */
void *QueuePeek(const queue_t *queue);

/* Append 'from' queue to 'to' queue */
void QueueAppend(queue_t *to, queue_t *from);

#endif	/*   QUEUE_H_	*/
