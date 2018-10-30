#ifndef SORT_H
#define SORT_H
#include <stddef.h>

void InsertionSort(int *arr, size_t size);

void SelectionSort(int *arr, size_t size);

void BubbleSort(int *arr, size_t size);

int RadixSort(int *arr, size_t size, int bits);

int CountSort(int *arr, size_t size, int from, int to, int *dst);

int MergeSort(int *arr, size_t size);

/* main function that implements QuickSort*/
void QuickSort(void *base,
	       size_t nmemb,
	       size_t size,
	       int (*compare)(const void *pivot_data,
	       		      const void *data));

#endif /* SORT_H */
