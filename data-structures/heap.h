#ifndef HEAP_H_ /*HEAP_H_*/
#define HEAP_H_

#include <stddef.h>

typedef struct heap_st heap_t;

heap_t *HeapCreate(int (*compare)(const void *node_data,
																	const void *data,
																	void *param),
   								 void *param);

void HeapDestroy(heap_t *heap);
/*push a data into the heap, return 1 if success or 0 otherwise*/
int HeapPush(heap_t *heap, void *data);
/*pop the item at the head of the heap*/
void HeapPop(heap_t *heap);
/*return the data at the head, or NULL if empty*/
void *HeapPeek(const heap_t *heap);
/*return the size of the heap*/
size_t HeapSize(const heap_t *heap);
/*return 1 if heap is empty, or 0 otherwise*/
int HeapIsEmpty(const heap_t *heap);
/*remove an item in the heap*/
void HeapRemove(heap_t *heap, const void *data);

#endif /*END OF HEAP_H_*/
