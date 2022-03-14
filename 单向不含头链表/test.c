#define _CRT_SECURE_NO_WARNINGS 1
#include"SingleList.h"
int main() {
	SL* slist = NULL;
	SingleListPushFront(&slist,1);
	PrintSList(slist);
	SingleListPushFront(&slist, 9);
	PrintSList(slist);
	SingleListPushBack(&slist, 2);
	PrintSList(slist);
	SingleListPushBack(&slist, 3);
	PrintSList(slist);
	SingleListPushBack(&slist, 4);
	PrintSList(slist);
	SingleListInsertAfter(slist, SingleListFind(slist,4), 5);
	//PrintSList(slist);
	//SingleListPopBack(&slist);
	//PrintSList(slist);
	//SingleListPopBack(&slist);
	//PrintSList(slist);
	PrintSList(slist);
	SingleListInsertBefore(&slist, SingleListFind(slist, 9), 0);
	PrintSList(slist);
	SingleListInsertBefore(&slist, SingleListFind(slist, 9), 0);
	PrintSList(slist);
	SingleListInsertBefore(&slist, SingleListFind(slist, 9), 0);
	PrintSList(slist);	SingleListInsertBefore(&slist, SingleListFind(slist, 9), 0);
	PrintSList(slist);
	SingleListInsertAfter(slist, SingleListFind(slist, 9), 9);
	PrintSList(slist);
	SingleListInsertAfter(slist, SingleListFind(slist, 9), 9);
	PrintSList(slist);
	return 0;
}