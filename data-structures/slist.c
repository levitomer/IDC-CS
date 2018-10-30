#include <stdlib.h> /* malloc, free */
#include <assert.h>

#include "slist.h"

/*
return NULL upon failure.
*/
slist_node_t *SListCreateAndInitNode(void *data, slist_node_t *next)
{
	slist_node_t *node = NULL;

	node = (slist_node_t *)malloc(sizeof(slist_node_t));
	if(NULL == node)
	{
		return (NULL);
	}

	node->data = data;
	node->next = next;

	return (node);
}

/*
Returns the 'where' that holds the new data
*/
slist_node_t *SListInsert(slist_node_t *where, slist_node_t *new_node)
{
	void *temp = NULL;

	assert(where != NULL);
	assert(new_node != NULL);

	/* data exchange */
	temp = where->data;
	where->data = new_node->data;
	new_node->data = temp;
	/* setup next if given */
	SListInsertAfter(where, new_node);

	return (where);
}

slist_node_t *SListInsertAfter(slist_node_t *where, slist_node_t *new_node)
{
	assert(where != NULL);
	assert(new_node != NULL);

	new_node->next = where->next;
	where->next = new_node;

	return (new_node);
}

/* Removes a node, the data is swapped and returns the removed node. */
slist_node_t *SListRemove(slist_node_t *node)
{
	assert(node != NULL);

	node->data = node->next->data;

	return (SListRemoveAfter(node));
}

/*
cannot remove the the last node in the list
*/
slist_node_t *SListRemoveAfter(slist_node_t *node)
{
	slist_node_t *removed_node = NULL;

	assert(node != NULL);
	assert(NULL != node->next);


	/* save the node after */
	removed_node = node->next;
	/* set next to point on the node after the removed node */
	node->next = (removed_node)->next;

	return (removed_node);
}

/*
if head is empty, then return NULL
O(n)
*/
void SListFreeAll(slist_node_t *head)
{
	slist_node_t *curr_node = NULL;

	while (head != NULL)
	{
		curr_node = head->next; /* save the next node */
		free(head);
		head = curr_node; /* move to the next node */
	}

	return;
}

/*
O(n)
*/
size_t SListCount(const slist_node_t *head)
{
	size_t count = 0;
	const slist_node_t *curr_node = head;

	while (curr_node != NULL)
	{
		curr_node = curr_node->next;
		++count;
	}

	return (count);
}

/*
Returns the matched node, or NULL if couldn't find it
O(n)
*/
slist_node_t *SListFind(slist_node_t *head,
			   int (*is_match)(const void *node_data,
					     const void *data,
					     void *param),
			   const void *data,
			   void *param)
{
	assert(NULL != is_match);

	while(head && !is_match(head->data, data, param))
	{
		head = head->next;
	}

	return (head);
}

/*
O(n)
*/
int SListHasLoop(const slist_node_t *head)
{
	const slist_node_t *pre = head;
	const slist_node_t *post = head;

	while (post && post->next)
	{
			pre = pre->next;
			post = post->next->next;

			/* If pre and post meet at some point then there
				 is a loop */
			if (pre == post)
			{
					return (1);
			}
	}

	return (0);
}

/*
if the given head is NULL, return NULL
O(n)
*/
slist_node_t *SListFlip(slist_node_t *head)
{
	slist_node_t *new_head = NULL;
	slist_node_t *next = NULL;

	while (head != NULL)
	{
		next = head->next;
		head->next = new_head;
		new_head = head;
		head = next;
	}

  return (new_head);
}

/*
Returns the the value of the last call to func (if value is 1 then return)
O(n)
*/
int SListForEach(slist_node_t *head, int (*func)(void *node_data, void *param), void *param)
{
	int func_out = 0;

	assert(func != NULL);

	while(head && (0 == func_out))
	{
		func_out = func(head->data, param);
		head = head->next;
	}

	return (func_out);
}

/*
Find intersection of two lists, and returns a pointer to the intersection node (or NULL if intersection wasn’t found)
O(n^2)
*/
slist_node_t *SListFindIntersection(const slist_node_t *head1, const slist_node_t *head2)
{
	slist_node_t *head2_start = NULL;

	assert(head1 != NULL);
	assert(head2 != NULL);

	head2_start = (slist_node_t *)head2;

	while (head1 != NULL)
	{
		head2 = head2_start;
		while (head2 != NULL)
		{
			if(head1 == head2)
			{
				return ((slist_node_t *)head1);
			}

			head2 = head2->next;
		}

		head1 = head1->next;
	}

	return (NULL);
}
