#include <stdio.h> /**/

#include "h_table.h"
#include "dlist.h"

struct hash_table_st
{
    int (*is_equal) (const void *table_data,
                            const void *data,
                            void *is_equal_param);
    int (*hash_func) (const void *data, void *hash_param);
    void *is_equal_param;
    void *hash_param;
    size_t table_size;
    dlist_t *table[1];
};

int TestCreateAndDestroy();
int TestInsert();
int TestIsEmpty();
int TestSize();
int TestForEach();
int TestFind();
/*int TestRemove();*/


int FuncPrint(void *node_data, void *param);
/*void print2DUtil(node_t *node, int space);*/
int IsEqual(const void *node_data,const void *data, void *param);
static void PrintErrorDetailsInt(char *func, int result, int line_NUM);
static void PrintErrorDetails(char *func, char *result, int line_NUM);
int Func(void *node_data, void *param);
 int Compare(const void *node_data,
            const void *data,
            void *param);
int HashFunc(const void *data, void *hash_param);
/*********************************************************************/
int main()
{
    int errors = 0;
    
       errors += TestCreateAndDestroy();
    errors += TestInsert();
    errors += TestIsEmpty();
    errors += TestSize();
    errors += TestFind();  
    errors += TestForEach();
    /*errors += TestRemove();*/
    
    if (errors > 0)
    {
        printf("\n%d function/s with errors\n",errors);
    }
    else
    {
        puts("ALL GOOD");
        /*puts("Segmentation fault (core dumped)");*/
    }
    
    return (0);
}
/*********************************************************************/
int TestCreateAndDestroy()
{
    int errors = 0;
    int hash_param = 1;
    int is_equal_param = 1;
    char *func = "TestCreateAndDestroy";
    
    hash_table_t *table = HTableCreate(IsEqual, HashFunc, 5, &hash_param, &is_equal_param);
    if (NULL == table)
    {
        PrintErrorDetails(func, "table" , __LINE__);
        ++errors;
    }
    if (HashFunc != table->hash_func)
    {
        PrintErrorDetails(func, "HashFunc" , __LINE__);
        ++errors;
    }       
    if (IsEqual != table->is_equal)
    {
        PrintErrorDetails(func, "IsEqual" , __LINE__);
        ++errors;
    }
    if (5 != table->table_size)
    {
        PrintErrorDetails(func, "5" , __LINE__);
        ++errors;
    }
    
    HTableDestroy(table);
    
    return (errors);
}
/*********************************************************************/
int TestInsert()
{
    int errors = 0;
    int hash_param = 1;
    int is_equal_param = 1;
    char *func = "TestInsert";
    int arr1[] = {12, 15, 21, 23, 31, 34, 41, 45, 56, 57, 58, 60, 71, 72, 84, 91, 92, 93, 94}; 
    int size = sizeof(arr1)/sizeof(int);
    int i = 0;
    hash_table_t *table = NULL;
    dlist_t *dlist = NULL;
        
    table = HTableCreate(IsEqual, HashFunc, 10, &hash_param, &is_equal_param);
     for (i = 0; i < size ; ++i)
     {
         HTableInsert(table, &arr1[i]);
     }
     dlist = table->table[9];
    if (DlistEnd(dlist) == DlistFind(DlistBegin(dlist), DlistEnd(dlist), IsEqual, &arr1[15], &is_equal_param))
    {
        PrintErrorDetails(func, "need to find!" , __LINE__);
        ++errors;
    }             
    if (DlistEnd(dlist) == DlistFind(DlistBegin(dlist), DlistEnd(dlist), IsEqual, &arr1[16], &is_equal_param))
    {
        PrintErrorDetails(func, "need to find!" , __LINE__);
        ++errors;
    }
    if (DlistEnd(dlist) == DlistFind(DlistBegin(dlist), DlistEnd(dlist), IsEqual, &arr1[16], &is_equal_param))
    {
        PrintErrorDetails(func, "need to find!" , __LINE__);
        ++errors;
    }
     if (DlistEnd(dlist) == DlistFind(DlistBegin(dlist), DlistEnd(dlist), IsEqual, &arr1[17], &is_equal_param))
    {
        PrintErrorDetails(func, "need to find!" , __LINE__);
        ++errors;
    }
      dlist = table->table[1];   
    if (DlistEnd(dlist) == DlistFind(DlistBegin(dlist), DlistEnd(dlist), IsEqual, &arr1[0], &is_equal_param))
    {
        PrintErrorDetails(func, "need to find!" , __LINE__);
        ++errors;
    }    
    if (DlistEnd(dlist) == DlistFind(DlistBegin(dlist), DlistEnd(dlist), IsEqual, &arr1[1], &is_equal_param))
    {
        PrintErrorDetails(func, "need to find!" , __LINE__);
        ++errors;
    } 
    if (DlistEnd(dlist) != DlistFind(DlistBegin(dlist), DlistEnd(dlist), IsEqual, &arr1[9], &is_equal_param))
    {
        PrintErrorDetails(func, "need to fail finding!" , __LINE__);
        ++errors;
    }     
                   
    HTableDestroy(table);
    
    return (errors);
}
/*********************************************************************/
int TestIsEmpty()
{
    int errors = 0;
    int hash_param = 1;
    int is_equal_param = 1;
    char *func = "TestIsEmpty";
    int arr1[] = {12, 15, 21, 23, 31, 34, 41, 45, 56, 57, 58, 60, 71, 72, 84, 91, 92, 93, 94}; 
    int size = sizeof(arr1)/sizeof(int);
    int i = 0;
    hash_table_t *table = NULL;
    
    table = HTableCreate(IsEqual, HashFunc, 10, &hash_param, &is_equal_param);
    
    if (1 != HTableIsEmpty(table))
    {
        PrintErrorDetails(func, "1" , __LINE__);
        ++errors;
    }     
        
     for (i = 0; i < 1 ; ++i)
     {
         HTableInsert(table, &arr1[i]);
     }

    if (0 != HTableIsEmpty(table))
    {
        PrintErrorDetails(func, "0" , __LINE__);
        ++errors;
    }     

     for (; i < size ; ++i)
     {
         HTableInsert(table, &arr1[i]);
     }
     
     if (0 != HTableIsEmpty(table))
    {
        PrintErrorDetails(func, "0" , __LINE__);
        ++errors;
    } 
    HTableDestroy(table);
    
    return (errors);
}   
/*********************************************************************/
int TestSize()
{
    int errors = 0;
    int hash_param = 1;
    int is_equal_param = 1;
    char *func = "TestSize";
    int arr1[] = {12, 15, 21, 23, 31, 34, 41, 45, 56, 57, 58, 60, 71, 72, 84, 91, 92, 93, 94}; 
    size_t size = sizeof(arr1)/sizeof(int);
    size_t i = 0;
    hash_table_t *table = NULL;
    
    table = HTableCreate(IsEqual, HashFunc, 10, &hash_param, &is_equal_param);
    
    if (0 != HTableSize(table))
    {
        PrintErrorDetails(func, "0" , __LINE__);
        ++errors;
    }     
        
     for (i = 0; i < 1 ; ++i)
     {
         HTableInsert(table, &arr1[i]);
     }

    if (1 != HTableSize(table))
    {
        PrintErrorDetails(func, "1" , __LINE__);
        ++errors;
    }     

     for (; i < size ; ++i)
     {
         HTableInsert(table, &arr1[i]);
     }
     
     if (size != HTableSize(table))
    {
        PrintErrorDetailsInt(func, size , __LINE__);
        ++errors;
    } 
    HTableDestroy(table);
    
    return (errors);
}   
/*********************************************************************/
int TestFind()
{
    int errors = 0;
    int hash_param = 1;
    int is_equal_param = 1;
    char *func = "TestFind";
    int arr1[] = {12, 15, 21, 23, 31, 34, 41, 45, 56, 57, 58, 60, 71, 72, 84, 91, 92, 93, 94}; 
    int size = sizeof(arr1)/sizeof(int);
    int i = 0;
    hash_table_t *table = NULL;
    
    table = HTableCreate(IsEqual, HashFunc, 10, &hash_param, &is_equal_param);
        
    if (NULL != HTableFind(table, &hash_param))
    {
        PrintErrorDetails(func, "NULL" , __LINE__);
        ++errors;
    }     
    
     for (i = 0; i < 1 ; ++i)
     {
         HTableInsert(table, &arr1[i]);
     }

    if (12 != *(int*)HTableFind(table, &arr1[0]))
    {
        PrintErrorDetails(func, "12" , __LINE__);
        ++errors;
    } 
    if (NULL != HTableFind(table, &arr1[1]))
    {
        PrintErrorDetails(func, "NULL" , __LINE__);
        ++errors;
    }
    
     for (; i < size ; ++i)
     {
         HTableInsert(table, &arr1[i]);
     }
     
    if (15 != *(int*)HTableFind(table, &arr1[1]))
    {
        PrintErrorDetails(func, "15" , __LINE__);
        ++errors;
    }     
     
    if (92 != *(int*)HTableFind(table, &arr1[16]))
    {
        PrintErrorDetails(func, "92" , __LINE__);
        ++errors;
    } 
    if (93 != *(int*)HTableFind(table, &arr1[17]))
    {
        PrintErrorDetails(func, "93" , __LINE__);
        ++errors;
    } 
    if (94 != *(int*)HTableFind(table, &arr1[18]))
    {
        PrintErrorDetails(func, "94" , __LINE__);
        ++errors;
    }          
    if (NULL != HTableFind(table, &hash_param))
    {
        PrintErrorDetails(func, "NULL" , __LINE__);
        ++errors;
    }     
            
    HTableDestroy(table);
    
    return (errors);
}      
/*********************************************************************/
int TestForEach()
{
    int errors = 0;
    int hash_param = 1;
    int is_equal_param = 1;
    char *func = "TestForEach";
    int arr1[] = {12, 15, 21, 23, 31, 34, 41, 45, 55, 57, 58, 60, 71, 72, 84, 91, 92, 93, 94};
    int check1 = 15;
    int check2 = 58;
    int check3 = 56;   
    
    int size = sizeof(arr1)/sizeof(int);
    int i = 0;
    hash_table_t *table = NULL;
    int ret = 0;
    dlist_t *dlist = NULL;
    dlist_iter_t iter = NULL;
        

        
    table = HTableCreate(IsEqual, HashFunc, 10, &hash_param, &is_equal_param);
    
    ret = HTableForEach(table, Func, &hash_param);
    if (ret != 0)
    {
        PrintErrorDetails(func, "0" , __LINE__);
        ++errors;
    }
    
    HTableInsert(table, &arr1[14]);
    ret = HTableForEach(table, Func, &hash_param);
    if (ret != 1)
    {
        PrintErrorDetails(func, "1" , __LINE__);
        ++errors;
    }     
     HTableDestroy(table);
     
    table = HTableCreate(IsEqual, HashFunc, 10, &hash_param, &is_equal_param);
    HTableInsert(table, &arr1[1]);
    ret = HTableForEach(table, Func, &hash_param);
    if (ret != 0)
    {
        PrintErrorDetails(func, "0" , __LINE__);
        ++errors;
    }
       dlist = table->table[1];     
       iter = DlistFind(DlistBegin(dlist), DlistEnd(dlist), IsEqual, &check1, &is_equal_param);
        
    if (15 != *(int*)(DlistGetData(iter)))
    {
        PrintErrorDetails(func, "15" , __LINE__);
        ++errors;
    }
    
     HTableInsert(table, &arr1[9]);
       dlist = table->table[5];          
     ret = HTableForEach(table, Func, &hash_param);
       iter = DlistFind(DlistBegin(dlist), DlistEnd(dlist), IsEqual, &check2, &is_equal_param);
    if (58 != *(int*)(DlistGetData(iter)))
    {
        PrintErrorDetails(func, "58" , __LINE__);
        ++errors;
    }    
     HTableDestroy(table);
      
    table = HTableCreate(IsEqual, HashFunc, 10, &hash_param, &is_equal_param);
           dlist = table->table[5];                   
     for (i = 0; i < size ; ++i)
     {
         HTableInsert(table, &arr1[i]);
     }
    HTableForEach(table, Func, &hash_param);
    /*HTableForEach(table, FuncPrint, &hash_param);*/
    iter = DlistFind(DlistBegin(dlist), DlistEnd(dlist), IsEqual, &check3, &is_equal_param);
    if (56 != *(int*)(DlistGetData(iter)))
    {
        PrintErrorDetails(func, "56" , __LINE__);
        ++errors;
    }   
      
          
     HTableDestroy(table);
    
    return (errors);
} 
/*
int HTableForEach(hash_table_t *table, 
                  int (*func)
                      (void *node_data,
                      void *param),
                  void *param); */
/*********************************************************************/
/*********************************************************************/
/*********************************************************************/
/*********************************************************************/

static void PrintErrorDetailsInt(char *func, int result, int line_NUM)
{
    fprintf(stderr, "Func: '%s'. result should be: '%d'. Line NUMber: %d\n", func, result, line_NUM);

    return;
}
static void PrintErrorDetails(char *func, char *result, int line_NUM)
{
    fprintf(stderr, "Func: '%s'. result should be: '%s'. Line NUMber: %d\n", func, result, line_NUM);

    return;
}
int FuncPrint(void *node_data, void *param)
{
    (void)(param);
    
    printf("%d, ", *(int*)node_data);
    
    return (0);
}

/* returns 1 if equal */
int IsEqual(const void *node_data, const void *data, void *param)
{
    (void)(param);
    
    return (*(int*)node_data == *(int*)data);
}

int HashFunc(const void *data, void *hash_param)
{
    (void)(hash_param);
    
    return (*(int*)data / 10);
}

int Func(void *node_data, void *param)
{
    (void)(param);
    if (*(int*)node_data > 50 && *(int*)node_data < 60)
    {
        ++*(int*)node_data;
    }
    if (*(int*)node_data > 80)
    {
        return (1);
    }
    return (0);
}




