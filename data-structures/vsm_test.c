#include <stdio.h> /**/
#include <unistd.h>
#include <stdlib.h> /**/
#include <string.h> /**/
#include "vsm.h"

#ifndef NDEBUG
#define MAGIC_NUM 0xDEADBEEF
#endif


static int TestVSMInit();
static int TestVSMalloc();

static int TestVSMTotalFree();
static int TestVSMMaxFree();
static int TestVSMClear();

static void PrintAddressesTillEnd(vsm_t *vsm, long size);
static void PrintErrorDetails(char *func, char *result, int line_NUM);
static void PrintTillEnd(vsm_t *vsm, long size);

/*********************************************************************************/
int main()
{
    int errors = 0;

    errors += TestVSMInit();
    errors += TestVSMalloc();
    errors += TestVSMClear();    
    errors += TestVSMTotalFree();
    errors += TestVSMMaxFree();
        
    if (errors > 0)
    {
        printf("%d function/s with errors\n",errors);
    }
    else
    {
        puts("ALL GOOD");
        /*puts("Segmentation fault (core dumped)");*/
    }

    return (0);
}
/*********************************************************************************/
/*********************************************************************************/

static int TestVSMInit()
{
    int errors = 0;
    char func[] = "TestVSMInit";
    vsm_t *checker = NULL;
    vsm_t *vsm = calloc(33, sizeof(char));
    /*long *mems = (long*)vsm;*/
    vsm = VSMInit(vsm, 33);
    /*PrintTillEnd(vsm, 4);*/
    if (vsm == NULL)
    {
        PrintErrorDetails(func, "NOT NULL", __LINE__);
        ++errors;
    }
    
    #ifndef NDEBUG
    if (*(long*)vsm != 32)
    {
        PrintErrorDetails(func, "32", __LINE__);
        ++errors;
    }
    if (*((long*)vsm + 1) != 24)
    {
        PrintErrorDetails(func, "24", __LINE__);
        ++errors;
    }    
    #else
    if (*(long*)vsm != 32)
    {
        PrintErrorDetails(func, "32", __LINE__);
        ++errors;
    }
    if (*((long*)vsm + 1) != 24)
    {
        PrintErrorDetails(func, "24", __LINE__);
        ++errors;
    }        
    #endif
    memset(vsm, 0, 33);       
    free(vsm);
/* when less the cap */
    #ifndef NDEBUG
    vsm = calloc(31, sizeof(char));
    checker = VSMInit(vsm, 31);
    if (checker != NULL)
    {
        PrintErrorDetails(func, "NULL", __LINE__);
        ++errors;
    }
    free(vsm);  
    #else
    vsm = calloc(23, sizeof(char));
    checker = VSMInit(vsm, 23);
    if (checker != NULL)
    {
        PrintErrorDetails(func, "NULL", __LINE__);
        ++errors;
    }  
    free(vsm);
    #endif
    
    return (errors);
}
/*********************************************************************************/
static int TestVSMalloc()
{
    int errors = 0;
    char func[] = "TestVSMalloc";
    long *checker = 0;
    vsm_t *vsm = calloc(33, sizeof(char));
    /*long *mems = (long*)vsm;*/
    vsm = VSMInit(vsm, 33);
    /*PrintTillEnd(vsm, 4);*/

    checker = VSMAlloc(vsm, 1);

/* malloc one block when room for one */    
    #ifndef NDEBUG
    if (*(long*)(checker - 1) != MAGIC_NUM)
    {
        PrintErrorDetails(func, "MAGIC_NUM", __LINE__);
        ++errors;
    }
    if (*(long*)(checker - 2) != -24)
    {
        PrintErrorDetails(func, "-24", __LINE__);
        ++errors;
    }
    #else
    if (*(long*)(checker - 1) != -16)
    {
        PrintErrorDetails(func, "-16", __LINE__);
        ++errors;
    }        
    #endif
    memset(vsm, 0, 33);
    free(vsm);
/*  malloc two blocks when room for two*/    
    vsm = calloc(56, sizeof(char));
    /*long *mems = (long*)vsm;*/
    vsm = VSMInit(vsm, 56);
    /*PrintTillEnd(vsm, 7);*/

    checker = VSMAlloc(vsm, 1);
    #ifndef NDEBUG
    if (*(long*)(checker - 1) != MAGIC_NUM)
    {
        PrintErrorDetails(func, "MAGIC_NUM", __LINE__);
        ++errors;
    }
    if (*(long*)(checker - 2) != -24)
    {
        PrintErrorDetails(func, "-24", __LINE__);
        ++errors;
    }
    if (*(long*)(checker + 1) != 24)
    {
        PrintErrorDetails(func, "24", __LINE__);
        ++errors;
    }
    #else
    if (*(long*)(checker - 1) != -16)
    {
        PrintErrorDetails(func, "-16", __LINE__);
        ++errors;
    }
    if (*(long*)(checker + 1) != 32)
    {
        PrintErrorDetails(func, "32", __LINE__);
        ++errors;
    }    
    #endif        
    /*printf("%p\n", (void*)checker);
    PrintTillEnd(vsm, 7);
    PrintAddressesTillEnd(vsm, 7);*/
    
    memset(vsm, 0, 56);
    free(vsm);
/*  malloc WHEN NO ROOM FOR ONE*/    
    vsm = calloc(32, sizeof(char));
    /*long *mems = (long*)vsm;*/
    vsm = VSMInit(vsm, 32);

    
    #ifndef NDEBUG
    checker = VSMAlloc(vsm, 9);

    if (checker != NULL)
    {
        PrintErrorDetails(func, "NULL", __LINE__);
        ++errors;
    }    
    #else
    checker = VSMAlloc(vsm, 17);
    /*PrintTillEnd(vsm, 4);*/
    if (checker != NULL)
    {
        PrintErrorDetails(func, "NULL", __LINE__);
        ++errors;
    }   
        
    #endif    
    free(vsm);    
/* malloc 3 different */
    vsm = calloc(88, sizeof(char));
    memset(vsm, 0, 88);    

    /*long *mems = (long*)vsm;*/
    vsm = VSMInit(vsm, 88);
    checker = VSMAlloc(vsm, 1);
    checker = VSMAlloc(vsm, 1);
    checker = VSMAlloc(vsm, 1);
        
    #ifndef NDEBUG
    if (*((long*)vsm + 1) != -24)
    {
        PrintErrorDetails(func, "24", __LINE__);
        ++errors;
    }
    if (*((long*)vsm + 4) != -24)
    {
        PrintErrorDetails(func, "-24", __LINE__);
        ++errors;
    }    
    if (*((long*)vsm + 7) != -24)
    {
        PrintErrorDetails(func, "-24", __LINE__);
        ++errors;
    }
    if (*((long*)vsm + 10) != 8)
    {
        PrintErrorDetails(func, "8", __LINE__);
        ++errors;
    }                    
    #else
    if (*((long*)vsm + 1) != -16)
    {
        PrintErrorDetails(func, "-16", __LINE__);
        ++errors;
    }
    if (*((long*)vsm + 3) != -16)
    {
        PrintErrorDetails(func, "-16", __LINE__);
        ++errors;
    }
    if (*((long*)vsm + 5) != -16)
    {
        PrintErrorDetails(func, "-16", __LINE__);
        ++errors;
    }        
    if (*((long*)vsm + 7) != 32)
    {
        PrintErrorDetails(func, "32", __LINE__);
        ++errors;
    }            
    #endif    
    free(vsm);    
    return (errors);
}
/*********************************************************************************/
static int TestVSMClear()
{
    int errors = 0;
    char func[] = "TestVSMClear";
    
    vsm_t *vsm = calloc(100, sizeof(char));
    vsm = VSMInit(vsm, 88);    
    VSMAlloc(vsm, 1);
    VSMAlloc(vsm, 1);
    VSMAlloc(vsm, 1);    
    VSMClear(vsm);
    
    if (*(long*)vsm != 88)
    {
        PrintErrorDetails(func, "88", __LINE__);
        ++errors;
    }     
    if (*(long*)((long*)vsm + 1) != 80)
    {
        PrintErrorDetails(func, "80", __LINE__);
        ++errors;
    }
        
    free(vsm);    
    return (errors);
}
/*********************************************************************************/
static int TestVSMTotalFree()
{
    int errors = 0;
    char func[] = "TestVSMTotalFree";
    long checker = 0;
    long *for_free = NULL;
    long *for_free1 = NULL;
    long *for_free2 = NULL;
    long *for_free3 = NULL;
    
    vsm_t *vsm = calloc(100, sizeof(char));
    vsm = VSMInit(vsm, 88);
    
    checker =     VSMTotalFree(vsm);

    if (checker != 80)
    {
        PrintErrorDetails(func, "80", __LINE__);
        ++errors;
    }     

    #ifndef NDEBUG
    VSMAlloc(vsm, 1);
    for_free = VSMAlloc(vsm, 1);
    VSMAlloc(vsm, 1);
    
    VSMFree(for_free);

    checker =     VSMTotalFree(vsm);    

    if (checker != 32)
    {
        PrintErrorDetails(func, "32", __LINE__);
        ++errors;
    }
    free(vsm);    
   /* free all. then check */
    vsm = calloc(100, sizeof(char));
    vsm = VSMInit(vsm, 88);
    
    
    for_free1 = VSMAlloc(vsm, 1);
    for_free2 = VSMAlloc(vsm, 1);
    for_free3 = VSMAlloc(vsm, 1);
    
    VSMFree(for_free1);    
    VSMFree(for_free2);    
    VSMFree(for_free3);
        
    
    checker =     VSMTotalFree(vsm);    

    if (checker != 80)
    {
        PrintErrorDetails(func, "80", __LINE__);
        ++errors;
    }
    free(vsm);        
   /* free all but first. then check */
    vsm = calloc(100, sizeof(char));
    vsm = VSMInit(vsm, 88);
    
    
    for_free1 = VSMAlloc(vsm, 1);
    for_free2 = VSMAlloc(vsm, 1);
    for_free3 = VSMAlloc(vsm, 1);
    
    VSMFree(for_free2);    
    VSMFree(for_free3);
        
    
    checker =     VSMTotalFree(vsm);    

    if (checker != 56)
    {
        PrintErrorDetails(func, "56", __LINE__);
        ++errors;
    }
/************************************************/    
    #else
    VSMAlloc(vsm, 1);
    for_free = VSMAlloc(vsm, 1);
    VSMAlloc(vsm, 1);
    
    VSMFree(for_free);

    checker =     VSMTotalFree(vsm);    

    if (checker != 48)
    {
        PrintErrorDetails(func, "48", __LINE__);
        ++errors;
    }
    free(vsm);    
   /* free all. then check */
    vsm = calloc(100, sizeof(char));
    vsm = VSMInit(vsm, 88);
    
    
    for_free1 = VSMAlloc(vsm, 1);
    for_free2 = VSMAlloc(vsm, 1);
    for_free3 = VSMAlloc(vsm, 1);
    
    VSMFree(for_free1);    
    VSMFree(for_free2);    
    VSMFree(for_free3);
        
    
    checker =     VSMTotalFree(vsm);    

    if (checker != 80)
    {
        PrintErrorDetails(func, "80", __LINE__);
        ++errors;
    }
    free(vsm);        
   /* free all but first. then check */
    vsm = calloc(100, sizeof(char));
    memset(vsm, 0, 100);    
    vsm = VSMInit(vsm, 88);
    
    
    for_free1 = VSMAlloc(vsm, 1);
    for_free2 = VSMAlloc(vsm, 1);
    for_free3 = VSMAlloc(vsm, 1);
    
    checker =     VSMTotalFree(vsm);    


    if (checker != 32)
    {
        PrintErrorDetails(func, "32", __LINE__);
        ++errors;
    }        
    
    VSMFree(for_free2);    
    VSMFree(for_free3);
        
    checker =     VSMTotalFree(vsm);    

    if (checker != 64)
    {
        PrintErrorDetails(func, "64", __LINE__);
        ++errors;
    }    
    #endif
    
    free(vsm);                 
    
    
    return (errors);
}
/*********************************************************************************/
static int TestVSMMaxFree()
{
    int errors = 0;
    char func[] = "TestVSMMaxFree";
    long checker = 0;
    long *for_free = NULL;
    long *for_free1 = NULL;
    long *for_free2 = NULL;
    long *for_free3 = NULL;
    vsm_t *vsm = NULL;
    
    vsm = calloc(100, sizeof(char));
    vsm = VSMInit(vsm, 88);
    
    /* after init */
    checker = VSMMaxFree(vsm);
    if (checker != 80)
    {
        PrintErrorDetails(func, "80", __LINE__);
        ++errors;
    }
    for_free1 = VSMAlloc(vsm, 1);
    for_free2 = VSMAlloc(vsm, 1);
    for_free3 = VSMAlloc(vsm, 9);
    
    #ifndef NDEBUG
    checker = VSMMaxFree(vsm);
    if (checker != 0)
    {
        PrintErrorDetails(func, "0", __LINE__);
        ++errors;
    }    
        
    VSMFree(for_free1);    
    VSMFree(for_free3);

    checker = VSMMaxFree(vsm);    

    if (checker != 32)
    {
        PrintErrorDetails(func, "32", __LINE__);
        ++errors;
    }            

    VSMFree(for_free2);    
    
    checker = VSMMaxFree(vsm);    
    
    if (checker != 80)
    {
        PrintErrorDetails(func, "80", __LINE__);
        ++errors;
    }        
    #else
    checker = VSMMaxFree(vsm);
    if (checker != 24)
    {
        PrintErrorDetails(func, "24", __LINE__);
        ++errors;
    }    
        
    VSMFree(for_free1);    
    VSMFree(for_free3);

    checker = VSMMaxFree(vsm);    

    if (checker != 48)
    {
        PrintErrorDetails(func, "48", __LINE__);
        ++errors;
    }            

    VSMFree(for_free2);    
    
    checker = VSMMaxFree(vsm);    
    
    if (checker != 80)
    {
        PrintErrorDetails(func, "80", __LINE__);
        ++errors;
    }
    #endif    
    free(vsm);                 
    
    return (errors);
}
/**********************************************************************************/
/*********************************************************************************/
/**********************************************************************************/
static void PrintTillEnd(vsm_t *vsm, long size)
{
    long i;
    
    for (i = 0; i < size; ++i)
    {
        printf("%ld|", *((long*)vsm + i));
    }
    puts("");
    
    return;
}
/******************************************************************************/
static void PrintAddressesTillEnd(vsm_t *vsm, long size)
{
    long i;
    
    for (i = 0; i < size; ++i)
    {
        printf("%p|", (void*)((long*)vsm + i));
    }
    puts("");
        
    return;
}
/******************************************************************************/
static void PrintErrorDetails(char *func, char *result, int line_NUM)
{
    fprintf(stderr, "Func: '%s'. result should be: '%s'. Line NUMber: %d\n", func, result, line_NUM);

    return;
}

