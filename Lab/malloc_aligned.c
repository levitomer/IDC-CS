#include <stdlib.h>
#include <stdio.h>

/*function to allocate memory aligned upon the user request*/
void *AlignedMalloc(size_t required_bytes, size_t alignment)
{
	void *mem = NULL; /*points to the aligned memory*/
	void **aligned_mem = NULL; /*a pointer to the address to the aligned memory*/

	/*support alignments beyond system's malloc*/
	int offset = sizeof(void *) /*save a space used later by free*/
					     + (alignment /*saving extra space,
							   assumes alignment is a power of 2*/
					     - 1); /*leaving room for bookkeeping.*/

	/*using mallloc to allocate the memory*/
	mem = (void *)malloc(offset + required_bytes);
	if (NULL == mem)
	{
		return (NULL);
	}

	/*aligning the memory adderess*/
	aligned_mem = (void **)(((size_t)mem + offset)
													& (~(alignment - 1))); /* mask to assuere alignment*/

	/*store the address of mem inside the reserved space saved by offset*/
	*(aligned_mem - 1) = mem;

	/*returns the address to the aligned memory that mem points to*/
	return (aligned_mem);
}

void AlignedFree(void *p)
{
	/*converts aligned_mem in effect to void *aligned_mem[],
	  and fetches mem using -1 as an index*/
	free(*((void **)p - 1));

	return;
}

/*C Program to test malloc aligned function*/
int main(int argc, char *argv[])
{
	char **endptr;
	int *p = AlignedMalloc(100, strtol(argv[1], endptr, 10));

	printf ("%s: %p\n", argv[1], p);
	AlignedFree(p);

	return (0);
}
