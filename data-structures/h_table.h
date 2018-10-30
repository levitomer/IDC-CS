#ifndef HTABLE_H_
#define HTABLE_H_

#include <stddef.h> /*size_t*/

typedef struct hash_table_st hash_table_t;


/*return pointer to the table or NULL upon failure*/
/*is_equal must return 1 if equal*/
hash_table_t *HTableCreate(int (*is_equal)(const void *node_data,
					   const void *data,
					   void *is_equal_param),
			   int (*hash_func) (const void *data, 
			   		     void *hash_param),
			   size_t table_size,
			   void *hash_param,
			   void *is_equal_param);

void HTableDestroy(hash_table_t *table);

/*remove node that contain the data*/
void HTableRemove(hash_table_t *table, const void *data);

/*return 0 for success, 1 upon failure*/
int HTableInsert(hash_table_t *table, const void *data);

/*return the number of nodes*/
size_t HTableSize(const hash_table_t *table);

/*return 1 if empty*/
int HTableIsEmpty(const hash_table_t *table);

/*return pointer to node data if found, NULL otherwise*/
void *HTableFind(const hash_table_t *table, const void *data);

/*returns the last call from the user function */
/*return value of func is 0 for success*/
int HTableForEach(hash_table_t *table, 
		  int (*func)(void *node_data,
			      void *param),
		  void *param);

#endif /*HTABLE_H_*/

