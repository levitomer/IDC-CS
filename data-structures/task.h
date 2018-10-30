#ifndef TASK_H_
#define TASK_H_

#include "uuid.h"

#include <time.h> /* time_t */

typedef struct task_st task_t;

task_t *TaskCreate(int (*func)(void *param),
					void *param,
					unsigned long interval_in_sec);

void TaskDestroy(task_t *task);

/* Update next run time of the task */
void TaskUpdate(task_t *task);

/* Comparison function
	Return 1 if task1 is before task 2 */
int TaskIsBefore(const void *task1, const void *task2, void *param);

/* Return the next run time of the task */
time_t TaskGetNextRunTime(const task_t *task);

/* Return the task uid */
uuid_t TaskGetID(const task_t *task);

/* Return 1 if task id equals to uid */
int TaskIsMatch(const void *task, const void *uid, void *param);

/* Run task.
	Return 0 if task should run again after the time interval.
	Return 1 if not required to run again. */
int TaskRun(task_t *task);

#endif /* TASK_H_ */

