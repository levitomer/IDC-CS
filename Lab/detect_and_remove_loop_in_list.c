#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Link list node */
typedef struct node_st node_t;

struct node_st
{
	int data;
	node_t *next;
};

void RemoveLoop(node_t *loop_node, node_t *head);

/* This function detects and removes loop in the list
  1 is has loop, 0 otherwise*/
int DetectAndRemoveLoop(node_t *list)
{
	node_t *slow_p = list;
	node_t *fast_p = list;

	while (slow_p && fast_p && fast_p->next)
	{
		slow_p = slow_p->next;
		fast_p  = fast_p->next->next;

		/* If slow_p and fast_p meet at some point then there
		is a loop */
		if (slow_p == fast_p)
		{
			RemoveLoop(slow_p, list);

			/* Return 1 to indicate that loop is found */
			return (1);
		}
	}

	/* Return 0 to indeciate that there is no loop*/
	return (0);
}

/* Function to remove loop.
 loop_node --> Pointer to one of the loop nodes
 head -->  Pointer to the start node of the linked list */
void RemoveLoop(node_t *loop_node, node_t *head)
{
	node_t *ptr1 = NULL;
	node_t *ptr2 = NULL;

	assert(loop_node != NULL);
	assert(head != NULL);

	/* Set a pointer to the beging of the Linked List*/
	ptr1 = head;

	/*move it one by one to find the first node which is
	part of the Linked List */
	while (1)
	{
		/*start from loop_node*/
		ptr2 = loop_node;
		/*check if ptr1 is catched*/
		while ((ptr2->next != loop_node) && (ptr2->next != ptr1))
		{
			ptr2 = ptr2->next;
		}
		/*break the loop before the intersection*/
		if (ptr2->next == ptr1)
		{
			break;
		}

		/* If ptr2 did't reach ptr1 then try the next node after ptr1 */
		ptr1 = ptr1->next;
	}

	/* detach ptr2*/
	ptr2->next = NULL;
}

/* Function to print linked list */
void PrintList(node_t *node)
{
	while (node != NULL)
	{
		printf("%d  ", node->data);
		node = node->next;
	}

	puts("\n");
}

node_t *NewNode(int key)
{
	node_t *temp = (node_t *)malloc(sizeof(node_t));
	if (NULL == temp)
	{
		return (NULL);
	}
	temp->data = key;
	temp->next = NULL;

	return (temp);
}

/* Drier program to test above function*/
int main()
{
	node_t *head = NewNode(50);
	head->next = NewNode(20);
	head->next->next = NewNode(15);
	head->next->next->next = NewNode(4);
	head->next->next->next->next = NewNode(10);

	/* Create a loop for testing */
	head->next->next->next->next->next = head->next->next;

	DetectAndRemoveLoop(head);

	printf("Linked List after removing loop \n");
	PrintList(head);

	return (0);
}
