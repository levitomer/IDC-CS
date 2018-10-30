#include <stdlib.h> /* malloc, free */
#include <assert.h>
#include <sys/time.h>

#include "task.h"

struct task_st
{
	uuid_t uid;
	time_t next_run_time;
	unsigned long interval_in_sec;
	int (*func)(void *param);
	void *param;
};

task_t *TaskCreate(int (*func)(void *param),
					void *param,
					unsigned long interval_in_sec)
{
	task_t *new_task = NULL;

	assert(func != NULL);
	assert(interval_in_sec != 0);

	new_task = (task_t *)malloc(sizeof(task_t));
	if (NULL == new_task)
	{
		return (NULL);
	}

	new_task->uid = UUIDCreate();
	new_task->interval_in_sec = interval_in_sec;
	new_task->next_run_time = time(NULL) + new_task->interval_in_sec;
	new_task->func = func;
	new_task->param = param;

	return(new_task);
}

/* Complexity O(1) */
void TaskDestroy(task_t *task)
{
	assert(task != NULL);

	free(task);
	task = NULL;

	return;
}

/* Complexity O(1) */
void TaskUpdate(task_t *task)
{
	assert(task != NULL);

	task->next_run_time = time(NULL) + task->interval_in_sec;

	return;
}

/* Complexity O(1) */
int TaskIsBefore(const void *task1, const void *task2, void *param)
{
	(void) param;

	assert(task1 != NULL);
	assert(task2 != NULL);

	return (difftime(TaskGetNextRunTime(task1), TaskGetNextRunTime(task2)) < 0);
}

/* Complexity O(1) */
time_t TaskGetNextRunTime(const task_t *task)
{
	assert(task != NULL);

	return(task->next_run_time);
}

/* Complexity O(1) */
uuid_t TaskGetID(const task_t *task)
{
	assert(task != NULL);

	return (task->uid);
}

/* Complexity O(1) */
int TaskIsMatch(const void *task, const void *uid, void *param)
{
	(void) param;

	assert(task != NULL);
	assert(uid != NULL);

	return (UUIDIsMatch(TaskGetID((const task_t *)task), *(const uuid_t *)uid));
}

/* Complexity O(1) */
/* Return 0 if task should run again after the time interval. or 1 if not */
int TaskRun(task_t *task)
{
	assert(task != NULL);

	return (task->func(task->param));
}
