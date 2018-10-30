#include <stdio.h>
#include <string.h>

#include "slist.h"
#include "queue.h"

struct queue_st
{
    slist_node_t *head;  	 /* first node of the queue */
    slist_node_t *tail;   	 /* last node of the queue */
};

#define COUNT 14
static float errors = 0;
static float success = 0;

char *rd46[] = {"ASAF", "IMRY", "YASMIN", "TOMER", "AVIV", "URI", "TZVI", "ROY", "TAMIR", "AMIR", "NADAV", "ADI", "YARON", "ERAN"};

/* TESTS */
void TestQueueCreate(void);
void TestQueueSize(void);
void TestQueueIsEmpty(void);
void TestQueueDestroy(void);
void TestQueueEnqueue(void);
void TestQueueDequeue(void);
void TestQueueAppend();
void TestQueuePeek(void);
static void PrintQueue(queue_t *queue);

int main()
{
printf("Starting tests\n");

	/* Test QueueCreate */
	TestQueueCreate();

	/* Test QueueSize */
	TestQueueSize();

	/* QueueIsEmpty */
	TestQueueIsEmpty();

	/* QueueEnqueue */
	TestQueueEnqueue();

	/* QueueDequeue */
	TestQueueDequeue();

	/* QueuePeek */
	TestQueuePeek();

	/* QueueAppend */
	TestQueueAppend();

	/* QueueDestroy */
	TestQueueDestroy();

	printf("DONE\n");


	/* checksum of errors */
	if(errors)
	{
		printf("defect rate: %2f -> You got %f error(s) (0_o)\n", ((errors/success)*100), errors);
	}
	else
	{
		printf("defect rate: %2f -> You are OK :D\n", ((errors/success)*100));
	}

	return 0;
}

void TestQueueCreate()
{
	/* queue Create Test */
	queue_t *queue = NULL;
	queue = QueueCreate();

	errors += (NULL != queue) ? (++success, 0) : (printf("ERROR: QueueCreate failed\n"), 1);

	if (errors)
	{
		printf("TestQueueCreate has errors\n");
	}
	else
	{
		printf("TestQueueCreate OK\n");
	}

	return;
}

void TestQueueSize()
{
	queue_t *queue1 = NULL;
	queue_t *queue2 = NULL;
	queue1 = QueueCreate();
	queue2 = QueueCreate();

	/* 1. check size of an empty queue */
	errors += (0 == QueueSize(queue1)) ? (++success, 0) : (printf("size should be 0 %lu\n", QueueSize(queue1)), 1);

	QueueEnqueue(queue2, rd46[1]);
	/* 2. check size of filled queue */
	errors += (1 == QueueSize(queue2)) ? (++success, 0) : (printf("size should be %d instead of %lu\n", COUNT, QueueSize(queue2)), 1);

	if (errors)
	{
		printf("TestQueueSize has errors\n");
	}
	else
	{
		printf("TestQueueSize OK\n");
	}

	return;
}

void TestQueueIsEmpty()
{
	queue_t *queue1 = NULL;
	queue_t *queue2 = NULL;
	queue1 = QueueCreate();
	queue2 = QueueCreate();

	/* 1. check empty queue */
	errors += (1 == QueueIsEmpty(queue1)) ? (++success, 0) : (printf("size should be 1 but is %d\n", QueueIsEmpty(queue1)), 1);

	QueueEnqueue(queue2, rd46[2]);
	/* 2. check filled queue */
	errors += (0 == QueueIsEmpty(queue2)) ? (++success, 0) : (printf("isempty should be 0 instead of %d\n", QueueIsEmpty(queue2)), 1);

	if (errors)
	{
		printf("TestQueueIsEmpty has errors\n");
	}
	else
	{
		printf("TestQueueIsEmpty OK\n");
	}

	return;
}

void TestQueuePeek()
{
	/*	1. peek empy queue */
	queue_t *queue = NULL;
	queue = QueueCreate();
	errors += (NULL == QueuePeek(queue)) ? (++success, 0) : (printf("QueuePeek has a problem, should return NULL if queue is empty\n"), 1);

	/* 	2. peek filled queue */
	QueueEnqueue(queue, rd46[10]);
	errors += (!strcmp(QueuePeek(queue), "NADAV")) ? (++success, 0) : (printf("QueuePeek should show NADAV instead of %s\n", (char *)QueuePeek(queue)), 1);


	if (errors)
	{
		printf("TestQueuePeek has errors\n");
	}
	else
	{
		printf("TestQueuePeek OK\n");
	}

	return;
}

void TestQueueEnqueue()
{
	size_t i;
	queue_t *queue = NULL;
	queue = QueueCreate();

	/* 	1. enqueue an new queue */
	for (i = 0; i < 4; ++i)
	{
		errors += (0 == QueueEnqueue(queue, rd46[i])) ? (++success, 0) : (printf("ERROR: QueueEnqueue Failed\n"), 1);
	}

	PrintQueue(queue);

	errors += (!strcmp(QueuePeek(queue), "ASAF")) ? (++success, 0) : (printf("ERROR: QueueEnqueue Failed, should be ASAF instead of %s\n", (char *)QueuePeek(queue)), 1);

	/* 	2. enqueue a filled queue */
	for (i = 4; i < 8; ++i)
	{
		errors += (0 == QueueEnqueue(queue, rd46[i])) ? (++success, 0) : (printf("ERROR: QueueEnqueue Failed\n"), 1);
	}

	PrintQueue(queue);

	errors += (!strcmp(QueuePeek(queue), "ASAF")) ? (++success, 0) : (printf("ERROR: QueueEnqueue Failed, should be ASAF instead of %s\n", (char *)QueuePeek(queue)), 1);

	/* 	3. enqueue after dequeue */
	printf("dequeued: %s\n", (char *)QueueDequeue(queue));
	QueueEnqueue(queue, rd46[1]);

	errors += (!strcmp(QueuePeek(queue), "IMRY")) ? (++success, 0) : (printf("ERROR: QueueEnqueue Failed, should be TZVI instead of %s\n", (char *)QueuePeek(queue)), 1);

	PrintQueue(queue);

	if (errors)
	{
		printf("TestQueueEnqueue has errors\n");
	}
	else
	{
		printf("TestQueueEnqueue OK\n");
	}

	return;
}

void TestQueueDequeue()
{
	size_t i;
	queue_t *queue = NULL;
	queue = QueueCreate();

	/* 	1. dequeue a new queue */
	errors += (NULL == QueueDequeue(queue)) ? (++success, 0) : (printf("ERROR: QueueDequeue Failed, dequeuing an empty queue should return NULL\n"), 1);
	PrintQueue(queue);

	/* 	2. dequeue filled queue */
	for (i = 9; i < 14; ++i)
	{
		errors += (0 == QueueEnqueue(queue, rd46[i])) ? (++success, 0) : (printf("ERROR: QueueEnqueue Failed\n"), 1);
	}
	PrintQueue(queue);

	errors += (!strcmp(QueuePeek(queue), "AMIR")) ? (++success, 0) : (printf("ERROR: QueueDequeue Failed, AMIR should be dequeued instead of %s\n", (char *)QueueDequeue(queue)), 1);

	/* 3. dequeue untill underflow */
	for (i = 0; i < 14; ++i)
	{
		errors += printf("dequeued: %s\n", (char *)QueueDequeue(queue)) ? (++success, 0) : (printf("ERROR: QueueEnqueue Failed\n"), 1);
	}
	PrintQueue(queue);

	QueueEnqueue(queue, rd46[0]);
	PrintQueue(queue);

	errors += (!strcmp(QueuePeek(queue), "ASAF")) ? (++success, 0) : (printf("ERROR: QueueEnqueue Failed, should return ASAF instead of %s\n", (char *)QueuePeek(queue)), 1);

	if (errors)
	{
		printf("TestQueueDequeue has errors\n");
	}
	else
	{
		printf("TestQueueDequeue OK\n");
	}

	return;
}

void TestQueueAppend()
{
	size_t i;
	queue_t *queue1 = NULL;
	queue_t *queue2 = NULL;
	queue_t *queue3 = NULL;
	queue_t *queue4 = NULL;
	queue1 = QueueCreate();
	queue2 = QueueCreate();
	queue3 = QueueCreate();
	queue4 = QueueCreate();

	/* 	1. append filled queues */
	for (i = 0; i < 9; ++i)
	{
		errors += (0 == QueueEnqueue(queue1, rd46[i])) ? (++success, 0) : (printf("ERROR: QueueEnqueue Failed\n"), 1);
	}

	for (i = 9; i < 14; ++i)
	{
		errors += (0 == QueueEnqueue(queue2, rd46[i])) ? (++success, 0) : (printf("ERROR: QueueEnqueue Failed\n"), 1);
	}

	PrintQueue(queue1);
	PrintQueue(queue2);
	QueueAppend(queue1, queue2);
	PrintQueue(queue1);

	errors += (!QueueIsEmpty(queue1)) ? (++success, 0) : (printf("ERROR: QueueAppend Failed\n"), 1);
	errors += (COUNT == QueueSize(queue1)) ? (++success, 0) : (printf("ERROR: the size of the new queue isn't as expected, should be %d instead of %lu\n", COUNT, QueueSize(queue1)), 1);
	errors += (!strcmp(QueuePeek(queue1), "ASAF")) ? (++success, 0) : (printf("ERROR: QueueEnqueue Failed, should return ASAF instead of %s\n", (char *)QueuePeek(queue1)), 1);


	/* 	2. append filled to empty queues */
	for (i = 0; i < 9; ++i)
	{
		errors += (0 == QueueEnqueue(queue3, rd46[i])) ? (++success, 0) : (printf("ERROR: QueueEnqueue Failed\n"), 1);
	}

	PrintQueue(queue3);
	PrintQueue(queue4);
	QueueAppend(queue4, queue3);
	PrintQueue(queue4);

	errors += (!QueueIsEmpty(queue4)) ? (++success, 0) : (printf("ERROR: QueueAppend Failed, the size should be %d, instead of %lu\n", 9, QueueSize(queue4)), 1);
	errors += (!strcmp(QueuePeek(queue4), "ASAF")) ? (++success, 0) : (printf("ERROR: QueueAppend Failed, should return ASAF instead of %s\n", (char *)QueuePeek(queue4)), 1);

	if (errors)
	{
		printf("TestQueueAppend has errors\n");
	}
	else
	{
		printf("TestQueueAppend OK\n");
	}

	return;
}

void TestQueueDestroy()
{
	queue_t *queue1 = NULL;
	queue_t *queue2 = NULL;
	queue1 = QueueCreate();
	queue2 = QueueCreate();

	/* destroy a queue */
	QueueEnqueue(queue1, rd46[0]);
	QueueEnqueue(queue2, rd46[0]);
	
	if (errors)
	{
		printf("TestQueueDestroy has errors\n");
	}
	else
	{
		printf("TestQueueDestroy OK\n");
	}

	return;
}

static void PrintQueue(queue_t *queue)
{
	slist_node_t *curr_node = NULL;

	printf("HEAD ");
	curr_node = queue->head;
	while (curr_node)
	{
		printf("-> %s ", (char *)curr_node->data);
		curr_node = curr_node->next;
	}
	printf("\n");
}
