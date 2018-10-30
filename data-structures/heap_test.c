#include <stdio.h>

#include "heap.h"
#include "dyn_vec.h"

int Compare(const void *node_data, const void *data, void *param);

void TestHeapPush(void);
void TestHeapPop(void);
void TestHeapRemove1(void);
void TestHeapRemove2(void);
void TestHeapRemove3(void);

struct heap_st
{
    dyn_vec_t *vector;
    int (*compare)(const void *node_data, const void *data, void *param);
    void *param;
};

int arr_push[20];
int arr_remove1[20];
int arr_remove2[20];

int main()
{
    TestHeapPush();
    TestHeapPop();
    TestHeapRemove1();
    TestHeapRemove2();
    TestHeapRemove3();

    return (0);
}

int Compare(const void *node_data, const void *data, void *param)
{
    (void)param;
    
    return (*(int *)data - *(int *)node_data);
}

void TestHeapPush(void)
{
    heap_t *heap = HeapCreate(&Compare, NULL);
    int nums[] = {0, 1, 2, 3, 4, 5, 6, 7};
    int heap_nums[] = {7, 6, 5, 3, 2, 1, 4, 0};
    size_t i = 0;
    
    for (i = 0; i < sizeof(nums) / sizeof(nums[0]); ++i)
    {
        HeapPush(heap, &nums[i]);
    }
    
    for (i = 0; i < sizeof(heap_nums) / sizeof(heap_nums[0]); ++i)
    {
        arr_push[i] = **(int **)DynVecGetItemAddress(heap->vector, i);
    }
    
    for (i = 0; i < sizeof(heap_nums) / sizeof(heap_nums[0]); ++i)
    {
        if (arr_push[i] != heap_nums[i])
        {
            puts("Error in TestHeapPush");
            puts("Your Result:");
            for (i = 0; i < sizeof(heap_nums) / sizeof(heap_nums[0]); ++i)
            {
                printf("%3d", arr_push[i]);
            }
            puts("");
            puts("Right Result:");
            for (i = 0; i < sizeof(heap_nums) / sizeof(heap_nums[0]); ++i)
            {
                printf("%3d", heap_nums[i]);
            }
            puts("");
            break;
        }
    }
    
    HeapDestroy(heap);
    
    return;
}

void TestHeapPop(void)
{
    heap_t *heap = HeapCreate(&Compare, NULL);
    int nums[] = {50, 10, 40, 35, 15, 30, 37};
    int result = 0;
    size_t i = 0;
    
    for (i = 0; i < sizeof(nums) / sizeof(nums[0]); ++i)
    {
        HeapPush(heap, &nums[i]);
    }
    
    for (i = 0; i < (sizeof(nums) / sizeof(nums[0])) - 1; ++i)
    {
        HeapPop(heap);
    }
    
    result = **(int **)DynVecGetItemAddress(heap->vector, 0);
    if (result != nums[1])
    {
        printf("Error in TestHeapPop\n result should be '10'\n your result is %d\n", result);
    }
    
    HeapDestroy(heap);
    
    return;
}

void TestHeapRemove1(void)
{
    heap_t *heap = HeapCreate(&Compare, NULL);
    int nums[] = {50, 10, 40, 35, 15, 30, 37};
    int heap_nums[] = {50, 37, 40, 35, 15, 30};
    size_t i = 0;
    
    for (i = 0; i < sizeof(nums) / sizeof(nums[0]); ++i)
    {
        HeapPush(heap, &nums[i]);
    }
    
    HeapRemove(heap, &nums[1]);
    
    for (i = 0; i < sizeof(heap_nums) / sizeof(heap_nums[0]); ++i)
    {
        arr_remove1[i] = **(int **)DynVecGetItemAddress(heap->vector, i);
    }
    
    for (i = 0; i < sizeof(heap_nums) / sizeof(heap_nums[0]); ++i)
    {
        if (arr_remove1[i] != heap_nums[i])
        {
            puts("Error in TestHeapRemove1");
            puts("Your Result:");
            for (i = 0; i < sizeof(heap_nums) / sizeof(heap_nums[0]); ++i)
            {
                printf("%3d", arr_remove1[i]);
            }
            puts("");
            puts("Right Result:");
            for (i = 0; i < sizeof(heap_nums) / sizeof(heap_nums[0]); ++i)
            {
                printf("%3d", heap_nums[i]);
            }
            puts("");
            break;
        }
    }
    
    HeapDestroy(heap);
    
    return;
}

void TestHeapRemove2(void)
{
    heap_t *heap = HeapCreate(&Compare, NULL);
    int nums[] = {3, 1, 2, 4, 5, 6, 7, 8, 10, 9, 12, 13, 11};
    int heap_nums[] = {13, 10, 12, 7, 9, 6, 5, 1, 4, 3};
    size_t i = 0;
    
    for (i = 0; i < sizeof(nums) / sizeof(nums[0]); ++i)
    {
        HeapPush(heap, &nums[i]);
    }
    
    HeapRemove(heap, &nums[12]);
    HeapRemove(heap, &nums[2]);
    HeapRemove(heap, &nums[7]);
    
    for (i = 0; i < sizeof(heap_nums) / sizeof(heap_nums[0]); ++i)
    {
        arr_remove2[i] = **(int **)DynVecGetItemAddress(heap->vector, i);
    }
    
    for (i = 0; i < sizeof(heap_nums) / sizeof(heap_nums[0]); ++i)
    {
        if (arr_remove2[i] != heap_nums[i])
        {
            puts("Error in TestHeapRemove2");
            puts("Your Result:");
            for (i = 0; i < sizeof(heap_nums) / sizeof(heap_nums[0]); ++i)
            {
                printf("%3d", arr_remove2[i]);
            }
            puts("");
            puts("Right Result:");
            for (i = 0; i < sizeof(heap_nums) / sizeof(heap_nums[0]); ++i)
            {
                printf("%3d", heap_nums[i]);
            }
            puts("");
            break;
        }
    }
    
    HeapDestroy(heap);
    
    return;
}

void TestHeapRemove3(void)
{
    heap_t *heap = HeapCreate(&Compare, NULL);
    int nums[] = {3, 1, 2, 4, 5, 6, 7, 8, 10, 9, 12, 13, 11};
    int num = 50;
    size_t i = 0;
    
    for (i = 0; i < sizeof(nums) / sizeof(nums[0]); ++i)
    {
        HeapPush(heap, &nums[i]);
    }
    
    HeapRemove(heap, &num);
    
    HeapDestroy(heap);
    
    return;
}



