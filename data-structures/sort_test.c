#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sort.h"

void PrintIntArray(int *arr, size_t size);

/***********************************************************************************/
/***********************************************************************************/

int TestInsertionSort(void);
int TestSelectionSort(void);
int TestBubbleSort(void);
int TestCountSort(void);
int TestRadixSort(void);

int TestQsortSort(void);
static int IntCompareFunc(const void *data1, const void *data2);

void WhaleFail(int errors);
void PromptSuccess(void);

int main()
{
    int error_count = 0;
    double time_spent;
/*    error_count += TestRadixSort();*/
clock_t end;
	clock_t begin = clock();

/* here, do your time-consuming job */


    	error_count += TestQsortSort();
    	
    	 end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("the time your code run is : %f", time_spent);
    if (0 == error_count)
    {
        PromptSuccess();
    }
    else
    {
        WhaleFail(error_count);
    }
    
    return (0);
}

/***********************************************************************************/
/***********************************************************************************/

int TestInsertionSort(void)
{
    int errors_found = 0;
    int single_element[1] = {0};
    int unsorted_array[] = {6, 7, 1, 2, 18, 3, 55, 55, 89, 1};
    int sorted_array[] = {1, 1, 2, 3, 6, 7, 18, 55, 55, 89};
    int i = 0;
    
    /*Test with unsorted array*/
    puts("Input array -");
    PrintIntArray(unsorted_array, 10);
    
    InsertionSort(unsorted_array, 10);
    
    puts("\n\nOutput after your insertion sort - ");
    PrintIntArray(unsorted_array, 10);
    
    while (i < 10)
    {
        if (unsorted_array[i] != sorted_array[i])
        {
            ++errors_found;
            break;
        }
        ++i;
    }
    
    puts("\n\nTesting Insertion Sort for Single element array\n(you should not see \"segmentation fault\")");

    if(single_element[0] != 0)
    {
        ++errors_found;
    }
    
    return (errors_found);
}

/***********************************************************************************/
/***********************************************************************************/

int TestBubbleSort(void)
{
    int errors_found = 0;
    int single_element[1] = {0};
    int unsorted_array[] = {6, 7, 1, 2, 18, 3, 55, 55, 89, 1};
    int sorted_array[] = {1, 1, 2, 3, 6, 7, 18, 55, 55, 89};
    int i = 0;
    
    /*Test with unsorted array*/
    puts("Input array -");
    PrintIntArray(unsorted_array, 10);
    
    BubbleSort(unsorted_array, 10);
    
    puts("\n\nOutput after your Bubble sort - ");
    PrintIntArray(unsorted_array, 10);
    
    while (i < 10)
    {
        if (unsorted_array[i] != sorted_array[i])
        {
            ++errors_found;
            break;
        }
        ++i;
    }
    
    puts("\n\nTesting Bubble Sort for Single element array\n(you should not see \"segmentation fault\")");

    if(single_element[0] != 0)
    {
        ++errors_found;
    }
    
    return (errors_found);
}

/***********************************************************************************/
/***********************************************************************************/

int TestSelectionSort(void)
{
    int errors_found = 0;
    int single_element[1] = {0};
    int unsorted_array[] = {6, 7, 1, 2, 18, 3, 55, 55, 89, 1};
    int sorted_array[] = {1, 1, 2, 3, 6, 7, 18, 55, 55, 89};
    int i = 0;
    
    /*Test with unsorted array*/
    puts("Input array -");
    PrintIntArray(unsorted_array, 10);
    
    InsertionSort(unsorted_array, 10);
    
    puts("\n\nOutput after your Selection sort - ");
    PrintIntArray(unsorted_array, 10);
    
    while (i < 10)
    {
        if (unsorted_array[i] != sorted_array[i])
        {
            ++errors_found;
            break;
        }
        ++i;
    }
    
    puts("\n\nTesting Selection Sort for Single Element array\n(you should not see \"segmentation fault\")");

    if(single_element[0] != 0)
    {
        ++errors_found;
    }
    
    return (errors_found);
}

/***********************************************************************************/
/***********************************************************************************/

int TestCountSort(void)
{
    int errors_found = 0;
    int single_element[1] = {0};
    int unsorted_array[] = {6, 7, 1, 2, -18, 3, -55, 55, 89, 1};
    int sorted_array[] = {-55, -18, 1, 1, 2, 3, 6, 7, 55, 89};
    int i = 0;
    int from = -90;
    int to = 150;
    int *dest = (int*)malloc(sizeof(int) * 10);
    if (NULL == dest)
    {
        puts("ERROR: malloc failed in count sort.");
        return (1);
    }
    
    /*Test with unsorted array*/
    puts("\nInput array for Count sort -");
    PrintIntArray(unsorted_array, 10);
    
    CountSort(unsorted_array, 10, from, to, dest);
    
    puts("\n\nOutput after your Count sort - ");
    PrintIntArray(dest, 10);
    
    while (i < 10)
    {
        if (dest[i] != sorted_array[i])
        {
            ++errors_found;
            break;
        }
        ++i;
    }
    
    puts("\n\nTesting Count Sort for Single element array\n(you should not see \"segmentation fault\")");

    if(single_element[0] != 0)
    {
        ++errors_found;
    }
    
    free(dest);
    
    return (errors_found);
}

/***********************************************************************************/
/***********************************************************************************/

int TestRadixSort()
{
    int errors_found = 0;
    int single_element[1] = {0};
    int unsorted_mixed_array[] = {6, 7, 1, 2, -18, 3, -55, 55, 89, 1};
    int sorted_array[] = {-55, -18, 1, 1, 2, 3, 6, 7, 55, 89};
    int i = 0;
    int *dest = (int*)malloc(sizeof(int) * 10);
    if (NULL == dest)
    {
        puts("ERROR: malloc failed in radix sort.");
        return (1);
    }
    
    /*Test with unsorted array*/
    puts("\nInput array for Radix sort -");
    PrintIntArray(unsorted_mixed_array, 10);
    
    RadixSort(unsorted_mixed_array, 10, 21);
    
    puts("\n\nOutput after your Radix sort - ");
    PrintIntArray(unsorted_mixed_array, 10);
    
    while (i < 10)
    {
        if (unsorted_mixed_array[i] != sorted_array[i])
        {
            ++errors_found;
            break;
        }
        ++i;
    }
    
    puts("\n\nTesting Count Sort for Single element array\n(you should not see \"segmentation fault\")");
    
    if(single_element[0] != 0)
    {
        ++errors_found;
    }
    
    free(dest);
    
    return (errors_found);
}

/***********************************************************************************/
/***********************************************************************************/

int TestQsortSort(void)
{
    int errors_found = 0;
    int i = 0;
    int unsorted_mixed_array[] = {6, 7, 1, 2, -18, 3, -55, 55, 89, 1};
    int sorted_array[] = {-55, -18, 1, 1, 2, 3, 6, 7, 55, 89};

    puts("\nInput array for Qsort sort -");
    PrintIntArray(unsorted_mixed_array, 10);
    
    Qsort(unsorted_mixed_array, 10, sizeof(int), IntCompareFunc);
    
    puts("\n\nOutput after your Qsort sort - ");
    PrintIntArray(unsorted_mixed_array, 10);

    while (i < 10)
    {
        if (unsorted_mixed_array[i] != sorted_array[i])
        {
            ++errors_found;
            break;
        }
        ++i;
    }

    return (errors_found);
}

/***********************************************************************************/
/***********************************************************************************/

static int IntCompareFunc(const void *data1, const void *data2)
{
    return (*(int *)data1 - *(int *)data2);
}

/***********************************************************************************/
/***********************************************************************************/

void WhaleFail(int errors)
{
    printf("\nHa! you failed with %d errors... Here is a Fail whale.\n", errors);
    puts("\n▄██████████████▄▐█▄▄▄▄█▌");
    puts("███▌██▌▄▌▄▐▐▌███▌▀▀██▀▀");
    puts("██████▌▄▌▄▐▐▌▀███▄▄█▌");
    puts("▄▄▄▄███████████████");
    
    return;
}



/***********************************************************************************/
/***********************************************************************************/

void PrintIntArray(int *arr, size_t size)
{
    int i = 0;
    
    /*Print element while there are elements to print*/
    while (i < size)
    {
        printf("%d ", arr[i]);
        ++i;
    }
    puts(""); /*output to screen what?!*/

    return;
}

/***********************************************************************************/
/***********************************************************************************/


void PromptSuccess()
{
    puts("\nOK \nyou did it. happy?! \n");
    





































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































puts("░░█▀░░░░░░░░░░░▀▀███████░░░░");





































puts("░░█▌░░░░░░░░░░░░░░░▀██████░░░");




































































































































































































































































































































































































































































































































































































































































































































puts("░█▌░░░░░░░░░░░░░░░░███████▌░░ ");




































































































































































puts("░█░░░░░░░░░░░░░░░░░████████░░");













































































puts("▐▌░░░░░░░░░░░░░░░░░▀██████▌░░ ");




























































puts("░▌▄███▌░░░░▀████▄░░░░▀████▌░░");



































































































































puts("▐▀▀▄█▄░▌░░░▄██▄▄▄▀░░░░████▄▄░");





































































































puts("▐░▀░░═▐░░░░░░══░░▀░░░░▐▀░▄▀▌▌ ");



































































puts("▐░░░░░▌░░░░░░░░░░░░░░░▀░▀░░▌▌");










































































puts("▐░░░▄▀░░░▀░▌░░░░░░░░░░░░▌█░▌▌");







































































puts("░▌░░▀▀▄▄▀▀▄▌▌░░░░░░░░░░▐░▀▐▐░");














































































































































































































































































































































































puts("░▌░░▌░▄▄▄▄░░░▌░░░░░░░░▐░░▀▐░░ ");









































































puts("░█░▐▄██████▄░▐░░░░░░░░█▀▄▄▀░░ ");














































































puts("░▐░▌▌░░░░░░▀▀▄▐░░░░░░█▌░░░░░░ ");












puts("░░█░░▄▀▀▀▀▄░▄═╝▄░░░▄▀░▌░░░░░░ ");































































puts("░░░▌▐░░░░░░▌░▀▀░░▄▀░░▐░░░░░░░");




















































































puts("░░░▀▄░░░░░░░░░▄▀▀░░░░█░░░░░░░ ");




















puts("░░░▄█▄▄▄▄▄▄▄▀▀░░░░░░░▌▌░░░░░░ ");











puts("░░▄▀▌▀▌░░░░░░░░░░░░░▄▀▀▄░░░░░ ");












































































































































































































puts("▄▀░░▌░▀▄░░░░░░░░░░▄▀░░▌░▀▄░░░ ");





























































































































puts("░░░░▌█▄▄▀▄░░░░░░▄▀░░░░▌░░░▌▄▄ ");






















































































































































































puts("░░░▄▐██████▄▄░▄▀░░▄▄▄▄▌░░░░▄░");











































































































































puts("░░▄▌████████▄▄▄███████▌░░░░░▄ ");











































































































































puts("░▄▀░██████████████████▌▀▄░░░░ ");











































































































































































puts("▀░░░█████▀▀░░░▀███████░░░▀▄░░ ");











































































































































































































































































































































































































































puts("░░░░▐█▀░░░▐░░░░░▀████▌░░░░▀▄░ ");
























































































































puts("░░░░░░▌░░░▐░░░░▐░░▀▀█░░░░░░░▀ ");















puts("░░░░░░▐░░░░▌░░░▐░░░░░▌░░░░░░░");



















































































































































puts("░╔╗║░╔═╗░═╦═░░░░░╔╗░░╔═╗░╦═╗░ ");





























































































































puts("░║║║░║░║░░║░░░░░░╠╩╗░╠═╣░║░║░ ");

























































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































puts("░║╚╝░╚═╝░░║░░░░░░╚═╝░║░║░╩═╝░");

    return;
}
























