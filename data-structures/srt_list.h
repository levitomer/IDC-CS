#ifndef SRT_LIST_H_
#define SRT_LIST_H_

#include <stddef.h> /*size_t*/

typedef struct srt_list_st srt_list_t;

typedef struct
{
    struct srt_list_info *info;
} srt_list_iter_t;


srt_list_t *SrtListCreate(int (*is_before)(const void *node_data, 
						 const void *data,
						 void *param),
			     void *param);

void SrtListDestroy(srt_list_t* srtlist);

size_t SrtListSize(const srt_list_t *srtlist);

int SrtListIsEmpty(const srt_list_t *srtlist);

/*returns iterator to inserted node, returns 'end' if function fails*/
/*data cannot be NULL*/
srt_list_iter_t SrtListInsert(srt_list_t *srtlist, void *data);

/*returns iterator to next node*/
srt_list_iter_t SrtListErase(srt_list_iter_t iter);

srt_list_iter_t SrtListBegin(const srt_list_t *srtlist);

srt_list_iter_t SrtListEnd(const srt_list_t *srtlist);

srt_list_iter_t SrtListNext(srt_list_iter_t iter);

srt_list_iter_t SrtListPrev(srt_list_iter_t iter);

void *SrtListGetData(srt_list_iter_t iter);

int SrtListIsSameIter(srt_list_iter_t iter_1, srt_list_iter_t iter_2);

/*
 * sends data from each node to func, along with param
 * stops if func fails (return != 0)
 * returns last returned value from function
 * 'to' is out of range
 */
int SrtListForEach(srt_list_iter_t from, 
		     srt_list_iter_t to,
		     int (*func)(void *node_data, void *param),
		     void *param);

/*returns srt_list_iter_t 'to' upon failure*/
/*'to' is out of range*/
srt_list_iter_t SrtListFind(srt_list_t *srtlist,
									   			  srt_list_iter_t from,
									   			  srt_list_iter_t to,
									   			  void *data);

/*returns srt_list_iter_t 'to' upon failure*/
/*'to' is out of range*/
srt_list_iter_t SrtListFindIf(srt_list_iter_t from,
											   			srt_list_iter_t to,
											   			int (*is_match)(
																		const void *node_data,
																		const void *data,
																		void *param),
															const void *data,
															void *param);

/*returns popped data*/
void *SrtListPopFront(srt_list_t *srtlist);

/*returns popped data*/
void *SrtListPopBack(srt_list_t *srtlist);

void SrtListMerge(srt_list_t *dest, srt_list_t *src);

#endif /*SRT_LIST_H_*/
