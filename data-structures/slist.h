#ifndef SLIST_H_
#define SLIST_H_

#include <stddef.h>

typedef struct slist_node_st slist_node_t;

struct slist_node_st
{
	slist_node_t *next;
	void *data;
};

/* Create and initialize a new node, return NULL upon failure. */
slist_node_t *SListCreateAndInitNode(void *data, slist_node_t *next);

/* Preappends a node before 'where', returns the 'where' that holds the new data */
slist_node_t *SListInsert(slist_node_t *where, slist_node_t *new_node);

/* Inserts a 'new_node' after 'where', and returns the 'new_node' */
slist_node_t *SListInsertAfter(slist_node_t *where, slist_node_t *new_node);

/* Removes a node, and returns the removed node.*/
slist_node_t *SListRemove(slist_node_t *node);

/* Detach a node from the list, cannot remove the the last node in the list. Return the removed node. */
slist_node_t *SListRemoveAfter(slist_node_t *node);

/* Free memory of all nodes starting from head */
void SListFreeAll(slist_node_t *head);

/* Return the numbers of nodes starting from the head */
size_t SListCount(const slist_node_t *head);

/* Finds a node within a given linked list, that matches the given data.
Returns the matched node */
slist_node_t *SListFind(slist_node_t *head,
						int (*is_match)(const void *node_data,
										const void *data,
										void *param),
						const void *data,
						void *param);

/* returns 1 if the linked list has loop, or 0 otherwise */
int SListHasLoop(const slist_node_t *head);

/* Flips the order of nodes, and returns the new head */
slist_node_t *SListFlip(slist_node_t *head);

/* Send the data from each node to func, along with param. Stops in case func fails, and Returns the the value of the last call to func. */
int SListForEach(slist_node_t *head,
				 int (*func)(void *node_data,
				 			 void *param),
				 void *param);

/* Find intersection of two lists, and returns a pointer to the intersection node (or NULL if no intersection weren’t found) */
slist_node_t *SListFindIntersection(const slist_node_t *head1, const slist_node_t *head2);

#endif /* SLIST_H_ */
