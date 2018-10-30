#ifndef FSM_H_
#define FSM_H_

typedef struct fsm_st fsm_t;

size_t FSMSuggestSize(size_t num_of_blocks, size_t block_size);

/*
 * memory recieved from user is assumed to be aligned
 * offset stored in last block is 0
 */
fsm_t *FSMInit(void *mem, size_t num_of_blocks, size_t block_size);

/*
 * returns an handle to the allocated region
 * remove the region from the end of the free list
 */
void *FSMAlloc(fsm_t *fsm);

/* To free a region, one would just link it to the free list. */
void FSMFree(void *block);

#endif /* FSM_H_ */
