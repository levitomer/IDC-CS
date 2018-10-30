#ifndef UUID_H_
#define UUID_H_

#include <sys/types.h> /* pid_t   */
#include <sys/time.h>  /* timeval */

typedef struct uuid_st
{
	unsigned long ctr;
	pid_t pid;
	struct timeval time;
}uuid_t;

uuid_t UUIDCreate(void);

/* Return an invalid uid for error handling */
uuid_t UUIDGetInvalidId(void);

/* Return 1 if uid1 equals uid2 */
int UUIDIsMatch(uuid_t uid1, uuid_t uid2);

#endif /* UUID_H_ */

