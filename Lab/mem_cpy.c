#include <stdio.h>
#include <string.h>
#include <assert.h>

/*generic mem_cpy */
void *MemCpyVoid(void *dest, const void *src, size_t size)
{
	void *temp = NULL;

	assert(src != NULL)
	assert(dest != NULL);
	
	temp = dest;

	while (size > 0)
	{
		/*copy byte by byte*/
		*(char *)dest = *(char *)src;

		/*increamenting in terms of sizeof(char)*/
		++(*((char **)(&dest)));
		++(*((char **)(&src)));

		--size;
	}

	return(temp);
}

int main(void)
{
	char c_src[] = "Infinity Labs";
	/*settinga destination array to copy src to it*/
	char c_dest[100];

	int int_src[] = {10, 20, 30, 40, 50};
	int n = 0;
	int int_dest[n];
	int i = 0;

	MemCpyVoid(c_dest, c_src, strlen(c_src) + 1);
	printf("Copied string is %s", c_dest);

	n = sizeof(isrc)/sizeof(isrc[0]);
	MemCpyVoid(int_dest, int_src,  sizeof(int_src));
	printf("\nCopied array is ");

	for (i = 0; i < n; ++i)
	{
		printf("%d ", idest[i]);
	}

	return (0);
}
