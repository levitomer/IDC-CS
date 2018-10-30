#include <stddef.h> /* offsetof, size_t */
#include <assert.h>
#include <string.h> /* memcpy */

#include "fsm.h"

#define WORD_SZ sizeof(size_t) /* the size of a word in the system */
#define OFFSET offsetof(fsm_t, block_size) /* the offset from the struct header */
#define ALIGNED_BLOCK_SZ(block_size) ((block_size) + (WORD_SZ - ((block_size) % (WORD_SZ))))
#define ROOT(ptr, type, member) ((type *)((size_t *)(ptr) - offsetof(type, member)))

struct fsm_st
{
	size_t block_size;
	size_t num_of_blocks;
	size_t offset;
};


size_t FSMSuggestSize(size_t num_of_blocks, size_t block_size)
{
	size_t mem_size;

	mem_size = sizeof(fsm_t) + (num_of_blocks * (ALIGNED_BLOCK_SZ(block_size)));

	return (mem_size);
}

/*
 * memory recieved from user is assumed to be aligned
 * offset stored in last block is 0
 */
fsm_t *FSMInit(void *mem, size_t num_of_blocks, size_t block_size)
{
	fsm_t *free_list = NULL;
	size_t head;
	size_t i;

	assert(mem != NULL);
	assert(num_of_blocks > 0);
	assert(block_size > 0);

	free_list->num_of_blocks = ((fsm_t *)mem)->num_of_blocks;
	free_list->block_size = ((fsm_t *)mem)->block_size;
	free_list->offset = sizeof(fsm_t); /* offset from head */

	memcpy(mem, free_list, sizeof(fsm_t));

	head = sizeof(fsm_t) + WORD_SZ + block_size;

	/* links the rest of the freelist offsets */
	for (i = 1; i < num_of_blocks; ++i)
	{
		memcpy((fsm_t *)mem + (sizeof(fsm_t) + (i * (WORD_SZ + block_size))),
			&head,
			WORD_SZ);

		head += WORD_SZ + ALIGNED_BLOCK_SZ(block_size);
	}

	memcpy((char *)mem + (sizeof(fsm_t) + (i * (block_size + WORD_SZ))),
		memchr(mem, '0', 1),
		WORD_SZ);
	
	return (free_list);
}

/*
 * returns an handle to the allocated region
 * remove the region from the end of the free list
 */
void *FSMAlloc(fsm_t *mem)
{
	size_t ret = *((size_t *)mem);
	*((size_t *)mem + WORD_SZ) = *((char *)mem +ret);

	*((size_t *)mem) = *((char *)mem + ret);
	*((char *)mem + ret) = ret;

	if (!ret)
	{
		return (NULL);
	}
	else
	{
		memcpy((char*)mem + ret, &ret, WORD_SZ);
	}

	return ((char*)mem + ret + WORD_SZ);
}

/* To free a region, one would just link it to the free list. */
void FSMFree(void *block)
{
	void *mem;
	size_t meta_data;
	size_t tmp;

	meta_data = *((char*)block - WORD_SZ);
	mem = (char *)block - WORD_SZ - meta_data;

	tmp = *((size_t*)mem + (2 * WORD_SZ));
	*((size_t*)mem + (2 * WORD_SZ)) = meta_data;
	*((size_t*)block - WORD_SZ) = tmp;

	return;
}
