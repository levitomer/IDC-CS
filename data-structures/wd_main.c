/*C program to init WATCHDOG executed as independent process*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "wd.h"

int main(int argc, char *argv[])
{
	printf("WATCHDOG started (PID: %d)\n", (int)getpid());

	/*indicating watchdog that app section is done*/
	g_wd = 1;

	if (WDStart(argc, argv) != 0)
	{
		perror("Error: starting watchdog failed in watchdog\n");

		return (1);
	}

	return (0);
}
