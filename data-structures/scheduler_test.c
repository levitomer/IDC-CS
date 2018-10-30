#include <stdio.h>
#include "scheduler.h"

int cnt = 0;

int print(void*);
int print2(void*);
int print3(void*);
int stop(void *param);
int clear(void *param);

   
int TestSchedulerCreate(void);
int TestSchedulerIsEmpty(void);
int TestSchedulerSize(void);
int TestSchedulerRun(void);
int TestSchedulerRemove(void);
int TestSchedulerClear(void);
    
int main()
{
    int ok = 0;
    
    ok += TestSchedulerCreate(); 
    ok += TestSchedulerIsEmpty();    
    ok += TestSchedulerSize();
    ok += TestSchedulerRun();
    ok += TestSchedulerRemove();
    ok += TestSchedulerClear();
    
    if (!ok)
    {
        puts("pass all the test");
    }
    
    else
    {
        printf("there is %d\n errors",ok);
    }
      return (0);
}

int TestSchedulerCreate(void)
{
    scheduler_t *sched = SchedulerCreate();
    SchedulerDestroy(sched);
    
    return (0);
}

int TestSchedulerIsEmpty(void)
{
    int errors = 0;
    scheduler_t *sched = SchedulerCreate();
    if(!SchedulerIsEmpty(sched))
    {
        puts("1. should be empty");
        ++errors;
    }
    SchedulerDestroy(sched);

    return(errors);    
}

int TestSchedulerSize(void)
{
    int errors = 0;
    scheduler_t *sched = SchedulerCreate();
    if(SchedulerSize(sched))
    {
        puts("2. should be empty");
        ++errors;
    }
    SchedulerDestroy(sched);

    return(errors);    
}

int TestSchedulerRun(void)
{
    int errors = 0;
    int check = 13;
    size_t size = 4;
    scheduler_t *sched = SchedulerCreate();
    SchedulerAddTask(sched, print,NULL,1);
    SchedulerAddTask(sched, print2,NULL,3);
    SchedulerAddTask(sched, print3,NULL,5);
    SchedulerAddTask(sched, stop, sched,6);
    
    if(SchedulerSize(sched) != size)
    {
        printf("3. should be %lu\n",size);
        ++errors;
    }
    
    if(SchedulerIsEmpty(sched))
    {
        puts("4. should not be empty");
        ++errors;
    }
    puts("wait 6 seconds");
    SchedulerRun(sched);
    
    if(cnt != check)
    {
        printf("5. cnt should be %d\n",check);
    }
    
    if(SchedulerIsEmpty(sched))
    {
        puts("6. should not be empty");
        ++errors;
    }
    
    SchedulerDestroy(sched);
    
    return (errors);
}

int TestSchedulerRemove(void)
{
    int errors = 0;
    int check = 13;
    size_t size = 4;
    uuid_t id;
    scheduler_t *sched = SchedulerCreate();
    SchedulerAddTask(sched, print,NULL,1);
    SchedulerAddTask(sched, print2,NULL,3);
    id = SchedulerAddTask(sched, print3,NULL,5);
    SchedulerAddTask(sched, stop, sched,6);
    
    if(SchedulerSize(sched) != size)
    {
        printf("7. should be %lu\n",size);
        ++errors;
    }
    
    if(SchedulerIsEmpty(sched))
    {
        puts("8. should not be empty");
        ++errors;
    }
    
    puts("wait 6 seconds - remove");
    cnt = 0;
    SchedulerRun(sched);
    if(cnt != check)
    {
        printf("9. cnt should be %d\n",check);
        ++errors;
    }
    
    if(SchedulerIsEmpty(sched))
    {
        puts("10. should be empty");
        ++errors;
    }
    
    SchedulerRemove(sched, id);
    puts("second run, wait 6 seconds ");
    SchedulerRun(sched);
    if(SchedulerSize(sched) != (size - 1))
    {
        printf("11. should be %lu\n",(size - 1));
        ++errors;
    }
    SchedulerDestroy(sched);
    
    return (errors);
}

int TestSchedulerClear(void)
{
    int errors = 0;
    int check = 13;
    size_t size = 4;
    
    scheduler_t *sched = SchedulerCreate();
    
    SchedulerAddTask(sched, print,NULL,1);
    SchedulerAddTask(sched, print2,NULL,3);
    SchedulerAddTask(sched, print3,NULL,5);
    SchedulerAddTask(sched, clear, sched,10);
    
    puts("wait 10 seconds");
    SchedulerRun(sched);
    
    if(!SchedulerIsEmpty(sched))
    {
        puts("11. should be empty");
        ++errors;
    }
    
    SchedulerDestroy(sched);
    return (errors);
    
}

int stop(void *param)
{
    SchedulerStop((scheduler_t *)param);
    
    return (0);
}

int clear(void *param)
{
    SchedulerClear((scheduler_t *)param);
    
    return (1);
}



int print(void *a)
{
    (void)a;
    ++cnt;
    return (0);
}
int print2(void *a)
{
    (void)a;
    cnt += 3;
    return (0);
}

int print3(void *a)
{
    (void)a;
    cnt += 5; 
    return (0);
}



