#define _CRT_SECURE_NO_WARNINGS 1
#include"SingleList.h"

SLN* BuySListNode(SLNDataType x) {
	SLN* newnode = (SLN*)malloc(sizeof(SLN));
	assert(newnode);
	newnode->next = NULL;
	newnode->data = x;
	return newnode;
}
void SingleListPushBack(SLN**pplist,SLNDataType x) {
	assert(pplist);
	if (!*pplist) {
		*pplist = BuySListNode(x);
		return;
	}
	SLN* tail = *pplist;
	while (tail->next) tail= tail->next;
	tail->next=BuySListNode(x);
}
void SingleListPopBack(SLN** pplist) {
	assert(pplist);
	if (!*pplist)return;
	SLN* tail = *pplist;
	while (tail->next->next) tail = tail->next;
	tail->next = NULL;
}

void SingleListPopFront(SLN** pplist) {
	assert(pplist);
	if (!*pplist) return;
	*pplist = (*pplist)->next;
}

void PrintSList(SLN* plist) {
	if (!plist) {
		printf("                          NULL                        \n");
		return;
	}
	SLN* cur = plist;
	while (cur) {
		printf("%d ", cur->data);
		cur=cur->next;
	}
	printf("\n");
}