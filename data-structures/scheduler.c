#include <stdlib.h> /* malloc, free */
#include <unistd.h> /* sleep */
#include <assert.h>

#include "pq.h"
#include "scheduler.h"
#include "task.h"

enum State
{
	RUNNING = 1,
	STOP = 0
};

struct scheduler_st
{
	pq_t *pq; /* scheduler tasks queue */
	int state; /* 1 = running | 0 = stopped */
};

scheduler_t *SchedulerCreate(void)
{
	scheduler_t *new_scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
	if (NULL == new_scheduler)
	{
		return (NULL);
	}

	new_scheduler->pq = PQCreate(TaskIsBefore, NULL);
	if (NULL == new_scheduler->pq)
	{
		free(new_scheduler);
		new_scheduler = NULL;
		return (NULL);
	}

	new_scheduler->state = RUNNING;

	return (new_scheduler);
}

/* Complexity O(n) */
void SchedulerDestroy(scheduler_t *scheduler)
{
	assert(scheduler != NULL);

	SchedulerClear(scheduler);
	PQDestroy(scheduler->pq);

	free(scheduler);
	scheduler = NULL;

	return;
}

/* Complexity O(1) */
int SchedulerIsEmpty(const scheduler_t *scheduler)
{
	assert(scheduler != NULL);

	return (PQIsempty(scheduler->pq));
}

/* Complexity O(n) */
size_t SchedulerSize(const scheduler_t *scheduler)
{
	assert(scheduler != NULL);

	return (PQSize(scheduler->pq));
}

/* Complexity O(n)  */
uuid_t SchedulerAddTask(scheduler_t *scheduler,
						int (*func)(void *param),
						void *param,
						unsigned long interval_in_sec)
{
	task_t *new_task = NULL;

	assert(scheduler != NULL);
	assert(func != NULL);

	new_task = TaskCreate(func, param, interval_in_sec);
	if (NULL == new_task)
	{
		return (UUIDGetInvalidId());
	}

	if (1 == PQEnqueue(scheduler->pq, new_task))
	{
		TaskDestroy(new_task);
		new_task = NULL;

		return (UUIDGetInvalidId());
	}

	return (TaskGetID(new_task));
}

/*
 * Complexity O(n)
 * Returns 1 if task isn't found or 0 if removed successfuly
 */
int SchedulerRemove(scheduler_t *scheduler, uuid_t uid)
{
	task_t *task_erase = (assert(scheduler != NULL),
						 (task_t *)PQErase(scheduler->pq, TaskIsMatch, &uid, NULL));


	if (NULL == task_erase)
	{
		return (1);
	}

	TaskDestroy(task_erase);

	return(0);
}

void SchedulerRun(scheduler_t *scheduler)
{
	task_t *curr_task = NULL;
	time_t curr_time;

	assert(scheduler != NULL);

	while (scheduler->state && !PQIsempty(scheduler->pq))
	{
		curr_task = PQDequeue(scheduler->pq);
		curr_time = time(NULL);

		/* case 1: suspend untill time to execute */
		while (TaskGetNextRunTime(curr_task) > curr_time)
		{
			sleep(TaskGetNextRunTime(curr_task) - curr_time);
			curr_time = time(NULL);
		}

		/* case 2: next run time is the current time */
		if (!TaskRun(curr_task))
		{
			TaskUpdate(curr_task);
			if (1 == PQEnqueue(scheduler->pq, curr_task))
			{
				TaskDestroy(curr_task);
			}
		}
		else
		{
			TaskDestroy(curr_task);
		}
	}

	scheduler->state = RUNNING;

	return;
}

/* Complexity O(1) */
void SchedulerStop(scheduler_t *scheduler)
{
	assert(scheduler != NULL);

	scheduler->state = STOP;

	return;
}

/* Complexity O(1) */
void SchedulerClear(scheduler_t *scheduler)
{
	assert(scheduler != NULL);

	while (!PQIsempty(scheduler->pq))
	{
		TaskDestroy(PQDequeue(scheduler->pq));
	}

	return;
}
