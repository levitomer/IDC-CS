#ifndef SWAP_H_
#define SWAP_H_

/*swaps two integers*/
static void Swap(int *p1, int *p2);

static void SwapIntPtr(int **p1, int **p2);

static void SwapVoidPtr(void **p1, void **p2);

/*swap void pointers values*/
static void SwapVoidData(void *data1, void *data2, size_t mem_size);

#endif /* end of include guard: SWAP_H_ */
