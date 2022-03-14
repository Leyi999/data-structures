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
	if (!tail->next) {
		free(tail);
		*pplist = NULL;
		return;
	}
	while (tail->next->next) tail = tail->next;
	free(tail->next);
	tail->next = NULL;
}
void SingleListPushFront(SLN** pplist,SLNDataType x) {
	assert(pplist);
	SLN* newnode = BuySListNode(x);
	newnode->next = *pplist;
	*pplist = newnode;
}

void SingleListPopFront(SLN** pplist) {
	assert(pplist);
	if (!*pplist) return;
	SLN* plist = *pplist;
	*pplist = (*pplist)->next;
	free(plist);
}
void PrintSList(SLN* plist) {
	if (!plist) {
		printf("                         (NULL)                       \n");
		return;
	}
	SLN* cur = plist;
	while (cur) {
		printf("%d ", cur->data);
		cur=cur->next;
	}
	printf("\n");
}

SLN* SingleListFind(SLN* pplist, SLNDataType x)
{
	assert(pplist);
	SLN* cur = pplist;
	while (cur) {
		if (cur->data == x)
			return cur;
		cur = cur->next;
	}
	return NULL;
}
void SingleListInsertAfter(SLN* plist, SLN* pos, SLNDataType x)
{
	if (!plist) {
		printf("plist=NULL!\n");
	}
	if (!pos) {
		printf("pos=NULL!\n");
		return;
	}
	SLN* newnode = BuySListNode(x);
	newnode->next = pos->next;
	pos->next =newnode;
}

void SingleListInsertBefore(SLN** pplist, SLN* pos, SLNDataType x)
{
	assert(pplist);
	if (!pos) {
		printf("pos = NULL!\n");
		return;
	}
	if (!*pplist) {
		printf("plist=NULL!\n");
		return;
	}
	SLN* newnode = BuySListNode(x);
	if (*pplist == pos) {
		newnode->next = pos;
		*pplist = newnode;
		return;
	}
	SLN* cur = *pplist;
	while (cur->next != pos) {
		cur = cur->next;
	}
	newnode->next = cur->next;
	cur->next = newnode;
}
