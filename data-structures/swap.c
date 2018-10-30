#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "swap.h"

static void Swap(int *p1, int *p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;

	return;
}

static void SwapIntPtr(int **p1, int **p2)
{
	int *tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

static void SwapVoidPtr(void **p1, void **p2)
{
	void *tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

static void SwapVoidData(void *data1, void *data2, size_t mem_size)
{
	unsigned char *char_b = NULL;
	unsigned char *char_a = NULL;
	unsigned char tmp;

	assert(data1 != NULL);
	assert(data2 != NULL);

	char_a = data1;
	char_b = data2;

	while (mem_size)
	{
		tmp = *char_a;
		*char_a++ = *char_b;
		*char_b++ = tmp;

		--mem_size;
	}
}
