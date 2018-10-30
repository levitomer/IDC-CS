#ifndef SEARCH_H_ /* SEARCH_H_ */
#define SEARCH_H_

#include<stddef.h>

void *BinaryIterSearch(const void *base,
		       size_t n_elements, 
		       size_t elem_size, 
		       const void *key, 
		       int (*compare)(const void *data1, const void *data2));

void *BinaryRecSearch(const void *base, 
		      size_t n_elements, 
		      size_t elem_size, 
		      const void *key, 
		      int (*compare)(const void *data1, const void *data2));

void *JumpSearch(const void *base, 
		 size_t n_elements, 
		 size_t elem_size, 
		 const void *key, 
		 int (*compare)(const void *data1, const void *data2));

/*
The compare function returns:
negative value if data1 < data2
positive value if data1 > data2 
0 if data1 == data2
*/

#endif /*END OF SEARCH_H_*/
