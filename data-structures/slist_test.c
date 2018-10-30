#include <stdio.h>
#include <string.h>

#include "slist.h"

/*int print(void *data, void *param);*/
int compare(const void *data, const void *key, void *param);

static void PrintList(slist_node_t *head)
{
	while (head)
	{
		printf("%s->", (char *)head->data);
		head = head->next;
	}
	printf("NULL\n");
}

int main() {

	int errors = 0;

	char *data1 = "ASAF";
	char *data2 = "IMRY";
	char *data3 = "YASMIN";
	char *data4 = "TOMER";
	char *data5 = "AVIV";
	char *data6 = "URI";
	char *data7 = "TZVI";
	char *data8 = "ROY";
	char *data9 = "TAMIR";
	char *data10 = "AMIR";
/*	char *data11 = "NADAV";*/
	char *data12 = "ADI";
	char *data13 = "YARON";
/*	char *data14 = "ERAN";*/

/*	slist_node_t *intersection = NULL, *found_node;*/
/*	char *key = "U";*/

	/* HEAD2: nodes */
	slist_node_t *head2 = NULL;
	slist_node_t *node7 = SListCreateAndInitNode(data7, NULL);
	slist_node_t *node6 = SListCreateAndInitNode(data6, NULL);
	slist_node_t *node5 = SListCreateAndInitNode(data5, NULL);
	slist_node_t *node4 = SListCreateAndInitNode(data4, NULL);
	/* end of HEAD2 */

	/* HEAD1 node list */
	slist_node_t *node3 = SListCreateAndInitNode(data3, NULL);
	slist_node_t *node2 = SListCreateAndInitNode(data2, node3);
	slist_node_t *node1 = SListCreateAndInitNode(data1, node2);
	slist_node_t *head = node1;
	/* end of HEAD1 node list */

	/* HEAD3: nodes */
	slist_node_t *head3 = NULL;
	slist_node_t *new_head = NULL;
	slist_node_t *node13 = SListCreateAndInitNode(data13, NULL);
	slist_node_t *node12 = SListCreateAndInitNode(data12, NULL);
/*	slist_node_t *node11 = SListCreateAndInitNode(data11, NULL);*/
	slist_node_t *node10 = SListCreateAndInitNode(data10, NULL);
	slist_node_t *node9 = SListCreateAndInitNode(data9, NULL);
	slist_node_t *node8 = SListCreateAndInitNode(data8, NULL);
	/* end of HEAD3 */
	int (*funcPtr)(void *, void *);
/*	int (*cmpFuncPtr)(const void *, const void *, void *);*/

/*	funcPtr = &print;*/
/*	cmpFuncPtr = &compare;*/

	/* HEAD2: node list*/
	head2 = node4;
	node4->next = node5;
	node5->next = node6;
	node6->next = node7;
	node7->next = node4;
	SListInsertAfter(node7, node4);
	/* end of HEAD2 node list */

	/* HEAD3: node list */
	head3 = node8;
	node8->next = node9;
	node9->next = node10;
	node10->next = node2;
	node2->next = node12;
	node12->next = node13;
	node13->next = NULL;
	/* end of node list */

	/* tests a single node creation */
	errors += strcmp((char *)head->data, "ASAF") ? (printf("ERROR: SListCreateAndInitNode Failed, node missmatch\n"), PrintList(head), 1) : 0;
	/* tests a new node creation with reference to a next node */
	errors += strcmp((char *)node2->data, "IMRY") ? (printf("ERROR: SListCreateAndInitNode Failed, node missmatch\n"), PrintList(head), 1) : 0;
	/* Test Case #1: tests an insertion of a new node before where */
	errors += strcmp((char *)SListInsert(node2, node5)->data, "AVIV") ? (printf("ERROR: SListInsert Test Case #1 Failed, node missmatch\n"), PrintList(head), 1) : 0;
	/* Test Case #2: check the data correspondence */
	errors += strcmp((char *)node2->data, "AVIV") ? (printf("ERROR: SListInsert Test Case #2 Failed, node missmatch\n"), PrintList(head), 1) : 0;
	/* Test Case #3: check data correspondence */
	errors += strcmp((char *)node2->next->data, "IMRY") ? (printf("ERROR: SListInsert Test Case #3 Failed, node missmatch\n"), PrintList(head), 1) : 0;
	/* Test Case #1: insertion of a new node after where */
	errors += strcmp((char *)SListInsertAfter(node2, node6)->data, "URI") ? (printf("ERROR: SListInsertAfter failed, node missmatch\n"), PrintList(head), 1) : 0;
	/* Test Case #2: check post insertion */
	errors += strcmp((char *)node2->next->data, "URI") ? (printf("ERROR: SListInsertAfter Failed, node missmatch\n"), PrintList(head), 1) : 0;
	/* Test Case #1: check a node removal of a given node */
	errors += strcmp((char *)SListRemove(node2)->data, "URI") ? (printf("ERROR: SListRemove Failed, node missmatch\n"), PrintList(head), 1) : 0;
	/* Test Case #2: check the data correspondence SListRemove */
	errors += strcmp((char *)node2->data, "URI") ? (printf("ERROR: SListRemove Test Case #2 Failed, failed, node missmatch\n"), PrintList(head), 1) : 0;
	/* Test Case #1: SListRemoveAfter */
	errors += strcmp((char *)SListRemoveAfter(node2)->data, "URI") ? (printf("ERROR: SListRemoveAfter Test Case #1 Failed, node missmatch\n"), PrintList(head), 1) : 0;
	/* Test Case #2: SListRemoveAfter */
	errors += strcmp((char *)node2->data, "URI") ? (printf("ERROR: SListRemoveAfter Test Case #2 Failed, node missmatch\n"), PrintList(head), 1) : 0;
	/* node counter test */
	errors += !(SListCount(head) == 4) ? (printf("ERROR: SListCount failed, count isn't as expected\n"), PrintList(head), 1) : 0;
	/* SListHasLoop test */
	errors += !SListHasLoop(head2) ? (printf("ERROR: SListHasLoop Failed to detect a loop\n"), PrintList(head2), 1) : 0;
	/* SListFreeAll test */
	errors +=  (SListFreeAll(head), NULL == head->next) ? (printf("ERROR: SListFreeAll Failed\n"), PrintList(head), 1) : 0;
	/* SListFind test */
/*	SListFind(head2, compare, "tomer", NULL);*/
/*	errors += !strcmp(node4->data, "tomer") ? (printf("ERROR: SListFind Failed, hope you know what is wrong, cuz we ain't (0_o)\n"), 1) : 0;*/
	/* SListFlip test */
	new_head = SListFlip(head3);
	errors +=  (strcmp(new_head->next->data, "ADI")) ? (printf("ERROR: SListFlip Failed\n"), PrintList(new_head), 1) : 0;
	/* SListFind test  */
/*	errors +=  (NULL == (found_node = SListFind(head, cmpFuncPtr, key, NULL))) ? (printf("ERROR: SListFind Failed\n"), PrintList(head), PrintList(head3), 1) : 0;*/
	/* SListForEach test */
/*	errors += (SListForEach(head, funcPtr, NULL) != 0) ? (printf("ERROR: SListForEach Failed\n"), PrintList(head), PrintList(head3), 1) : 0;*/
	/* SListFindIntersection test */
/*	intersection = SListFindIntersection(head, head3);*/
/*	errors +=  (strcmp(intersection->data, "IMRY")) ? (printf("ERROR: SListFlip Failed\n"), PrintList(head), PrintList(head3), 1) : 0;*/

	if (errors)
	{
		printf("%d error(s) :(\n", errors);
		return errors;
	}

	printf("OK :D\n");
	return 0;
}

/*int compare(const void *data, const void *key, void *param)*/
/*{*/
/*	test_t *variant = (test_t *)data;*/
/*	char ch1 = *(char *)key;*/
/*	(void)param;*/

/*	return (variant->ch1 == ch1);*/
/*}*/
