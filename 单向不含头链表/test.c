#define _CRT_SECURE_NO_WARNINGS 1
#include"SingleList.h"
int main() {
	SL* slist = NULL;
	SingleListPushFront(&slist, 1);
	PrintSList(slist);
	SingleListPushFront(&slist, 2);
	PrintSList(slist);
	SingleListPushFront(&slist, 4);
	PrintSList(slist);
	SingleListErase(&slist, SingleListFind(slist, 2));
	PrintSList(slist);
	SingleListPushFront(&slist, 2);
	PrintSList(slist);
	SingleListEraseAfter(slist);
	PrintSList(slist);
	SingleListMotify(SingleListFind(slist, 9),999);
	PrintSList(slist);

	

	return 0;
}