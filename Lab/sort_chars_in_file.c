#include <stdio.h>
#include <stdlib.h>  /*for EXIT_FAILURE*/
#include <limits.h>  /*for *_MAX*/

#define SIZE 10

/* "unsigned long int" chosen to match the ftell() limit,
  and numeric variables at top level start out zeroed*/
unsigned long int occurrences[UCHAR_MAX + 1];

int SortCharsInFile(const char *filename, char *result);

int main() 
{
	char *result = (char *)malloc(SIZE);
	if (NULL == result)
	{
		return (1);
	}
	
	SortCharsInFile("filename", result);
	printf("the sorted chars are:\n");
	printf("%s\n", result);
	
	return (0);
}

int SortCharsInFile(const char *filename, char *result)
{
	FILE *infp = NULL;
	int ch;


	infp = fopen(filename, "rt");
	/*ensure the file can be read*/
	if (!infp) 
	{
		perror(filename);
		
		return (EXIT_FAILURE);
	}

	/* count each character; EOF is a value distinct from*/
	/* all characters*/
	for(ch = fgetc(infp); ch != EOF; ch = fgetc(infp)) {
		/* cast to unsigned because arrays have no negative index*/
		occurrences[(unsigned char)ch] += 1;
	}

	/* once ch becomes EOF, the file has been read*/
	/* to either its end or an error*/
	if (ferror(infp)) 
	{
		fclose(infp);
		perror(filename);
		return EXIT_FAILURE;
	}

	/* close the successfully read file*/
	fclose(infp);
	infp = NULL;  /* it's good practice to cut off dangling pointers early*/

	/* now print all characters in the file in sorted order*/
	for (ch = 0; ch <= UCHAR_MAX; ++ch) 
	{
		for (; occurrences[ch] > 0; --occurrences[ch])
		{
			*result++ = ch;
		}
	}

	return (0);
}

