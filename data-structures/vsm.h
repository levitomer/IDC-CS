#ifndef VSM_H_
#define VSM_H_

typedef struct vsm_st vsm_t;

vsm_t *VSMInit(void *memory, long total_size);
/*return pointer to the 'manager'*/


void *VSMAlloc(vsm_t *vsm, long required_size);
/*return pointer to the memory block or NULL if faile*/

void VSMFree(void *memory_to_free);


long VSMTotalFree(const vsm_t *vsm);


long VSMMaxFree(const vsm_t *vsm);

void VSMClear(vsm_t *vsm);

#endif /*VSM_H_*/
