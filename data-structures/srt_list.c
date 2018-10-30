#include <stdlib.h> /* malloc, free */
#include <assert.h>

#include "dlist.h"
#include "srt_list.h"

struct srt_list_st
{
	dlist_t *dlist;
	int (*is_before)(const void *node_data,
			   const void *data,
			   void *param);
	void *param;
};

typedef struct
{
	int (*is_before)(const void *node_data,
			   const void *data,
			   void *param);
	void *param;
} param_t;

static int IsMatch(const void *node_data, 
		     const void *data,
		     void *param);

static int IsAfter(const void *node_data,
		     const void *data,
		     void *param);

srt_list_t *SrtListCreate(int (*is_before)(const void *node_data,
						 const void *data,
						 void *param),
						 void *param)
{
	srt_list_t *srtlist = NULL;

	assert(is_before != NULL);

	srtlist = (srt_list_t *)malloc(sizeof(srt_list_t));
	if (NULL == srtlist)
	{
		return (NULL);
	}

	srtlist->dlist = DlistCreate();
	if (NULL == srtlist->dlist)
	{
		free(srtlist);
		srtlist = NULL;
		return (NULL);
	}

	srtlist->is_before = is_before;
	srtlist->param = param;

	return (srtlist);
}

/* Complexity O(1) */
void SrtListDestroy(srt_list_t *srtlist)
{
	assert(srtlist != NULL);

	DlistDestroy(srtlist->dlist);

	free(srtlist);
	srtlist = NULL;

	return;
}

/* Complexity O(1) */
size_t SrtListSize(const srt_list_t *srtlist)
{
	assert(srtlist != NULL);

	return (DlistSize(srtlist->dlist));
}

/* Complexity O(1) */
int SrtListIsEmpty(const srt_list_t *srtlist)
{
	assert(srtlist != NULL);

	return (DlistIsEmpty(srtlist->dlist));
}
/* complexity O(n)
 * returns 'end' if function fails
 */
srt_list_iter_t SrtListInsert(srt_list_t *srtlist, void *data)
{

	dlist_iter_t where = NULL;
	srt_list_iter_t ret;
	param_t tools;

	assert(srtlist != NULL);
	assert(data != NULL);

	tools.is_before = srtlist->is_before;
	tools.param = srtlist->param;

	where = DlistFind(DlistBegin(srtlist->dlist),
					  DlistEnd(srtlist->dlist),
					  &IsAfter,
					  data,
					  &tools);
	/* insert the new data at where within the srtlist */
	ret.info = (struct srt_list_info *)DlistInsert(srtlist->dlist, where, data);

	return (ret);
}

/* Complexity O(1) */
srt_list_iter_t SrtListBegin(const srt_list_t *srtlist)
{
	srt_list_iter_t ret;

	assert(srtlist != NULL);

	ret.info = (struct srt_list_info *)DlistBegin(srtlist->dlist);

	return (ret);
}

/* Complexity O(1) */
srt_list_iter_t SrtListEnd(const srt_list_t *srtlist)
{
	srt_list_iter_t ret;

	assert(srtlist != NULL);

	ret.info = (struct srt_list_info *)DlistEnd(srtlist->dlist);

	return (ret);
}

/* Complexity O(1) */
srt_list_iter_t SrtListNext(srt_list_iter_t iter)
{
	srt_list_iter_t ret;

	assert(iter.info != NULL);

	ret.info = (struct srt_list_info *)DlistNext((dlist_iter_t)iter.info);

	return (ret);
}

/* Complexity O(1) */
srt_list_iter_t SrtListPrev(srt_list_iter_t iter)
{
	srt_list_iter_t ret;

	assert(iter.info != NULL);

	ret.info = (struct srt_list_info *)DlistPrev((dlist_iter_t)iter.info);

	return (ret);
}

/* Complexity O(1) */
void *SrtListGetData(srt_list_iter_t iter)
{
	assert(iter.info != NULL);

	return (DlistGetData((dlist_iter_t)iter.info));
}

/* complexity O(1)
 * returns iterator to next node
 */
srt_list_iter_t SrtListErase(srt_list_iter_t iter)
{
	srt_list_iter_t ret;

	assert(iter.info != NULL);

	ret.info = (struct srt_list_info *)DlistErase((dlist_iter_t)iter.info);

	return (ret);
}

/* complexity O(1)*/
int SrtListIsSameIter(srt_list_iter_t iter_1, srt_list_iter_t iter_2)
{
	assert(iter_1.info != NULL);
	assert(iter_2.info != NULL);

	return (iter_1.info == iter_2.info);
}

/* complexity O(1)*/
void *SrtListPopFront(srt_list_t *srtlist)
{
	assert(srtlist != NULL);
	assert(srtlist->dlist != NULL);

	return (DlistPopFront(srtlist->dlist));
}

/* complexity O(1)*/
void *SrtListPopBack(srt_list_t *srtlist)
{
	assert(srtlist != NULL);

	return (DlistPopBack(srtlist->dlist));
}

/* complexity O(n)
 * stops if func fails (return != 0)
 * returns last returned value from function
 * 'to' is out of range
 */
int SrtListForEach(srt_list_iter_t from,
				   srt_list_iter_t to,
				   int (*func)(void *node_data,
				   			   void *param),
	   			   void *param)
{
	assert(from.info != NULL);
	assert(to.info != NULL);
	assert(func != NULL);

	return (DlistForEach((dlist_iter_t)from.info,
						 (dlist_iter_t)to.info,
						 func,
						 param));
}


/* complexity O(n)
 * tools used to transfer is_before for for associativity comparison
 * 'to' is out of range
 */
srt_list_iter_t SrtListFind(srt_list_t *srtlist,
							srt_list_iter_t from,
							srt_list_iter_t to,
							void *data)
{
	srt_list_iter_t found;
	dlist_iter_t where = NULL;
	param_t tools;

	assert(srtlist != NULL);
	assert(from.info != NULL);
	assert(to.info != NULL);

	tools.is_before = srtlist->is_before;
	tools.param = srtlist->param;

	where = DlistFind((dlist_iter_t)from.info,
					  (dlist_iter_t)to.info,
					  &IsMatch,
					  data,
					  &tools);

	/* using associative comparison */
	if (!DlistIsSameIter(where, (dlist_iter_t)to.info) &&
	IsMatch(data, DlistGetData(where), &tools))
	{
		found.info = (struct srt_list_info *)where;

		return (found);
	}

	return (to);
}

/* complexity O(n)
 * 'to' is out of range
 */
srt_list_iter_t SrtListFindIf(srt_list_iter_t from,
							  srt_list_iter_t to,
  							  int (*is_match)(const void *node_data,
  							  				  const void *data,
  							  				  void *param),
			  				  const void *data,
			  				  void *param)
{
	srt_list_iter_t ret;

	assert(is_match != NULL);
	assert(data != NULL);

	ret.info = (struct srt_list_info *)DlistFind((dlist_iter_t)from.info,
												 (dlist_iter_t)to.info,
												 is_match,
												 data,
												 param);

	return (ret);
}

/* complexity O(n) */
void SrtListMerge(srt_list_t *dest, srt_list_t *src)
{
	dlist_iter_t where = NULL;
	dlist_iter_t end_dest = NULL;
	dlist_iter_t from = NULL;
	dlist_iter_t end_src = NULL;
	dlist_iter_t to = NULL;
	param_t tools;

	assert(dest != NULL);
	assert(src != NULL);

	tools.is_before = dest->is_before;
	tools.param = dest->param;

	from = DlistBegin(src->dlist);
	end_src = DlistEnd(src->dlist);
	where = DlistBegin(dest->dlist);
	end_dest = DlistEnd(dest->dlist);

	while (!SrtListIsEmpty(src))
	{
		where = DlistFind(where,
				    end_dest,
				    &IsAfter,
				    DlistGetData(from),
				    &tools);
		/* splice src to dest if dest is empty or where is end of dest */
		if (DlistIsSameIter(where, end_dest))
		{
			to = end_src;
		}
		else
		{
			to = DlistFind(from,
					 end_src,
					 &IsAfter,
					 DlistGetData(where),
					 &tools);
		}

		DlistSplice(where, from, to);

		from = to;
	}

	return;
}

static int IsMatch(const void *node_data, const void *data, void *param)
{
	return (!((param_t *)param)->is_before(node_data, data, ((param_t *)param)->param));
}

static int IsAfter(const void *node_data, const void *data, void *param)
{
	return (((param_t *)param)->is_before(data, node_data, ((param_t *)param)->param));
}
