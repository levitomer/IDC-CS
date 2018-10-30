#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>

#include "sort.h"
#include "swap.h"

static void SwapVoidMemCpy(void *a, void *b, size_t width);

static void *Partition(void *base,
		        char *start,
		        char *end,
		        size_t size,
		        int (*compare)(const void *pivot_data,
		       		       const void *data));

/* main function that implements QuickSort
Time Complexity (avg.): O(N(log(N))
Time Complexity (worst case): O(N^2)*/
void QuickSort(void *base,
	       size_t nmemb,
	       size_t size,
	       int (*compare)(const void *pivot_data,
	       		      const void *data))
{
	char *pivot = NULL;
	char *start = NULL;
	char *end = NULL;
	size_t nmemb_left = 0;
	size_t nmemb_right = 0;

	assert(base != NULL);
	assert(compare != NULL);

	/*if there is only 1 item, array is sorted*/
	if (nmemb <= 1)
	{
		return;
	}

	start = (char *)base;
	end = start + size * nmemb - size;

	pivot = (char *)Partition(base, start, end, size, compare);
	nmemb_left = (pivot - start)/size;
	nmemb_right = (end - (pivot))/size;

	if (start < end)
	{
		/* Devide and sorts each sub-array*/
		QuickSort(start, nmemb_left, size, compare);
		QuickSort(start + ((size_t)(pivot + 1) * size), nmemb_right, size, compare);
	}

	return;
}

static void *Partition(void *base,
		        char *start,
		        char *end,
		        size_t size,
		        int (*compare)(const void *pivot_data,
		       		       const void *data))
{
	size_t random = 0;
	void *pivot = NULL;

	assert(base != NULL);
	assert(compare != NULL);

	/* randomize a number in between start & end*/
	random = rand() % (((end - start)/size) + 1);

	/*Swap base[random] with base[end]*/
	SwapVoidData(start + (random * size), end, size);

	pivot = end;

	/*loop till pivot is at its correct position*/
	while (start < end)
	{
		if (compare(pivot, start) >= 0)
		{
			start = start + size;
		}
		else if (compare(pivot, end) < 0)
		{
			end = end - size;
		}

		if (compare(start, end) > 0)
		{
			SwapVoidData(start, end, size);
		}
	}

	SwapVoidData(pivot, start, size);

	return (end);
}


static int RadixCountSort(int *arr,
			  size_t size,
			  int range,
			  int *dest,
			  int mask,
			  size_t offset);

static void RecMergeSort(int *start, int *end, int *buffer);

static void MergeSubArray(int *start,
			  int *middle,
			  int *end,
			  int *buffer);

int MergeSort(int *arr, size_t size)
{
	int *buffer = NULL;
	int *start = NULL;
	int *end = NULL;

	assert(arr != NULL);

	start = arr;
	end = arr + size;

	buffer = (int *)calloc(sizeof(int), size);
	if (NULL == buffer)
	{
		return (1);
	}

	RecMergeSort(start, end, buffer);

	free(buffer);
	buffer = NULL;

	return (0);
}

static void MergeSubArray(int *start, int *middle, int *end, int *buffer)
{
	int *buffer_writer = NULL;
	int *reader = NULL;
	int *start_origin = NULL;

	assert(start != NULL);
	assert(middle != NULL);
	assert(end != NULL);
	assert(buffer != NULL);

	start_origin = start;
	buffer_writer = buffer;
	reader = middle;

	/*PROGRESSION*/

	/*sort left & right sides of array*/
	while ((start < middle) && (reader < end))
	{
		if (*start <= *reader)
		{
			*buffer_writer = *start;
			++start;
		}
		else
		{
			*buffer_writer = *reader;
			++reader;
		}

		++buffer_writer;
	}


	/* appends the remaining values from left side*/
	memcpy(buffer_writer, start, (middle - start)*(sizeof(int)));

	/* appends the remaining values from right side*/
	memcpy(buffer_writer, reader, (end - reader)*(sizeof(int)));

	memcpy(start_origin, buffer, (end - start_origin)*(sizeof(int)));

	return;
}


static void RecMergeSort(int *start, int *end, int *buffer)
{
	int *middle = NULL;

	assert(start != NULL);
	assert(end != NULL);
	assert(buffer != NULL);

	/*init sizes*/
	middle = ((start + ((end - start) / 2)));

	/*TERMINATING CONDITION*/
	if (start == middle)
	{
		return;
	}

	/* Sort first and second halves */
	RecMergeSort(start, middle, buffer);
	RecMergeSort(middle, end, buffer);

	MergeSubArray(start, middle, end, buffer);

	return;
}


int CountSort(int *arr,  size_t size, int from, int to, int *dst)
{
	int *arr_end = arr + size;
	int *arr_start = arr;
	int i = 0;

	int lut_range = to - from + 1;
	/* sets a lut for value histogram */
	int *lut = (int *)calloc(lut_range, sizeof(int));
	if (NULL == lut)
	{
		return(1);
	}

	/* fill the lut with the count of each value */
	for (	; arr < arr_end; ++arr)
	{
		/*from - handle negative numbers*/
		++lut[*arr - from];
	}

	/* calculates the indexes to fill */
	for (i = 1; i < lut_range; ++i)
	{
		lut[i] += lut[i - 1];
	}

	/* retrieve the values by the time they were referenced */
	for (arr = arr_start; arr < arr_end; ++arr)
	{
		dst[lut[*arr - from] - 1] = *arr;
		--lut[*arr - from];
	}

	free(lut);
	lut = NULL;

	return(0);
}

int RadixSort(int *arr, size_t size, int bits)
{
	int *dest = NULL;
	int mask = (1<<bits) - 1;
	int idx = 0;
	int range = (1<<bits);
	size_t offset = 0;
	int *arr_addr = arr;

	assert(arr != NULL);

	dest = (int *)malloc(size * sizeof(int));
	if (NULL == dest)
	{
		return (1);
	}

	/* loops until all bits are 0's */
	for (idx = INT_MAX; idx > 0; idx>>=bits)
	{
		RadixCountSort(arr, size, range, dest, mask, offset);
		offset += bits;
	}

	if (arr_addr != arr)
	{
		SwapIntPtr(&arr, &dest);
	}
	memcpy(arr, dest, size);

	free(dest);
	dest = NULL;

	return(0);
}

static int RadixCountSort(int *arr,
			     size_t size,
			     int range,
			     int *dest,
			     int mask,
			     size_t offset)
{
	int *lut = NULL;
	int *arr_start = NULL;
	int *arr_end = NULL;
	int i = 0;

	assert(arr != NULL);

	arr_end = arr + size;
	arr_start = arr;
	mask <<= offset; /* updating the mask offset */

	/* sets a lut for value histogram */
	lut = (int *)calloc(range, sizeof(int));
	if (NULL == lut)
	{
		return (1);
	}

	/* fill the lut with the count of each value */
	for (	; arr < arr_end; ++arr)
	{
		lut[*arr & mask]++;
	}

	/* count the values and fill the lut */
	for (i = 1; i < range; ++i)
	{
		lut[i] += lut[i - 1];
	}

	/* retrieve the values by the time they were referenced */
	for (arr = arr_end - 1; arr > arr_start; --arr)
	{
		*(dest + lut[*arr & mask] - 1) = *arr;
		--lut[*arr & mask];
	}

	free(lut);
	lut = NULL;

	return (0);
}

/* Complexity O(n^2) */
void InsertionSort(int *arr, size_t size)
{
	size_t post = 0;
	int pre = 0;
	int check = 0;

	assert(arr != NULL);

	for (post = 1; post < size; ++post)
	{
		check = arr[post];
		pre = post - 1;
		/* moves the small values to the right */
		while ((pre >= 0) && (arr[pre] > check))
		{
			arr[pre + 1] = arr[pre];
			--pre;
		}
		arr[pre + 1] = check;
	}

	return;
}

/* Complexity O(n^2) */
void SelectionSort(int *arr, size_t size)
{
	size_t i, j, min_idx;

	assert(arr != NULL);

	for (i = 0; i < (size - 1); ++i)
	{
		min_idx = i; /* index of minimum element */

		for (j = (i + 1); j < size; ++j)
		{
			if (arr[j] < arr[min_idx])
			{
				min_idx = j;
			}
		}
		/* Swap the minimum element with the first element */
		Swap(&arr[min_idx], &arr[i]);
	}
	return;
}

/*
Time Complexity: O(n^2)
Stable
*/
void BubbleSort(int *arr, size_t size)
{
	size_t i, j;

	for (i = 0; i < (size - 1); ++i)
	{
		for (j = 0; j < (size - 1 - i); ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				Swap(&arr[j], &arr[j + 1]);
			}
		}
	}

	return;
}
