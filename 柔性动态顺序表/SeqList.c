#define _CRT_SECURE_NO_WARNINGS 1
#include"SeqList.h"

void SeqListInit(SeqList** psl) {
	assert(psl);
	*psl = malloc(sizeof(psl) + 0);
	if (*psl==NULL) { 
		printf("SeqListInit:: malloc fail!");
		return;
	}
	(*psl)->size = 0;
	(*psl)->capacity = 0;
}
void SeqListDestory(SeqList** psl) {
	assert(*psl);
	free(*psl);
	(*psl) = NULL;
}
void SeqListCheakCapacity(SeqList** psl) {
	assert(*psl);
	if ((*psl)->size == (*psl)->capacity) {
		size_t newCapacity = ((*psl)->capacity == 0) ? 4 : 2 * (*psl)->capacity;
		SeqList* tmp = realloc(*psl, sizeof(SeqList) + newCapacity * sizeof(SLDataType));

		if (tmp == NULL) {
			printf("SeqListCheakCapacity:: realloc失败！");
			exit(-1);
		}
		(*psl) = tmp;
		(*psl)->capacity = newCapacity;
	}
}

void SeqListPushBack(SeqList** psl,SLDataType x) {
	SeqListCheakCapacity(psl);
	(*psl)->arr[(*psl)->size++] = x;
}
void SeqListPopBack(SeqList** psl) {
	assert(*psl);
	if ((*psl)->size > 0)
	--(*psl)->size;
}
void SeqListPushFront(SeqList** psl,SLDataType x) {
	assert(*psl);
	SeqListCheakCapacity(psl);
	memmove((*psl)->arr + 1, (*psl)->arr, (*psl)->size*sizeof(SLDataType));
	*(*psl)->arr = x;
	++(*psl)->size;
}
void SeqListPopFront(SeqList** psl) {
	assert(*psl);
	memmove((*psl)->arr, (*psl)->arr + 1, ((*psl)->size---1)*sizeof(SLDataType));
}
void SeqListPrint(SeqList** psl) {
	assert((*psl)->arr);
	int len = (*psl)->size;
	if (len == 0) {
		printf("                                (NULL)                           \n");
	}
	for (int i = 0; i < len;i++) {
		printf("%d ", (*psl)->arr[i]);
	}
	printf("\n");
}

int SeqListFind(SeqList** psl, SLDataType x) {
	assert(*psl);
	for (int i = 0; i < (int)(*psl)->size; i++) {
		if ((*psl)->arr[i] == x)
			return i;
	}
	return -1;
}
void SeqListInsert(SeqList** psl, size_t pos, SLDataType x) {
	assert(*psl);
	SeqListCheakCapacity(psl);
	if (pos > (*psl)->size) {
		printf("越界!\n");
		return;
	}
	memmove((*psl)->arr + pos + 1, (*psl)->arr + pos, ((*psl)->size++ - pos) * sizeof(SLDataType));
	(*psl)->arr[pos] = x;
}
void SeqListErase(SeqList** psl, size_t pos) {
	assert(*psl);
	if (pos >= (*psl)->size) {
		printf("越界!\n");
		return;
	}
	memmove((*psl)->arr + pos, (*psl)->arr + pos + 1, ((*psl)->size-- - pos-1) * sizeof(SLDataType));
}
void SeqListModify(SeqList** psl, size_t pos, SLDataType x) {
	assert(*psl);
	if (pos >= (*psl)->size) {
		printf("越界!\n");
	}
	(*psl)->arr[pos] = x;
}