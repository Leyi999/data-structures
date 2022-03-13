#define _CRT_SECURE_NO_WARNINGS 1
#include"SeqList.h"
int main() {
	SeqList*sl=NULL;
	SeqList** psl = &sl;
	SeqListInit(psl);
	SeqListPrint(psl);
	SeqListInsert(psl, 0, 1);
	SeqListPrint(psl);
	SeqListPopFront(psl);
	SeqListPrint(psl);
	SeqListPushBack(psl,1);
	SeqListPrint(psl);
	SeqListPopBack(psl);
	SeqListPrint(psl);
	SeqListPushBack(psl, 1);
	SeqListPushBack(psl, 1);
	SeqListPushBack(psl, 1);

	SeqListInsert(psl, 3, 2);
	SeqListInsert(psl, 1, 2);
	SeqListPushBack(psl, 1);
	SeqListErase(psl, 0);
	SeqListPushFront(psl, 666);
	SeqListPrint(psl);
	SeqListModify(psl, SeqListFind(psl,666), 999);
	SeqListPrint(psl);

	return 0;

}