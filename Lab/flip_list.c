/*Iterative and Recursive C program to flip a linked list*/
#include <stdio.h>
#include <stdlib.h>

/* Link list node */
typedef struct node_st node_t;

struct node_st
{
	int data;
	node_t *next;
};

/* Function to reverse the linked list */
node_t* IterFlip(node_t *head)
{
	node_t *current = head;
	node_t *new_head = NULL;
	node_t *next = NULL;

	while (current != NULL)
	{
		/*Store next*/
		next = current->next;
		/*Reverse current node's pointer*/
		current->next = new_head;
		/*Move pointers one position ahead.*/
		new_head = current;
		/*go to the next node*/
		current = next;
	}

	/* Previous pointer is new head*/
	/*of linked list.*/
	return (new_head);
}


void RecFlip(node_t **head_ref)
{
	node_t *first;
	node_t *other;

	/* empty list */
	if (*head_ref == NULL)
	{
		return;
	}

	first = *head_ref;
	other = first->next;

	/* Termintate when first is the last node */
	if (other == NULL)
	{
		return;
	}

	/* reverse the rest list and put the first element at the end */
	RecFlip(&other);
	/*swip the node after other to be first*/
	first->next->next = first;
	/* release the node */
	first->next  = NULL;
	/* fix the head pointer */
	*head_ref = other;

	return;
}


/* Function to print linked list */
void printList(node_t *head)
{
	node_t *temp = head;

	while (temp != NULL)
	{
		printf("%d ", temp->data);
		puts("\n");
		temp = temp->next;
	}
}

node_t *new_node(int data)
{
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	if (NULL == new_node)
	{
		return (NULL);
	}

	new_node->data = data;

	return (new_node);
}

/*Test*/
int main()
{
	/* Start with the empty list */
	node_t *head = new_node(85);
	head->next = new_node(15);
	head->next->next = new_node(4);
	head->next->next->next = new_node(20);

	printf("Given linked list\n");
	printList(head);
	head = IterFlip(head);
/*	recFlip(&head);*/

	printf("\nReversed Linked list \n");
	printList(head);


	return (0);
}
