#include <stdio.h>
    
#include "search.h"        

#define ERR_MSG(func_name, result, correct) (printf("%s returned %d instead of %d (line %d)\n", func_name, result, correct,  __LINE__))
#define ERR_MSG_POINTERS(func_name, result, correct) (printf("%s returned %p instead of %p (line %d)\n", func_name, result, correct, __LINE__))
#define FINAL_ERR_MSG(errors) (printf("Total errors: %d :(\n", errors))
#define FINAL_SUCCESS (puts("OK! :)"))

unsigned int errors = 0;    

void TestJumpSearch(void);
void TestBinaryRecSearch(void);
void TestBinaryIterSearch(void);

        
int main(void)        
{        
    TestJumpSearch();
    TestBinaryRecSearch();
    TestBinaryIterSearch();
    
    if (0 == errors)
    {
        FINAL_SUCCESS;
    }
    else
    {
        FINAL_ERR_MSG(errors);
    }
    
    return (0);
}

/***************************************************************************/

/*
The compare function returns:
negative value if data1 < data2
positive value if data1 > data2
0 if data1 == data2
*/
int Compare(const void *data1, const void *data2)
{
    return (*(int*)data1 - *(int*)data2);
}

/***************************************************************************/

void TestBinaryIterSearch(void)
{
    int *res_p = 0;
    int *correct_p = NULL;
    char *func_name = "BinaryIterSearch";
    int arr[] = {1, 2, 4, 6, 8, 9, 13, 16, 20, 27, 30, 45, 60, 70, 100, 200};
    int arr2[] = {6};
    int fake_element = -3;
    int fake_element2 = 300;
    
    
    res_p = BinaryIterSearch(arr2, sizeof(arr2) / sizeof(arr2[0]), sizeof(int), &arr2[0], Compare);
    correct_p = &arr2[0];
    if (res_p != correct_p)
    {
        ERR_MSG(func_name, *res_p, *correct_p);
        ++errors;
    }
    
    res_p = BinaryIterSearch(arr2, sizeof(arr2) / sizeof(arr2[0]), sizeof(int), &fake_element, Compare);
    correct_p = NULL;
    if (res_p != correct_p)
    {
        ERR_MSG(func_name, *res_p, *correct_p);
        ++errors;
    }
    
    res_p = BinaryIterSearch(arr2, sizeof(arr2) / sizeof(arr2[0]), sizeof(int), &arr[5], Compare);
    correct_p = NULL;
    if (res_p != correct_p)
    {
        ERR_MSG(func_name, *res_p, *correct_p);
        ++errors;
    }

    res_p = BinaryIterSearch(arr2, sizeof(arr2) / sizeof(arr2[0]), sizeof(int), &fake_element2, Compare);
    correct_p = NULL;
    if (res_p != correct_p)
    {
        ERR_MSG(func_name, *res_p, *correct_p);
        ++errors;
    }    
        
        
        
        
    res_p = BinaryIterSearch(arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), &fake_element2, Compare);
    correct_p = NULL;
    if (res_p != correct_p)
    {
        ERR_MSG(func_name, *res_p, *correct_p);
        ++errors;
    }
    
    res_p = BinaryIterSearch(arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), &arr[9], Compare);
    correct_p = &arr[9];
    if (res_p != correct_p)
    {
        ERR_MSG(func_name, *res_p, *correct_p);
        ++errors;
    }
    
    res_p = BinaryIterSearch(arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), &arr[2], Compare);
    correct_p = &arr[2];
    if (res_p != correct_p)
    {
        ERR_MSG_POINTERS(func_name, (void*)res_p, (void*)correct_p);
        ++errors;
    }
    
    res_p = BinaryIterSearch(arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), &arr[15], Compare);
    correct_p = &arr[15];
    if (res_p != correct_p)
    {
        ERR_MSG_POINTERS(func_name, (void*)res_p, (void*)correct_p);
        ++errors;
    }
    
    res_p = BinaryIterSearch(arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), &fake_element, Compare);
    correct_p = NULL;
    if (res_p != correct_p)
    {
        ERR_MSG_POINTERS(func_name, (void*)res_p, (void*)correct_p);
        ++errors;
    }
    
    return;
}


/***************************************************************************/

void TestBinaryRecSearch(void)
{
    int *res_p = 0;
    int *correct_p = NULL;
    char *func_name = "BinaryRecSearch";
    int arr[] = {1, 2, 4, 6, 8, 9, 13, 16, 20, 27, 30, 45, 60, 70, 100, 200};
    int arr2[] = {6};
    int fake_element = -3;
    int fake_element2 = 300;
    
    
    res_p = BinaryRecSearch(arr2, sizeof(arr2) / sizeof(arr2[0]), sizeof(int), &arr2[0], Compare);
    correct_p = &arr2[0];
    if (res_p != correct_p)
    {
        ERR_MSG(func_name, *res_p, *correct_p);
        ++errors;
    }
    
    res_p = BinaryRecSearch(arr2, sizeof(arr2) / sizeof(arr2[0]), sizeof(int), &fake_element, Compare);
    correct_p = NULL;
    if (res_p != correct_p)
    {
        ERR_MSG(func_name, *res_p, *correct_p);
        ++errors;
    }
    
    res_p = BinaryRecSearch(arr2, sizeof(arr2) / sizeof(arr2[0]), sizeof(int), &arr[5], Compare);
    correct_p = NULL;
    if (res_p != correct_p)
    {
        ERR_MSG(func_name, *res_p, *correct_p);
        ++errors;
    }

    res_p = BinaryRecSearch(arr2, sizeof(arr2) / sizeof(arr2[0]), sizeof(int), &fake_element2, Compare);
    correct_p = NULL;
    if (res_p != correct_p)
    {
        ERR_MSG(func_name, *res_p, *correct_p);
        ++errors;
    }    
        
    res_p = BinaryRecSearch(arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), &fake_element2, Compare);
    correct_p = NULL;
    if (res_p != correct_p)
    {
        ERR_MSG(func_name, *res_p, *correct_p);
        ++errors;
    }
    
    res_p = BinaryRecSearch(arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), &arr[9], Compare);
    correct_p = &arr[9];
    if (res_p != correct_p)
    {
        ERR_MSG(func_name, *res_p, *correct_p);
        ++errors;
    }
    
    res_p = BinaryRecSearch(arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), &arr[2], Compare);
    correct_p = &arr[2];
    if (res_p != correct_p)
    {
        ERR_MSG_POINTERS(func_name, (void*)res_p, (void*)correct_p);
        ++errors;
    }
    
    res_p = BinaryRecSearch(arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), &arr[15], Compare);
    correct_p = &arr[15];
    if (res_p != correct_p)
    {
        ERR_MSG_POINTERS(func_name, (void*)res_p, (void*)correct_p);
        ++errors;
    }
    
    res_p = BinaryRecSearch(arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), &fake_element, Compare);
    correct_p = NULL;
    if (res_p != correct_p)
    {
        ERR_MSG_POINTERS(func_name, (void*)res_p, (void*)correct_p);
        ++errors;
    }
    
    return;
}


/***************************************************************************/

void TestJumpSearch(void)
{
    int *res_p = 0;
    int *correct_p = NULL;
    char *func_name = "JumpSearch";
    int arr[] = {1, 2, 4, 6, 8, 9, 13, 16, 20, 27, 30, 45, 60, 70, 100, 200};
    int arr2[] = {6};
    int fake_element = -3;
    int fake_element2 = 300;
    
    
    res_p = JumpSearch(arr2, sizeof(arr2) / sizeof(arr2[0]), sizeof(int), &arr2[0], Compare);
    correct_p = &arr2[0];
    if (res_p != correct_p)
    {
        ERR_MSG(func_name, *res_p, *correct_p);
        ++errors;
    }
    
    res_p = JumpSearch(arr2, sizeof(arr2) / sizeof(arr2[0]), sizeof(int), &fake_element, Compare);
    correct_p = NULL;
    if (res_p != correct_p)
    {
        ERR_MSG(func_name, *res_p, *correct_p);
        ++errors;
    }
    
    res_p = JumpSearch(arr2, sizeof(arr2) / sizeof(arr2[0]), sizeof(int), &arr[5], Compare);
    correct_p = NULL;
    if (res_p != correct_p)
    {
        ERR_MSG(func_name, *res_p, *correct_p);
        ++errors;
    }

    res_p = JumpSearch(arr2, sizeof(arr2) / sizeof(arr2[0]), sizeof(int), &fake_element2, Compare);
    correct_p = NULL;
    if (res_p != correct_p)
    {
        ERR_MSG(func_name, *res_p, *correct_p);
        ++errors;
    }    
        
    res_p = JumpSearch(arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), &fake_element2, Compare);
    correct_p = NULL;
    if (res_p != correct_p)
    {
        ERR_MSG(func_name, *res_p, *correct_p);
        ++errors;
    }
    
    res_p = JumpSearch(arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), &arr[9], Compare);
    correct_p = &arr[9];
    if (res_p != correct_p)
    {
        ERR_MSG(func_name, *res_p, *correct_p);
        ++errors;
    }
    
    res_p = JumpSearch(arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), &arr[2], Compare);
    correct_p = &arr[2];
    if (res_p != correct_p)
    {
        ERR_MSG_POINTERS(func_name, (void*)res_p, (void*)correct_p);
        ++errors;
    }
    
    res_p = JumpSearch(arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), &arr[15], Compare);
    correct_p = &arr[15];
    if (res_p != correct_p)
    {
        ERR_MSG_POINTERS(func_name, (void*)res_p, (void*)correct_p);
        ++errors;
    }
    
    res_p = JumpSearch(arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), &fake_element, Compare);
    correct_p = NULL;
    if (res_p != correct_p)
    {
        ERR_MSG_POINTERS(func_name, (void*)res_p, (void*)correct_p);
        ++errors;
    }
    
    return;
}



