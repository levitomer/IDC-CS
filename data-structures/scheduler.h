#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "uuid.h"

#include <stddef.h> /* size_t */

typedef struct scheduler_st scheduler_t;

scheduler_t *SchedulerCreate(void);

void SchedulerDestroy(scheduler_t *sched);

int SchedulerIsEmpty(const scheduler_t *sched);

size_t SchedulerSize(const scheduler_t *sched);

/*  * Add a task to the scheduler and return the task id.
	* func that is supplied by the user should return
	* 0 if the task is requested to be performed again in the future,
	* other value will cause removal of task from the scheduler.
*/
uuid_t SchedulerAddTask(scheduler_t *sched,
			int (*func)(void *param),
			void *param,
			unsigned long interval_in_sec);

/* Remove a specific task from the scheduler */
int SchedulerRemove(scheduler_t *sched, uuid_t uid);

/* Run the scheduler */
void SchedulerRun(scheduler_t *sched);

/* Stop the scheduler */
void SchedulerStop(scheduler_t *sched);

/* Clear all tasks from scheduler */
void SchedulerClear(scheduler_t *sched);

#endif /* SCHEDULER_H_ */

