#define _CRT_SECURE_NO_WARNINGS 1
#include"SingleList.h"
int main() {
	SingleListNode* slist = NULL;
	SingleListPushBack(&slist,1);
	PrintSList(slist);
	SingleListPushBack(&slist, 2);
	SingleListPushBack(&slist, 3);
	SingleListPushBack(&slist, 4);
	PrintSList(slist);
	SingleListPopBack(&slist);
	PrintSList(slist);
	SingleListPopBack(&slist);
	PrintSList(slist);

	SingleListPopFront(&slist);
	PrintSList(slist);
	SingleListPopFront(&slist);
	PrintSList(slist);
	SingleListPopFront(&slist);
	PrintSList(slist);
	SingleListPopFront(&slist);
	PrintSList(slist);
	SingleListPopFront(&slist);
	PrintSList(slist); 	
	return 0;
}