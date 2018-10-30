#include <stdio.h>
#include <string.h>

#include "dlist.h"
#include "srt_list.h"

static float errors = 0;
static int success = 0;

typedef int(*is_before)(const void *, const void *, void *);
typedef int(*is_match)(const void *, const void *, void *);
typedef int(*func)(void *, void *);

int IsBefore(const void *node_data, const void *data, void *param);
int IsMatch(const void *node_data, const void *data, void *param);
int Null(void *node_data, void *param);
int IsMentor(const void *node_data,
										const void *data,
										void *param);

char *rd46[] = {"ASAF", "IMRY", "YASMIN", "TOMER", "AVIV", "URI", "TZVI", "ROY", "TAMIR", "AMIR", "NADAV", "ADI", "YARON", "ERAN", "IRIS"};

/* TESTS */
void TestSrtListCreate(void); /*DONE*/
void TestSrtListSize(void); /*DONE*/
void TestSrtListInsert(void); /*DONE*/
void TestSrtListErase(void); /*DONE*/
void TestSrtListIsEmpty(void); /*DONE*/
void TestSrtListIsSameIter(void); /*DONE*/
void TestSrtListGetData(void); /*DONE*/
void TestSrtListBegin(void); /*DONE*/
void TestSrtListEnd(void); /*DONE*/
void TestSrtListNext(void); /*DONE*/
void TestSrtListPrev(void); /*DONE*/
void TestSrtListPopFront(void); /*DONE*/
void TestSrtListPopBack(void); /*DONE*/
void TestSrtListForEach(void); /*DONE*/
void TestSrtListFind(void); /*DONE*/
void TestSrtListFindIf(void); /*DONE*/
void TestSrtListMerge(void);

static void PrintSrtList(srt_list_t *srtlist);

int main()
{
	printf("STARTING TESTS\n");

	TestSrtListCreate();
	TestSrtListSize();
	TestSrtListInsert();
	TestSrtListErase();
	TestSrtListIsEmpty();
	TestSrtListIsSameIter();
	TestSrtListGetData();
	TestSrtListBegin();
	TestSrtListEnd();
	TestSrtListNext();
	TestSrtListPrev();
	TestSrtListPopFront();
	TestSrtListPopBack();
	TestSrtListForEach();
	TestSrtListFind();
	TestSrtListFindIf();
	TestSrtListMerge();

	printf("DONE\n");

	/* checksum of errors */
	if(errors)
	{
		printf("defect rate: %f -> You got %f error(s) (0_o)\n", ((errors/success)*100), errors);
	}
	else
	{
		printf("defect rate: %f -> You are OK :D\n", ((errors/success)*100));
	}

	return 0;
}

void TestSrtListCreate(void)
{
	srt_list_t *srtlist = NULL;
	is_before isbefore = IsBefore;

	srtlist = SrtListCreate(isbefore, 0);

	errors += (NULL != srtlist) ? (++success, 0) : (printf("ERROR: SrtListCreate failed\n"), 1);

	SrtListDestroy(srtlist);
	srtlist = NULL;

	if (errors)
	{
		printf("TestSrtListCreate has errors\n");
	}
	else
	{
		printf("TestSrtListCreate OK\n");
	}

	return;
}

void TestSrtListSize(void)
{
	srt_list_t *srtlist = NULL;
	is_before isbefore = IsBefore;

	srtlist = SrtListCreate(isbefore, 0);

	PrintSrtList(srtlist);
	SrtListInsert(srtlist, rd46[0]);
	SrtListInsert(srtlist, rd46[1]);
	SrtListInsert(srtlist, rd46[2]);
	PrintSrtList(srtlist);

	errors += (NULL != srtlist) ? (++success, 0) : (printf("ERROR: SrtListCreate failed\n"), 1);
	errors += (3 == SrtListSize(srtlist)) ? (++success, 0) : (printf("ERROR: SrtListSize failed, size should be %lu\n", SrtListSize(srtlist)), 1);
	errors += (0 == SrtListIsEmpty(srtlist)) ? (++success, 0) : (printf("ERROR: DlistIsEmpty failed, should be %d\n", SrtListIsEmpty(srtlist)), 1);

	SrtListDestroy(srtlist);
	srtlist = NULL;

	if (errors)
	{
		printf("TestSrtListSize has errors\n");
	}
	else
	{
		printf("TestSrtListSize OK\n");
	}

	return;
}

void TestSrtListInsert(void)
{
	srt_list_t *srtlist = NULL;
	is_before isbefore = IsBefore;

	srtlist = SrtListCreate(isbefore, 0);
	PrintSrtList(srtlist);

	SrtListInsert(srtlist, rd46[0]);
	SrtListInsert(srtlist, rd46[1]);
	SrtListInsert(srtlist, rd46[3]);
	PrintSrtList(srtlist);
	errors += (NULL != srtlist) ? (++success, 0) : (printf("ERROR: SrtListCreate failed\n"), 1);
	errors += (3 == SrtListSize(srtlist)) ? (++success, 0) : (printf("ERROR: SrtListSize failed, size should be 0\n"), 1);
	errors += (0 == SrtListIsEmpty(srtlist)) ? (++success, 0) : (printf("ERROR: DlistIsEmpty failed, should be 0\n"), 1);
	errors += (0 == strcmp((char *)SrtListGetData(SrtListBegin(srtlist)), "IMRY")) ? (++success, 0) : (printf("ERROR: SrtListInsert Failed. The data shouldn't be NULL.\n"));

	SrtListInsert(srtlist, rd46[11]);
	PrintSrtList(srtlist);
	errors += (4 == SrtListSize(srtlist)) ? (++success, 0) : (printf("ERROR: SrtListSize failed, size should be 0\n"), 1);
	errors += (0 == SrtListIsEmpty(srtlist)) ? (++success, 0) : (printf("ERROR: DlistIsEmpty failed, should be 0\n"), 1);
	errors += (0 == strcmp((char *)SrtListGetData(SrtListBegin(srtlist)), "ADI")) ? (++success, 0) : (printf("ERROR: SrtListInsert Failed. The data isn't sorted shouldn't be ADI at the head.\n"));

	SrtListInsert(srtlist, rd46[2]);
	PrintSrtList(srtlist);
	errors += (NULL != srtlist) ? (++success, 0) : (printf("ERROR: SrtListCreate failed\n"), 1);
	errors += (5 == SrtListSize(srtlist)) ? (++success, 0) : (printf("ERROR: SrtListSize failed, size should be 0\n"), 1);
	errors += (0 == SrtListIsEmpty(srtlist)) ? (++success, 0) : (printf("ERROR: DlistIsEmpty failed, should be 0\n"), 1);
	errors += (0 == strcmp((char *)SrtListPopBack(srtlist), "YASMIN")) ? (++success, 0) : (printf("ERROR: SrtListPopBack Failed. The data should be YASMIN.\n"));

	SrtListDestroy(srtlist);
	srtlist = NULL;

	if (errors)
	{
		printf("TestSrtListInsert has errors\n");
	}
	else
	{
		printf("TestSrtListInsert OK\n");
	}

	return;
}

void TestSrtListErase(void)
{
	srt_list_t *srtlist = NULL;
	is_before isbefore = IsBefore;
	srt_list_iter_t iter;
	srtlist = SrtListCreate(isbefore, 0);

	SrtListInsert(srtlist, rd46[0]);
	SrtListInsert(srtlist, rd46[1]);
	SrtListInsert(srtlist, rd46[2]);

	iter = SrtListBegin(srtlist);
	SrtListErase(iter);
	PrintSrtList(srtlist);

	errors += (NULL != srtlist) ? (++success, 0) : (printf("ERROR: SrtListCreate failed\n"), 1);
	errors += (0 == SrtListIsEmpty(srtlist)) ? (++success, 0) : (printf("ERROR: DlistIsEmpty failed, should be 0\n"), 1);
	errors += (2 == SrtListSize(srtlist)) ? (++success, 0) : (printf("ERROR: DlistSize failed, size should be 0\n"), 1);

	SrtListDestroy(srtlist);
	srtlist = NULL;

	if (errors)
	{
		printf("TestSrtListErase has errors\n");
	}
	else
	{
		printf("TestSrtListErase OK\n");
	}

	return;
}

void TestSrtListIsEmpty(void)
{
	srt_list_t *srtlist = NULL;
	is_before isbefore = IsBefore;

	srtlist = SrtListCreate(isbefore, 0);

	PrintSrtList(srtlist);

	errors += (NULL != srtlist) ? (++success, 0) : (printf("ERROR: SrtListCreate failed\n"), 1);
	errors += (1 == SrtListIsEmpty(srtlist)) ? (++success, 0) : (printf("ERROR: DlistIsEmpty failed, should be 0\n"), 1);
	errors += (0 == SrtListSize(srtlist)) ? (++success, 0) : (printf("ERROR: SrtListSize failed, size should be 0\n"), 1);

	SrtListDestroy(srtlist);
	srtlist = NULL;

	if (errors)
	{
		printf("TestSrtListIsEmpty has errors\n");
	}
	else
	{
		printf("TestSrtListIsEmpty OK\n");
	}

	return;
}

void TestSrtListIsSameIter(void)
{
	srt_list_t *srtlist = NULL;
	srt_list_iter_t from;
	srt_list_iter_t to;
	is_before isbefore = IsBefore;
	srtlist = SrtListCreate(isbefore, 0);

	SrtListInsert(srtlist, rd46[0]);
	SrtListInsert(srtlist, rd46[1]);
	SrtListInsert(srtlist, rd46[2]);
	PrintSrtList(srtlist);

	from = SrtListBegin(srtlist);
	to = SrtListEnd(srtlist);
	errors += (NULL != srtlist) ? (++success, 0) : (printf("ERROR: SrtListCreate failed\n"), 1);
	errors += (0 == SrtListIsEmpty(srtlist)) ? (++success, 0) : (printf("ERROR: DlistIsEmpty failed, should be 0\n"), 1);
	errors += (!SrtListIsSameIter(from, to)) ? (++success, 0) : (printf("ERROR: SrtListIsSameIter failed, iters are not the same\n"), 1);
	to = SrtListBegin(srtlist);
	errors += (SrtListIsSameIter(from, to)) ? (++success, 0) : (printf("ERROR: SrtListIsSameIter failed, same iters\n"), 1);

	SrtListDestroy(srtlist);
	srtlist = NULL;

	if (errors)
	{
		printf("TestDlistIsSameIter has errors\n");
	}
	else
	{
		printf("TestDlistIsSameIter OK\n");
	}

	return;
}

void TestSrtListGetData(void)
{
	srt_list_t *srtlist = NULL;
	is_before isbefore = IsBefore;
	srtlist = SrtListCreate(isbefore, 0);


	SrtListInsert(srtlist, rd46[0]);
	SrtListInsert(srtlist, rd46[1]);
	SrtListInsert(srtlist, rd46[2]);
	PrintSrtList(srtlist);

	errors += (NULL != srtlist) ? (++success, 0) : (printf("ERROR: SrtListCreate failed\n"), 1);
	errors += (0 == SrtListIsEmpty(srtlist)) ? (++success, 0) : (printf("ERROR: DlistIsEmpty failed, should be 0\n"), 1);
	errors += (3 == SrtListSize(srtlist)) ? (++success, 0) : (printf("ERROR: DlistSize failed, size should be 0\n"), 1);
	errors += (0 == strcmp((char *)SrtListGetData(SrtListBegin(srtlist)), "IMRY")) ? (++success, 0) : (printf("ERROR: TestSrtListGetData Failed. The data shouldn't be NULL.\n"));

	SrtListDestroy(srtlist);
	srtlist = NULL;

	if (errors)
	{
		printf("TestSrtListGetData has errors\n");
	}
	else
	{
		printf("TestSrtListGetData OK\n");
	}

	return;
}

void TestSrtListBegin(void)
{
	srt_list_t *srtlist = NULL;
	is_before isbefore = IsBefore;
	srtlist = SrtListCreate(isbefore, 0);


	SrtListInsert(srtlist, rd46[0]);
	SrtListInsert(srtlist, rd46[1]);
	PrintSrtList(srtlist);

	errors += (0 == strcmp((char *)SrtListGetData(SrtListBegin(srtlist)), "IMRY")) ? (++success, 0) : (printf("ERROR: SrtListBegin Failed. data missmatch.\n"));

	SrtListDestroy(srtlist);
	srtlist = NULL;

	if (errors)
	{
		printf("TestSrtListBegin has errors\n");
	}
	else
	{
		printf("TestSrtListBegin OK\n");
	}

	return;
}

void TestSrtListEnd(void)
{
	srt_list_t *srtlist = NULL;
	is_before isbefore = IsBefore;
	srtlist = SrtListCreate(isbefore, 0);


	SrtListInsert(srtlist, rd46[0]);
	SrtListInsert(srtlist, rd46[1]);
	SrtListInsert(srtlist, rd46[2]);
	PrintSrtList(srtlist);

	errors += (strcmp((char  *)SrtListGetData(SrtListPrev(SrtListEnd(srtlist))), "YASMIN")) ? (printf("ERROR: SrtListEnd Failed. data missmatch.\n")) : (++success, 0);

	SrtListDestroy(srtlist);
	srtlist = NULL;

	if (errors)
	{
		printf("TestSrtListEnd has errors\n");
	}
	else
	{
		printf("TestSrtListEnd OK\n");
	}

	return;
}

void TestSrtListNext(void)
{
	srt_list_t *srtlist = NULL;
	is_before isbefore = IsBefore;
	srt_list_iter_t iter;
	srtlist = SrtListCreate(isbefore, 0);

	SrtListInsert(srtlist, rd46[0]);
	SrtListInsert(srtlist, rd46[0]);
	SrtListInsert(srtlist, rd46[2]);
	PrintSrtList(srtlist);

	errors += (NULL != srtlist) ? (++success, 0) : (printf("ERROR: SrtListCreate failed\n"), 1);

	iter = SrtListBegin(srtlist);

	errors += (strcmp((char *)SrtListGetData(iter), (char *)SrtListGetData(SrtListNext(iter)))) ? (printf("ERROR: SrtListNext Failed. The data shouldn't be NULL.\n")) : (++success, 0);

	SrtListDestroy(srtlist);
	srtlist = NULL;

	if (errors)
	{
		printf("TestSrtListNext has errors\n");
	}
	else
	{
		printf("TestSrtListNext OK\n");
	}

	return;
}

void TestSrtListPrev(void)
{
	srt_list_t *srtlist = NULL;
	is_before isbefore = IsBefore;
	srt_list_iter_t begin;
	srt_list_iter_t end;

	srtlist = SrtListCreate(isbefore, 0);

	SrtListInsert(srtlist, rd46[0]);
	SrtListInsert(srtlist, rd46[1]);
	SrtListInsert(srtlist, rd46[2]);
	PrintSrtList(srtlist);


	errors += (NULL != srtlist) ? (++success, 0) : (printf("ERROR: SrtListCreate failed\n"), 1);

	begin = SrtListBegin(srtlist);
	end = SrtListEnd(srtlist);

	errors += (strcmp((char *)SrtListGetData(SrtListNext(begin)), (char *)SrtListGetData(SrtListPrev(end)))) ? (++success, 0) : (printf("ERROR: SrtListPrev Failed.\n"));

	SrtListDestroy(srtlist);
	srtlist = NULL;

	if (errors)
	{
		printf("TestSrtListPrev has errors\n");
	}
	else
	{
		printf("TestSrtListPrev OK\n");
	}

	return;
}

void TestSrtListPopFront(void)
{
	srt_list_t *srtlist = NULL;
	is_before isbefore = IsBefore;
	srt_list_iter_t begin;

	srtlist = SrtListCreate(isbefore, 0);

	SrtListInsert(srtlist, rd46[0]);
	SrtListInsert(srtlist, rd46[1]);
	SrtListInsert(srtlist, rd46[2]);
	PrintSrtList(srtlist);

	SrtListPopFront(srtlist);
	PrintSrtList(srtlist);


	errors += (NULL != srtlist) ? (++success, 0) : (printf("ERROR: SrtListCreate failed\n"), 1);

	begin = SrtListBegin(srtlist);

	errors += (strcmp((char *)SrtListGetData(begin), "ASAF")) ? (printf("ERROR: SrtListPopFront Failed.\n")) : (++success, 0);

	SrtListDestroy(srtlist);
	srtlist = NULL;

	if (errors)
	{
		printf("TestSrtListPopFront has errors\n");
	}
	else
	{
		printf("TestSrtListPopFront OK\n");
	}

	return;
}

void TestSrtListPopBack(void)
{
	srt_list_t *srtlist = NULL;
	is_before isbefore = IsBefore;
	srt_list_iter_t begin;

	srtlist = SrtListCreate(isbefore, 0);

	SrtListInsert(srtlist, rd46[0]);
	SrtListInsert(srtlist, rd46[1]);
	SrtListInsert(srtlist, rd46[2]);
	PrintSrtList(srtlist);

	SrtListPopBack(srtlist);
	PrintSrtList(srtlist);

	errors += (NULL != srtlist) ? (++success, 0) : (printf("ERROR: SrtListCreate failed\n"), 1);

	begin = SrtListBegin(srtlist);

	errors += (strcmp((char *)SrtListGetData(SrtListNext(begin)), "ASAF")) ? (printf("ERROR: SrtListPopBack Failed.\n")) : (++success, 0);

	SrtListDestroy(srtlist);
	srtlist = NULL;

	if (errors)
	{
		printf("TestSrtListPopBack has errors\n");
	}
	else
	{
		printf("TestSrtListPopBack OK\n");
	}

	return;
}

void TestSrtListForEach(void)
{
	srt_list_t *srtlist = NULL;
	func str_null = Null;
	is_before isbefore = IsBefore;
	srtlist = SrtListCreate(isbefore, 0);

	SrtListInsert(srtlist, rd46[0]);
	SrtListInsert(srtlist, rd46[1]);
	SrtListInsert(srtlist, rd46[2]);
	PrintSrtList(srtlist);

	errors += (NULL != srtlist) ? (++success, 0) : (printf("ERROR: SrtListCreate failed\n"), 1);
	errors += (0 == SrtListIsEmpty(srtlist)) ? (++success, 0) : (printf("ERROR: DlistIsEmpty failed, should be 0\n"), 1);
	errors += (3 == SrtListSize(srtlist)) ? (++success, 0) : (printf("ERROR: DlistSize failed, size should be 0\n"), 1);
	errors += (0 == SrtListForEach(SrtListBegin(srtlist), SrtListEnd(srtlist), str_null, 0)) ? (++success, 0) : (printf("ERROR: DlistForEach Failed. The data shouldn't be NULL.\n"));

	SrtListDestroy(srtlist);
	srtlist = NULL;

	if (errors)
	{
		printf("TestSrtListForEach has errors\n");
	}
	else
	{
		printf("TestSrtListForEach OK\n");
	}

	return;
}

void TestSrtListFind(void)
{
	srt_list_t *srtlist = NULL;
	is_before isbefore = IsBefore;
	srt_list_iter_t begin;
	srt_list_iter_t end;
	srt_list_iter_t found;

	srtlist = SrtListCreate(isbefore, 0);

	PrintSrtList(srtlist);
	SrtListInsert(srtlist, rd46[0]);
	SrtListInsert(srtlist, rd46[1]);
	SrtListInsert(srtlist, rd46[2]);
	PrintSrtList(srtlist);

	errors += (NULL != srtlist) ? (++success, 0) : (printf("ERROR: SrtListCreate failed\n"), 1);

	begin = SrtListBegin(srtlist);
	end = SrtListEnd(srtlist);
	found = SrtListFind(srtlist, begin, end, "ASAF");

	errors += (strcmp((char *)SrtListGetData(found), "IMRY")) ? (printf("ERROR: SrtListFind Failed. the data found is %s", (char *)SrtListGetData(found))) : (++success, 0);

	SrtListDestroy(srtlist);
	srtlist = NULL;

	if (errors)
	{
		printf("TestSrtListFind has errors\n");
	}
	else
	{
		printf("TestSrtListFind OK\n");
	}

	return;
}

void TestSrtListFindIf(void)
{
	srt_list_t *srtlist = NULL;
	is_before isbefore = IsBefore;
	srt_list_iter_t begin;
	srt_list_iter_t end;

	srtlist = SrtListCreate(isbefore, 0);

	SrtListInsert(srtlist, rd46[0]);
	SrtListInsert(srtlist, rd46[1]);
	SrtListInsert(srtlist, rd46[2]);
	SrtListInsert(srtlist, rd46[14]);
	PrintSrtList(srtlist);

	errors += (NULL != srtlist) ? (++success, 0) : (printf("ERROR: SrtListCreate failed\n"), 1);

	begin = SrtListBegin(srtlist);
	end = SrtListEnd(srtlist);

	errors += ((char *)SrtListFindIf(begin, end, &IsMentor, "IRIS", 0).info) ? (++success, 0) : (printf("ERROR: SrtListFindIf Failed.\n"));

	SrtListDestroy(srtlist);
	srtlist = NULL;

	if (errors)
	{
		printf("TestSrtListFindIf has errors\n");
	}
	else
	{
		printf("TestSrtListFindIf OK\n");
	}

	return;
}

void TestSrtListMerge(void)
{
	srt_list_t *srtlist1 = NULL;
	srt_list_t *srtlist2 = NULL;
	is_before isbefore = IsBefore;

	srtlist1 = SrtListCreate(isbefore, 0);
	srtlist2 = SrtListCreate(isbefore, 0);
	errors += (NULL != srtlist1) ? (++success, 0) : (printf("ERROR: SrtListCreate failed\n"), 1);
	errors += (NULL != srtlist2) ? (++success, 0) : (printf("ERROR: SrtListCreate failed\n"), 1);

	SrtListInsert(srtlist1, rd46[0]);
	SrtListInsert(srtlist1, rd46[1]);
	SrtListInsert(srtlist1, rd46[11]);
	PrintSrtList(srtlist1);

	SrtListInsert(srtlist2, rd46[3]);
	SrtListInsert(srtlist2, rd46[4]);
	SrtListInsert(srtlist2, rd46[5]);
	PrintSrtList(srtlist2);

	SrtListMerge(srtlist1, srtlist2);

	errors += (strcmp((char *)SrtListGetData(SrtListPrev(SrtListEnd(srtlist1))), "YASMIN")) ? (printf("ERROR: SrtListPrev Failed.\n")) : (++success, 0);

	SrtListDestroy(srtlist1);
	srtlist1 = NULL;
	SrtListDestroy(srtlist2);
	srtlist2 = NULL;

	if (errors)
	{
		printf("TestSrtListMerge has errors\n");
	}
	else
	{
		printf("TestSrtListMerge OK\n");
	}

	return;
}

static void PrintSrtList(srt_list_t *srtlist)
{
	srt_list_iter_t begin = SrtListBegin(srtlist);
	srt_list_iter_t end = SrtListEnd(srtlist);

	printf("<-(null)");
	while (!SrtListIsSameIter(begin, end))
	{
		printf("<->[%s]", (char *)SrtListGetData(begin));
		begin = SrtListNext(begin);
	}
	printf("<->(null)\n");

	return;
}

/* return 1 if node data is before data */
int IsBefore(const void *node_data, const void *data, void *param)
{
	return (strlen((char *)node_data) < strlen((char *)data));
}

int IsMatch(const void *node_data, const void *data, void *param)
{
	return !(strcmp((char *)node_data, (char *)data));
}

int Null(void *node_data, void *param)
{
	(void)param;
	if (NULL == (char *)node_data)
	{
		return(1);
	}

	return (0);
}

int IsMentor(const void *node_data,
	      const void *data,
	      void *param)
{
	return (strcmp((char*)node_data, (char *)data));
}
