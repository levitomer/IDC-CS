/*H_TABLE API IMPLEMENTATION*/

#include <stddef.h> /*offsetof*/
#include <assert.h>
#include <stdlib.h> /*malloc, free*/
#include <string.h> /*memset*/

#include "h_table.h"
#include "dlist.h"

struct hash_table_st
{
	int (*is_equal) (const void *table_data,
			 const void *data,
			 void *is_equal_param);
	int (*hash_func) (const void *data,
			  void *hash_param);
	void *is_equal_param;
	void *hash_param;
	size_t table_size;
	dlist_t *container[1];
};

/*init hash table with Dlists*/
static hash_table_t *HTableInit(hash_table_t *table);

/* return pointer to the table or NULL upon failure */
/* is_equal must return 1 if equal */
hash_table_t *HTableCreate(int (*is_equal)(const void *node_data,
					   const void *data,
					   void *is_equal_param),
			   int (*hash_func) (const void *data,
			   		     void *hash_param),
			   size_t table_size,
			   void *hash_param,
			   void *is_equal_param)
{
	hash_table_t *new_table = NULL;

	assert(is_equal != NULL);
	assert(hash_func != NULL);
	assert(table_size > 0);

	new_table = (hash_table_t *)malloc(sizeof(hash_table_t) +
					  (table_size * sizeof(dlist_t *)));
	if (NULL == new_table)
	{
		return (NULL);
	}

	new_table->is_equal = is_equal;
	new_table->is_equal_param = is_equal_param;
	new_table->hash_func = hash_func;
	new_table->hash_param = hash_param;
	new_table->table_size = table_size;

	return (HTableInit(new_table));
}

static hash_table_t *HTableInit(hash_table_t *new_table)
{
	size_t idx = 0, jdx = 0;
	
	assert(new_table != NULL);

	for (idx = 0; idx < new_table->table_size; ++idx)
	{
		new_table->container[idx] = DlistCreate();

		if(NULL == new_table->container[idx])
		{
			for(jdx = 0; jdx < idx; ++jdx)
			{
				DlistDestroy(new_table->container[jdx]);
			}
			
			memset(new_table, 0, sizeof(hash_table_t));
			
			free(new_table);
			
			return (NULL);
		}
		
	}

	return (new_table);
}

/*Time Complexity : O(n)*/
void HTableDestroy(hash_table_t *table)
{
	size_t idx = 0;

	assert(table != NULL);

	for (idx = 0; idx < table->table_size; ++idx)
	{
		DlistDestroy(*(table->container + idx));
	}

	memset(table, 0, sizeof(hash_table_t) + (table->table_size*sizeof(dlist_t *)));
	free(table);

	return;
}

/*Time Complexity : O(1)*/
int HTableInsert(hash_table_t *table, const void *data)
{
	size_t idx = 0;
	dlist_iter_t insert = NULL;
	
	assert(data != NULL);
	assert(table != NULL);

	/*Compute the index using the hash function*/
	idx = table->hash_func(data, table->hash_param);
	
	insert = DlistPushFront(table->container[idx], (void *)data);

	return (DlistIsSameIter(insert, DlistEnd(table->container[idx])));
}

/*return pointer to node data if found, NULL otherwise*/
void *HTableFind(const hash_table_t *table, const void *data)
{
	/*get the hash*/
	size_t hash_idx = 0;
	dlist_t *dlist = NULL;
	dlist_iter_t ret = NULL;
	
	assert(table != NULL);
	assert(data != NULL);
	
	hash_idx = table->hash_func(data, table->hash_param);
	
	/*locate the dlist from the hash container*/
	dlist = *(table->container + hash_idx);
	 
	ret = (DlistGetData(DlistFind(DlistBegin(dlist),
				  DlistEnd(dlist),
				  table->is_equal,
				  data,
				  table->is_equal_param)));
	
	return (ret);
}

void HTableRemove(hash_table_t *table, const void *data)
{
	size_t hash_idx = 0;
	dlist_t *dlist = NULL;
	
	assert(table != NULL);
	assert(data != NULL);
	
	/*get the hash*/
	hash_idx = table->hash_func(data, table->hash_param);
	
	/*locate the dlist from the hash container*/
	dlist = table->container[hash_idx];

	DlistErase(DlistFind(DlistBegin(dlist),
			   DlistEnd(dlist),
			   table->is_equal,
			   data,
			   table->is_equal_param));
	
	return;
}

/*Time Complexity : O(n*m)*/
int HTableForEach(hash_table_t *table, 
                  int (*func)
                      (void *node_data,
                      void *param),
                  void *param)
{
	dlist_t *dlist = NULL;
	size_t i = 0;
	int status = 0; 
	
	assert(table != NULL);
	assert(func != NULL);
	
	for (i = 0; (i < table->table_size) && (0 == status); ++i)
	{
		dlist = table->container[i];
		status = DlistForEach(DlistBegin(dlist),
				   DlistEnd(dlist),
				   func,
				   param);
	}
	
	return (status);	
}

/*Time Complexity : O(n*m)*/
size_t HTableSize(const hash_table_t *table)
{
	size_t idx = 0;
	size_t size = 0;
	
	assert(table != NULL);
	
	for (idx = 0; idx < table->table_size; ++idx)
	{
		if(!DlistIsEmpty(table->container[idx]))
		{
			size += DlistSize(table->container[idx]);
		}
	}
	
	return (size);
}

/*Time Complexity : O(n)*/
int HTableIsEmpty(const hash_table_t *table)
{
	size_t i = 0, is_empty = 1;
	
	assert(table);
	
	for (i = 0; i < table->table_size && is_empty == 1; ++i)
	{
		is_empty = DlistIsEmpty(table->container[i]); 
	}
	
	return (is_empty);
}
