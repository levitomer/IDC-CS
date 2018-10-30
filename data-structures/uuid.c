#include <stdlib.h> /* malloc, free */
#include <unistd.h>

#include "uuid.h"

uuid_t UUIDCreate(void)
{
	uuid_t new_uid;

	static unsigned long counter = 0;

	new_uid.ctr = ++counter;
	new_uid.pid = getpid();
	gettimeofday(&new_uid.time, NULL);

	return (new_uid);
}

/* Return an invalid uid for error handling */
uuid_t UUIDGetInvalidId(void)
{
	uuid_t uid;

	uid.ctr = 0;
	uid.pid = 0;
	uid.time.tv_sec = 0;
	uid.time.tv_usec = 0;

	return (uid);
}

/* Return 1 if uid1 equals uid2 */
int UUIDIsMatch(uuid_t uid1, uuid_t uid2)
{
	return (uid1.ctr == uid2.ctr &&
		 uid1.pid == uid2.pid &&
		 uid1.time.tv_sec == uid2.time.tv_sec &&
		 uid1.time.tv_usec == uid2.time.tv_usec);
}
