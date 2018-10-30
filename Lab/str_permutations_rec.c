#include <stdio.h>
#include <string.h>

/* Function to swap values at two pointers */
void Swap(char *x, char *y)
{
	char temp = *x;
	*x = *y;
	*y = temp;

	return;
}

/*	Function to print permutations of string
	This function takes three parameters:
	1. String
	2. Starting index of the string
	3. Ending index of the string.
*/
void StrPermutations(char *str, int left, int right)
{
	int i = 0;

	if (left == right)
	{
		printf("%s\n", str);
	}
	else
	{
		for (i = left; i <= right; ++i)
		{
			Swap((str + left), (str + right));
			StrPermutations(str, left + 1, right);
			Swap((str + left), (str + i)); /*backtrack*/
		}
	}

	return;
}

int main()
{
	char str[] = "ABC";
	int n = strlen(str);
	StrPermutations(str, 0, n - 1);

	return (0);
}
