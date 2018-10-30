#include <stdlib.h> /* free */
#include <assert.h>

#include "srt_list.h"
#include "pq.h"

typedef srt_list_t pq_st;

pq_t *PQCreate(int (*is_before)(
   					  const void *node_data,
   					  const void *data,
   					  void *param),
   			 void *param)
{
	assert(is_before != NULL);

	return ((pq_t *)SrtListCreate(is_before, param));
}

/* Complexity O(n) */
void PQDestroy(pq_t *pqueue)
{
	assert(pqueue != NULL);

	SrtListDestroy((srt_list_t *)pqueue);
	pqueue = NULL;

	return;
}

/* Complexity O(1) */
int PQIsempty(const pq_t *pqueue)
{
		assert(pqueue != NULL);

		return (SrtListIsEmpty((srt_list_t *)pqueue));
}

/* Complexity O(n) */
size_t PQSize(const pq_t *pqueue)
{
		assert(pqueue != NULL);

		return (SrtListSize((srt_list_t *)pqueue));
}

/* Complexity O(n)
 * data cannot be null
 * Returns 0 upon failure, 1 upon success
 */
int PQEnqueue(pq_t *pqueue, void *data)
{
		assert(pqueue != NULL);
		assert(data != NULL);

		if (SrtListIsSameIter(SrtListInsert((srt_list_t *)pqueue, data),
							  SrtListEnd((srt_list_t *)pqueue)))
		{
			return (1);
		}

		return (0);
}

/* Complexity O(1) */
void *PQDequeue(pq_t *pqueue)
{
		assert(pqueue != NULL);
		
		if(PQIsempty(pqueue))
		{
			return (NULL);
		}
		
		return (SrtListPopFront((srt_list_t *)pqueue));
}

/* Complexity O(1) */
void *PQPeek(const pq_t *pqueue)
{
		assert(pqueue != NULL);

		return (SrtListGetData(SrtListBegin((srt_list_t *)pqueue)));
}

/* Complexity O(n) */
void PQClear(pq_t *pqueue)
{
		assert(pqueue != NULL);

		while (!SrtListIsEmpty((srt_list_t *)pqueue))
		{
			SrtListPopBack((srt_list_t *)pqueue);
		}

		return;
}

/* Complexity O(n) */
void *PQErase(pq_t *pqueue,
			  int (*is_match)(const void *node_data,
							  const void *data,
							  void *param),
			  const void *data,
			  void *param)
{
	srt_list_iter_t found;
	void *ret = NULL;

 	assert(pqueue != NULL);
	assert(data != NULL);
	assert(is_match != NULL);

	found = SrtListFindIf(SrtListBegin((srt_list_t *)pqueue),
						  SrtListEnd((srt_list_t *)pqueue),
						  is_match,
						  data,
						  param);


	if (SrtListIsSameIter(found, SrtListEnd((srt_list_t *)pqueue)))
	{
		return (NULL);
	}

	ret = SrtListGetData(found);
	SrtListErase(found);

	return(ret);
}
