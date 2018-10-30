#include <stdlib.h>/*malloc, free*/
#include <assert.h>
#include <string.h>/*memset*/

#include "dyn_vec.h" /*DYN_VEC_H_*/
#include "heap.h" /*HEAP_H_*/

/*MACROs*/
#define PARENT_IDX(IDX) (((IDX) - 1) / 2)
#define LEFT_CHILD_IDX(IDX) (((IDX) * 2) + 1)
#define RIGHT_CHILD_IDX(IDX) (((IDX) * 2) + 2)
/*END OF MACROs*/

/*STRUCTs*/
struct heap_st
{
	dyn_vec_t *vector;
	/* Return 0 for equal, positive for data > node_data, negative data < node_data */
	int (*compare)(const void *node_data,
		      			 const void *data,
		      			 void *param);
	void *param;
}; /*END OF STRUCTs*/

/*HELPER FUNCTIONS*/
/*return 1 if has parent address or 0 otherwise*/
static int HasParent(heap_t *heap, size_t child_idx);
/*return 1 if parent has a left address or 0 otherwise*/
static int HasLeftChild(heap_t *heap, size_t parent_idx);
/*return 1 if parent has a right address or 0 otherwise*/
static int HasRightChild(heap_t *heap, size_t parent_idx);
/*swap parent and child values*/
static void SwapPointers(void **parent_idx, void **child_idx);
/*sorts an item downwards within MAX Binary Heap */
static void HeapifyDown(heap_t *heap, size_t idx);
/*sorts an item upwards within MAX Binary Heap */
static void HeapifyUp(heap_t *heap, size_t new_child_idx);
/*return 1 if data found in the heap or 0 otherwise*/
static int FindData(heap_t *heap, size_t idx, size_t *ret_idx, void *data);
/*END OF HELPER FUNCTIONS*/

heap_t *HeapCreate(int (*compare)(const void *node_data,
				  const void *data,
				  void *param),
				  void *param)
{
	heap_t *new_heap = NULL;

	assert(compare != NULL);

	new_heap = (heap_t *)malloc(sizeof(heap_t));
	if (NULL == new_heap)
	{
		return (NULL);
	}

	new_heap->vector = DynVecCreate(0, sizeof(void *));
	if (NULL == new_heap->vector)
	{
		free(new_heap);
		new_heap = NULL;

		return(NULL);
	}

	new_heap->compare = compare;
	new_heap->param = param;

	return (new_heap);
}

void HeapDestroy(heap_t *heap)
{
	assert(heap != NULL);

	DynVecDestroy(heap->vector);

	free(heap);

	return;
}

/*Complexity: */
int HeapPush(heap_t *heap, void *data)
{
	assert(heap != NULL);
	assert(data != NULL);

	if (1 == DynVecPushBack(heap->vector, &data))
	{
		return (1);
	}

	HeapifyUp(heap, HeapSize(heap) - 1);

	return (0);
}

static void HeapifyUp(heap_t *heap, size_t new_child_idx)
{
	void **parent_ptr = NULL;
	void **new_child_ptr = NULL;

	assert(heap != NULL);

	if (!HasParent(heap, new_child_idx))
	{
		return;
	}

	parent_ptr = DynVecGetItemAddress(heap->vector,
					  PARENT_IDX(new_child_idx));
	new_child_ptr = DynVecGetItemAddress(heap->vector,
					     new_child_idx);
	/*data is ordered*/
	if (heap->compare(*parent_ptr,
			  *new_child_ptr,
			  heap->param)
			  < 0)
	{
		return;
	}

	/*Swap parent_data with child data*/
	SwapPointers(parent_ptr, new_child_ptr);

	/*placing the new data in its correct position recursively*/
	HeapifyUp(heap, PARENT_IDX(new_child_idx));

	return;
}

void HeapPop(heap_t *heap)
{
	void **head_ptr = NULL;
	void **last_ptr = NULL;

	assert(heap != NULL);
	assert(0 == HeapIsEmpty(heap));

	if (1 == HeapSize(heap))
	{
		DynVecPopBack(heap->vector);

		return;
	}

	head_ptr = DynVecGetItemAddress(heap->vector, 0);
	last_ptr = DynVecGetItemAddress(heap->vector, HeapSize(heap) - 1);

	/* Swap the last item and root */
	SwapPointers(head_ptr, last_ptr);
	/*remove the old root*/
	DynVecPopBack(heap->vector);
	/*re-position the heap root to the correct spot*/
	HeapifyDown(heap, 0);

	return;
}

static void HeapifyDown(heap_t *heap, size_t new_head)
{
	void **right_child_ptr = NULL;
	void **left_child_ptr = NULL;
	void **new_head_ptr = NULL;
	void **max_ptr = NULL;
	size_t max_idx = 0;

	assert(heap != NULL);

	/* BY DEFINITION: no left child === no childrens */
	if (!HasLeftChild(heap, new_head))
	{
		return;
	}

	new_head_ptr = DynVecGetItemAddress(heap->vector,
					    new_head);
	left_child_ptr = DynVecGetItemAddress(heap->vector,
						LEFT_CHILD_IDX(new_head));

	/* new_head has 2 children */
	if (HasRightChild(heap, new_head))
	{
		right_child_ptr = DynVecGetItemAddress(heap->vector,
						       		RIGHT_CHILD_IDX(new_head));
		/* if new_head is in the correct place */
		if ((heap->compare(*left_child_ptr,
					 *new_head_ptr,
					 heap->param)
					 > 0)
					 &&
			(heap->compare(*right_child_ptr,
							 *new_head_ptr,
							 heap->param))
										 > 0)
		{
			return;
		}

		/*check which right data is greater than left data*/
		if (heap->compare(*left_child_ptr,
				  						*right_child_ptr,
				  						heap->param)
											> 0)
		{
			max_ptr = right_child_ptr;
			max_idx = RIGHT_CHILD_IDX(new_head);
		}
		else
		{
			max_ptr = left_child_ptr;
			max_idx = LEFT_CHILD_IDX(new_head);
		}
	}
	else
	{
		/* if new_head is in the correct place */
		if (heap->compare(*left_child_ptr,
											*new_head_ptr,
											heap->param)
											> 0)
		{
			return;
		}
		/*continue downwards with left child*/
		max_ptr = left_child_ptr;
		max_idx = LEFT_CHILD_IDX(new_head);
	}

	SwapPointers(new_head_ptr, max_ptr);

	HeapifyDown(heap, max_idx);

	return;
}

void *HeapPeek(const heap_t *heap)
{
	void *ret = NULL;

	assert(heap != NULL);

	ret = *(void **)DynVecGetItemAddress(heap->vector, 0);

	return(ret);
}

size_t HeapSize(const heap_t *heap)
{
	assert(heap != NULL);

	return(DynVecSize(heap->vector));
}

int HeapIsEmpty(const heap_t *heap)
{
	assert(heap != NULL);

	return(0 == DynVecSize(heap->vector));
}

static void SwapPointers(void **parent_idx, void **child_idx)
{
	void *temp = NULL;

	assert(parent_idx !=NULL);
	assert(child_idx != NULL);

	temp = *parent_idx;
	*parent_idx = *child_idx;
	*child_idx = temp;

	return;
}

/* Time complexity: O(n) */
/* Space complexity: O(1) */
void HeapRemove(heap_t *heap, const void *data)
{
	size_t remove_idx = 0;
	void **last_ptr = NULL;
	void **remove_ptr = NULL;

	assert(heap != NULL);
	assert(data != NULL);

	if (1 == FindData(heap, 0, &remove_idx, (void *)data))
	{
		return;
	}

	/* remove if last item in the vector*/
	if ((HeapSize(heap) - 1) == remove_idx)
	{
		DynVecPopBack(heap->vector);

		return;
	}

	last_ptr = DynVecGetItemAddress(heap->vector, (HeapSize(heap) - 1));
	remove_ptr = DynVecGetItemAddress(heap->vector, remove_idx);

	/*swap the last data and removed data*/
	SwapPointers(last_ptr, remove_ptr);
	/*pop the old root*/
	DynVecPopBack(heap->vector);
	/*reposition the heap*/
	HeapifyUp(heap, remove_idx);
	HeapifyDown(heap, remove_idx);

	return;
}

/* Time complexity: O(n) */
/* Space complexity: O(1) */
static int FindData(heap_t *heap,
										size_t idx,
										size_t *ret_idx,
										void *data)
{
	void **check_data_ptr = NULL;
	int ret = 0;

	assert(heap != NULL);
	assert(data != NULL);
	assert(ret_idx != NULL);

	/* If the index equal or bigger than the size, data not found */
	if (idx >= HeapSize(heap))
	{
		return (1);
	}

	/* check if data is found */
	check_data_ptr = DynVecGetItemAddress(heap->vector, idx);
	if (0 == heap->compare(*check_data_ptr, data, heap->param))
	{
		*ret_idx = idx;
		
		return (0);
	}

	/*continue searching if data not found*/
	ret = FindData(heap, LEFT_CHILD_IDX(idx), ret_idx, data);
	if (ret != 0)
	{
		ret = FindData(heap, RIGHT_CHILD_IDX(idx), ret_idx, data);
	}

	return (ret);
}

static int HasParent(heap_t *heap, size_t child_idx)
{
	assert(heap != NULL);

	return (HeapSize(heap) > PARENT_IDX(child_idx));
}

static int HasLeftChild(heap_t *heap, size_t parent_idx)
{
	assert(heap != NULL);

	return (HeapSize(heap) > LEFT_CHILD_IDX(parent_idx));
}

static int HasRightChild(heap_t *heap, size_t parent_idx)
{
	assert(heap != NULL);

	return (HeapSize(heap) > RIGHT_CHILD_IDX(parent_idx));
}
