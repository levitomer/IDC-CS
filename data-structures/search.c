#include <math.h> /*sqrt*/
#include <assert.h> 

#include "search.h"

/*Complexity: O(Log n)*/
void *BinaryIterSearch(const void *base,
		       size_t n_elements, 
		       size_t elem_size, 
		       const void *key, 
		       int (*compare)(const void *data1, 
		       const void *data2))
{
	const char *left = NULL;
	const char *middle = NULL;
	const char *right = NULL;
	int comp = 0;
	
	assert(base != NULL);
	assert(key != NULL);
	assert(compare != NULL);
	assert(n_elements > 0);
	assert(elem_size > 0);
	
	left = (char *)base;
	right = (char *)base + elem_size * (n_elements - 1);
	
	do 
	{
		middle = left + elem_size * ((right - left)/(elem_size * 2));
		comp = compare(middle, key);
		
		if (comp < 0) 
		{
			left = middle + elem_size;
		}
		else
		{
			right = middle - elem_size;
		}
	} while ((0 != comp) && left <= right);

	if (0 == comp)
	{
		return ((void *)middle);
	}
	
	return (NULL);
}

/*Complexity: O(Log n)*/
void *BinaryRecSearch(const void *base,
		      size_t n_elements,
		      size_t elem_size,
		      const void *key,
		      int (*compare)(const void *data1, 
				     const void *data2))
{
	const char *left = NULL;
	const char *right = NULL;
	const char *middle = NULL;
	int comp = 0;
	
	assert(base != NULL);
	assert(key != NULL);
	assert(compare != NULL);
	assert(n_elements > 0);
	assert(elem_size > 0);
	
	left = (char *)base;
	right = left + (n_elements - 1) * elem_size;
	
	if (compare(key, right) > 0 || compare(key,left) < 0 || (left <= right))
	{
		return (NULL);
	}


	middle = left + elem_size * ((right - left)/(elem_size * 2));
	comp = compare(middle, key);
	
	/*Terminating Case*/
	if (0 == comp)
	{
		return ((void *)middle);
	}
	
	/*Progress through*/
	if (comp < 0)
	{
		return (BinaryRecSearch(middle + elem_size, 
					n_elements/2, 
					elem_size, 
					key, 
					compare));
	}

	return (BinaryRecSearch(left, 
				n_elements/2, 
				elem_size, 
				key, 
				compare));

}

/*
Time Complexity : O(√n)
Auxiliary Space : O(1)
*/
void *JumpSearch(const void *base,
		   size_t n_elements,
		   size_t elem_size,
		   const void *key,
		   int (*compare)(const void *data1, 
		   		  const void *data2))
{
	const char *jumper = NULL;
	const char *runner = NULL;
	const char *end = NULL;
	int step = 0;
	
	assert(base != NULL);
	assert(n_elements > 0);
	assert(elem_size > 0);
	
	jumper = (char *)base;
	end = (char *)base + (n_elements - 1) * elem_size;
	
	/*The value of the function ((n/m) + m-1) will be minimum when m = √n. 
	Therefore, the best step size is m = √n.*/
	step = sqrt(n_elements) * elem_size;

	/*jump through elements*/
	while ((jumper + step <= end) && (compare(jumper + step, key) < 0))
	{
		jumper += step;
	}
	
	runner = jumper;
	
	/*linear search*/
	while ((runner <= end) && (runner <= jumper + step))
	{
		if (0 == compare(runner, key))
		{
			return ((void *)runner);
		}
		
		runner += elem_size;
	}
	
	return (NULL);
}


/*
NOTES:
1) Works only sorted arrays.
2) The optimal size of a block to be jumped is O(√ n). 
   This makes the time complexity of Jump Search O(√n)
3) The time complexity of Jump Search is between Linear Search O(n) 
   and Binary Search O (Log n)
4) Binary Search is better than Jump Search, 
5) Jump search has an advantage that we traverse back only once (Binary Search may require up to O(Log n) jumps, consider a situation where the element to be search is the smallest element or smaller than the smallest). So in a systems where jumping back is costly, we use Jump Search.
*/
