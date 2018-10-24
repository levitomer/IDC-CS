#include <stdio.h>
#include <stdlib.h>

/* Link list node */
typedef struct node_st node_t;

struct node_st
{
	int data;
	node_t *next;
};
 
/* Function to get the counts of node in a linked list */
int GetCount(node_t *head);
 
/* function to get the intersection point of two linked
   lists head1 and head2 where head1 has d more nodes than
   head2 */
int GetIntesectionNode(int d, node_t *head1, node_t *head2);
 
/* function to get the intersection point of two linked
   lists head1 and head2 */
int GetIntesection(node_t *head1, node_t *head2)
{
	int c1 = GetCount(head1);
	int c2 = GetCount(head2);
	int d;

	if(c1 > c2)
	{
		d = c1 - c2;
		
		return GetIntesectionNode(d, head1, head2);
	}
	else
	{
		d = c2 - c1;
		
		return GetIntesectionNode(d, head2, head1);
	}
}
 
/* function to get the intersection point of two linked
   lists head1 and head2 where head1 has d more nodes than
   head2 */
int GetIntesectionNode(int d, node_t *head1, node_t *head2)
{
	int i;
	node_t *current1 = head1;
	node_t *current2 = head2;
	
	for(i = 0; i < d; i++)
	{
		if(current1 == NULL)
		{
			return (-1);
		}
		
		current1 = current1->next;
	}
	
	while(current1 !=  NULL && current2 != NULL)
	{
		if(current1 == current2)
		{
			return current1->data;
		}
		
		current1= current1->next;
		current2= current2->next;
	}
	
	return (-1);
}

/* Takes head pointer of the linked list and
   returns the count of nodes in the list */
int GetCount(node_t *head)
{
	node_t *current = head;
	int count = 0;
	
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	
	return (count);
}


/* IGNORE THE BELOW LINES OF CODE. THESE LINES
   ARE JUST TO QUICKLY TEST THE ABOVE FUNCTION */
int main()
{

	node_t *newNode = NULL;
	node_t* head1 = (node_t *)malloc(sizeof(node_t));
	head1->data  = 10;
	node_t *head2 = (node_t *)malloc(sizeof(node_t));
	head2->data  = 3;
	newNode = (node_t *) malloc(sizeof(node_t));
	newNode->data = 6;
	head2->next = newNode;
	
	newNode = (node_t *) malloc (sizeof(node_t));
	newNode->data = 9;
	head2->next->next = newNode;
	
	newNode = (node_t *) malloc (sizeof(node_t));
	newNode->data = 15;
	head1->next = newNode;
	head2->next->next->next  = newNode;
	
	newNode = (node_t *) malloc (sizeof(node_t));
	newNode->data = 30;
	head1->next->next= newNode;
	
	head1->next->next->next = NULL;
	
	printf("\n The node of intersection is %d \n",
	GetIntesection(head1, head2));
	
	getchar();
}

