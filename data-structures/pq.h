#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <stddef.h> /* size_t */

typedef struct pq_st pq_t;

pq_t *PQCreate(int (*is_before)(
   					  const void *node_data,
   					  const void *data,
   					  void *param),
   			 void *param);

void PQDestroy(pq_t *pq);

int PQIsempty(const pq_t *pq);

size_t PQSize(const pq_t *pq);

/* Push new element to the queue */
/* data cannot be null */
/* Returns 1 upon failure, 0 upon success */
int PQEnqueue(pq_t *pq, void *data);

/* Removes element from the queue. */
/* Returns removed data. */
void *PQDequeue(pq_t *pq);

/* Returns data of element to be dequeued. */
void *PQPeek(const pq_t *pq);

/* remove all elements from queue */
void PQClear(pq_t *pq);

/* remove an element from queue  */
/* Returns removed data, Null if element not found */
void *PQErase(pq_t *pq,
   		 int (*is_match)(
   			  const void *node_data,
   			  const void *data,
   			  void *param),
   		 const void *data,
   		 void *param);

#endif /*PRIORITYQUEUE_H_*/
