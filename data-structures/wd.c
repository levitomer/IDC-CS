/*C Program to simulate watch dog tracing application*/
#include <stdio.h> /*printf*/
#include <stdlib.h> /*getenv*/
#include <unistd.h> /**/
#include <pthread.h> /*pthread_create, pthread_join*/
#include <semaphore.h>/*sem_wait, sem_post*/
#include <signal.h>/*SIGUSR1, SIGUSR2*/
#include <fcntl.h>/*O_CREAT, SEM_FAILED*/
#include <errno.h> /*perror*/

#include "wd.h"

typedef struct sigaction sig;

/*GLOBALS*/
	char **g_argv = NULL;
	int g_wd = 0; /*watchdog identifire*/
	static int g_term = 0; /*termination identifire*/
	static int g_pulse = 1; /*pulser*/
	pid_t g_pid;
	pthread_t app_scheduler_tid;
	scheduler_t *g_scheduler = NULL;
	extern char **environ;
/*END OF GLOBALS*/

/*LOCKS*/
	sem_t *sem;
/*END OF LOCKS*/

/*TASKs*/
	/*transfer signal SIGUSR1 to another process*/
	int Task1(void *param);
	/*signals SIGUSR2 to assure a process is still activated*/
	int Task2(void *param);
/*END OF TASKS*/

/*THREADs*/
	/*running scheduler*/
	void *Scheduler(void *param);
/*END OF THREADS*/

/*STATIC HELPRES*/
	/*initializing global variables*/
	static int Init();
	/*restart a non-responsive program*/
	static int Restart(void *param);
	/*closing the app safely*/
	static void Cleanup();
/*END OF HELPERS*/

/*SIGNAL HANDLER*/
	static void SignalHandler(int sig, siginfo_t *siginfo, void *context);
/*END OF SIGNAL HANDLER*/

/*starting watchdog*/
int WDStart(int argc, char **argv)
{
	char *const args[] = {"wd.out", NULL};
	g_argv = argv;
	pid_t child;

	if (Init())
	{
		return (1);
	}

	/*WATCHDOG*/
	if (g_wd)
	{
		g_pid = getppid();

		/*notify that watchdog scheduler is ready*/
		sem_post(sem);
		/*run the app scheduler as a thread*/
		Scheduler(g_scheduler);

	}
	/*APP*/
	else
	{
		if (getenv("WD_ENV") == NULL)
		{
			setenv("WD_ENV", "", 1);

			/*create a new identical process*/
			g_pid = fork();
			/*child process creation failed*/
			if (g_pid < 0)
			{
				perror("Error: fork faild");

				return (errno);
			}
			/*child process created successfuly*/
			else if (0 == g_pid)
			{
				/*runs WD instead the current process*/
				if (execv("wd.out", environ) < 0)
				{
					perror("Error: wd.out execv failed");

					return (errno);
				}
			}
		}
		else
		{
			g_pid = getppid();
		}
		/*notifying wd to run the scheduler*/
		sem_wait(sem);
		/*run the app scheduler as a thread*/
		if (pthread_create(&app_scheduler_tid, NULL, &Scheduler, g_scheduler) != 0)
		{
			perror("Error: app scheduler thread failed\n");

			return (errno);
		}
	}

	return (errno);
}

static int Init()
{
	uuid_t task1_id;
	uuid_t task2_id;

	sig sigusr;

	sigusr.sa_sigaction = &SignalHandler;
	sigusr.sa_flags = SA_SIGINFO;

	if (sigaction(SIGUSR1, &sigusr, NULL) != 0)
	{
		perror("Error: sigaction SIGUSR1 failed\n");

		return (errno);
	}

	if (sigaction(SIGUSR2, &sigusr, NULL) != 0)
	{
		perror("Error: sigaction SIGUSR2 failed\n");

		return (errno);
	}

	g_scheduler = SchedulerCreate();
	if (NULL == g_scheduler)
	{
		perror("Error: SCHEDULER creation faild");

		return (errno);
	}

	task1_id = SchedulerAddTask(g_scheduler, Task1, NULL, 1);
	if(UUIDIsMatch(task1_id , UUIDGetInvalidId()))
	{
		perror("Error: TASK1 addition failed\n");

		SchedulerDestroy(g_scheduler);

		return (errno);
	}

	task2_id = SchedulerAddTask(g_scheduler, Task2, NULL, 3);
	if(UUIDIsMatch(task2_id , UUIDGetInvalidId()))
	{
		perror("Error: TASK2 addition failed\n");

		SchedulerDestroy(g_scheduler);

		return (errno);
	}

	/*opens semaphore with both read & write permissions*/
	sem = sem_open("/sem", O_CREAT, S_IRUSR | S_IWUSR, 0);
	if (SEM_FAILED == sem)
	{
			perror("Error: sem_open failed for APP\n");

			return (errno);
	}

	return (0);
}

static void SignalHandler(int sig, siginfo_t *siginfo, void *context)
{
	(void) context;

	switch (sig)
	{
		case SIGUSR1:

			++g_pulse;

			fprintf(stdout, "PID: %d pulse: (%d) Recieved: SIGUSR1\n", siginfo->si_pid, g_pulse);
			break;

		case SIGUSR2:

			g_term = 1;

			fprintf(stdout, "PID: %d pulse: (%d) Recieved: SIGUSR2\n", siginfo->si_pid, g_pulse);
			break;

		default:

			printf("Received %d Signal\n", sig);
			return;
	}

	return;
}

void *Scheduler(void *scheduler)
{
	while(1)
	{
		if (!g_term)
		{
			SchedulerRun((scheduler_t *)g_scheduler);
		}
	}

	return (NULL);
}

int Task1(void *param)
{
	(void)param;

	printf("TASK 1:\n");
	if (kill(g_pid, SIGUSR1) != 0)
	{
		fprintf(stderr, "Failed to send signal %d to %d\n", SIGUSR1, g_pid);
	}

	return (0);
}

/*check the communication between application and watchdog*/
int Task2(void *param)
{
	(void)param;

	printf("TASK 2: pulse (%d)\n", g_pulse);
	/*check communication between two processes*/
	if (g_pulse != 0)
	{
		g_pulse = 0;
	}
	/*the application havn't responded*/
	else
	{
		Restart(param);
	}

	return (0);
}

/*restart the process whom stop responding*/
static int Restart(void *param)
{
	pid_t new_process;

	char *filename = NULL;

	filename = (g_wd) ? getenv("_") : "wd.out";

	/*create an identical child process*/
	new_process = fork();
	if (0 == new_process)
	{
		/*overlay that child process to be the watchdog*/
		if (0 > execv(filename, g_argv))
		{
			perror("Error: restart failed\n");

			return (errno);
		}
	}
}

/*stops watchdog*/
int WDStop(int argc, char const *argv[])
{
	clock_t begin = clock();

	double timeout = 0;

	/*trying to cleanup application*/
	while((timeout < 10)  || !g_term)
	{
		printf("%f\n", timeout);

		/*acknowledgement recieved*/
		if (kill(argv[0], SIGUSR2) != 0)
		{
			fprintf(stderr, "Failed to send signal %d to %d\n", SIGUSR2, g_pid);
		}
		else
		{
			/*close the app safely*/
			Cleanup();
		}

		clock_t end = clock();
		timeout = (double)(end - begin) / CLOCKS_PER_SEC;
	}

	/*acknoledgement haven't recieved*/
	if (kill(argv[0], SIGKILL) != 0)
	{
		fprintf(stderr, "Failed to send signal %d to %d\n", SIGKILL, g_pid);
	}

	return (0);
}

/*closing the application*/
static void Cleanup(void *param)
{
	SchedulerStop(g_scheduler);
	SchedulerDestroy(g_scheduler);
	pthread_join(app_scheduler_tid, NULL);
	sem_unlink("/sem");

	return;
}
