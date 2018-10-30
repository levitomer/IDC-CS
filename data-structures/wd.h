#ifndef WATCH_DOG_
#define WATCH_DOG_

#include "scheduler.h"

extern int g_wd;

int WDStart(int argc, char **argv);

int WDStop(int argc, char const *argv[]);

#endif /*	WATCH_DOG_H_ */
