/*C Program to test watch dog application*/
#include <stdio.h> /*printf, sleep*/
#include <errno.h> /*perror*/
#include <sys/types.h>
#include <unistd.h>

#include "wd.h"

int main(int argc, char *argv[])
{
	printf("APP started (PID: %d)\n", (int)getpid());

	/*start watchdog*/
	if (WDStart(argc, argv) != 0)
	{
		perror("Error: starting watchdog failed in app\n");

		return (1);
	}

	/*app routine*/
	while (1)
	{
		puts("app: pending for signal\n");
		sleep(1);
	}

	/*end watchdog*/
	// if (WDStop(argc, argv) != 0)
	// {
	// 	perror("Error: \n");
	// }

	return (0);
}
