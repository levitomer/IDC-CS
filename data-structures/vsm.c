#include <stddef.h> /* offsetof, long */
#include <stdlib.h> /* labs */
#include <assert.h>

#include "vsm.h"

#define MAGIC_NUM 0xDEADBEEF
#define WORD_SZ sizeof(long)
#define ALIGNED_BLOCK_SZ(block_size) ((block_size) + ((WORD_SZ - ((block_size) % (WORD_SZ))) % WORD_SZ))
 
typedef struct metadata_st
{
	long memory_size;

	#ifndef NDEBUG
		long magic_num;
	#endif /* NDEBUG */

}metadata_t;

static void VSMDefrag(const vsm_t *vsm, long *total, long *max);

/* Complexity: O(1) */
vsm_t *VSMInit(void *memory, long total_size)
{
		metadata_t *metadata = NULL;

		assert(memory != NULL);
		
		/* check memory alignment */
		assert(((unsigned long)memory & (WORD_SZ - 1)) == 0);
		
		/* save memory for total size placeholder */
		total_size -= (total_size % WORD_SZ);
		
		/* assure total size is sufficiently large to contain at least metadata */
		if (total_size < (long)(sizeof(metadata_t) + (2 * sizeof(long))))
		{
			return (NULL);
		}

		*(long *)memory = total_size;

		metadata = (metadata_t *)((char *)memory + sizeof(long));
		metadata->memory_size = total_size - sizeof(long);

		return (memory);
}

/* Complexity O(n) */
void *VSMAlloc(vsm_t *vsm, long size)
{
	metadata_t *metadata = NULL;
	long *vsm_end = NULL;

	
	assert (vsm != NULL);
	
	vsm_end = (long *)((char *)vsm + *(long *)vsm);
	
	size = sizeof(metadata_t) + ALIGNED_BLOCK_SZ(size);
	if (size >= *(long*)vsm)
	{
		return (NULL);
	}
	
	metadata = (metadata_t *)((char *)vsm + sizeof(long));

	/* stop when start meets end */
	while ((char *)metadata != (char *)vsm_end)
	{
		/* case 1: memory available */
		if (metadata->memory_size >= size)
		{
			/* requested memory slot is less than limit */
			if ((metadata->memory_size > size) &&
			   (((char*)metadata + size) != (char*)vsm_end))
			{
				/* update the total size in the next metadata */
				((metadata_t *)((char *)metadata + size))->memory_size = metadata->memory_size - size;
			}

			metadata->memory_size = -(size);

			#ifndef NDEBUG
				metadata->magic_num = MAGIC_NUM;
			#endif /* NDEBUG */ 

			return ((char *)metadata + sizeof(metadata_t));
		}
		/* case 2: memory available but not sufficient */
		else if ((metadata->memory_size > 0) &&
				(((char *)metadata + metadata->memory_size) != (char *)vsm_end) &&
				(((metadata_t *)((char *)metadata + metadata->memory_size))->memory_size > 0))
		{
			/* aggregate the memory vacancies */
			metadata->memory_size +=
			((metadata_t *)((char *)metadata + metadata->memory_size))->memory_size;
		}
		else /* case 3: memory is already allocated */
		{
			metadata = (metadata_t *)((char*)metadata + labs(metadata->memory_size));
		}
	}
	
	return (NULL);
}

/* Complexity: O(1) */
void VSMFree(void *memory_to_free)
{
	metadata_t *metadata = NULL;

	assert(memory_to_free != NULL);
	
	/* assert that memory is not free */
	assert(((metadata_t *)((char *)memory_to_free - sizeof(metadata_t)))->memory_size < 0);
	
	if (0 == memory_to_free)
	{
		return;
	}
	
	metadata = (metadata_t *)((char *)memory_to_free - sizeof(metadata_t));
	
	#ifndef NDEBUG
		assert(metadata->magic_num == MAGIC_NUM);
	#endif /* NDEBUG */ 

	metadata->memory_size = -metadata->memory_size;

	return;
}

/* Complexity: O(n) */
long VSMTotalFree(const vsm_t *vsm)
{
	long total = 0;
	long max = 0;
	
	assert(vsm != NULL);
	
	VSMDefrag(vsm, &total, &max);
	
	return (total);
}

/* Complexity: O(n) */
long VSMMaxFree(const vsm_t *vsm)
{
	long total = 0;
	long max = 0;
	
	assert(vsm != NULL);
	
	VSMDefrag(vsm, &total, &max);
	
	return (max);
}

/* Complexity: O(1) */
void VSMClear(vsm_t *vsm)
{
	metadata_t *metadata = NULL;
	
	assert(vsm);
	
	metadata = (metadata_t *)((char *)vsm + sizeof(long));
	
	metadata->memory_size = *((long *)vsm) - sizeof(long);

	return;
}

static void VSMDefrag(const vsm_t *vsm, long *total, long *max)
{
	long *runner = NULL;
	long *accum = NULL; /* accument metadata */
	long *end = NULL; /* end of vsm */

	assert(vsm != NULL);
	assert(total != NULL);
	assert(max != NULL);
	
	accum = (long *)((char *)vsm + sizeof(long));
	end = (long *)((char *)vsm + *((long *)vsm));

	while (accum < end)
	{
		if (*accum > 0)
		{
			runner = (long *)((char *)accum + *accum);

			while ((runner < end) && (*runner > 0))
			{
				*accum += *runner;
				runner = (long *)((char *)runner + *runner);
			}
			
			/* save the max */
			if (*accum > *max)
			{
				*max = *accum;
			}
			
			/* updates the total */
			*total += *accum;
		}

		*(char **)&accum += labs(*accum);
	}

	return;
}
