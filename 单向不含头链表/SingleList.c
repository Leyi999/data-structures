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
void SingleListInsert(SLN* plist, SLN* pos, SLNDataType x)
{
	if (!plist) {
		printf("SingleListInsert:: plist=NULL!\n");
	}
	if (!pos) {
		printf("SingleListInsert:: pos=NULL\n");
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
		printf(" SingleListInsertBefore fail:: pos = NULL!\n");
		return;
	}
	if (!*pplist) {
		printf("SingleListInsertBefore fail:: plist=NULL!\n");
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
void SingleListErase(SLN** pplist, SLN* pos) {
	assert(pplist);
	if (!pos) {
		printf("SingleListErase fail:: pos=NULL!\n");
		return;
	}
	if (!*pplist) {
		printf("SingleListErase fail:: plist=NULL!\n");
		return;
	}
	if (*pplist == pos) {
		*pplist = pos->next;
		free(pos);
		pos = NULL;
		return;
	}
	SLN* cur = *pplist;
	while (cur->next != pos) {
		cur = cur->next;
	}
	cur->next = pos->next;
	free(pos);
}
void SingleListEraseAfter(SLN*pos) {
	if (!pos) {
		printf("SingleListEraseAfter fail:: pos=NULL!\n");
		return;
	}
	SLN* next = pos->next;
	if (next) {
		pos->next = next->next;
		free(next);
		next = NULL;
	}
}
void SingleListMotify(SLN* pos, SLNDataType x) {
	if (!pos) {
		printf("SingleListMotify fail:: pos=NULL!\n");
		return;
	}
	pos->data = x;
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
void SingleListDestroy(SLN** pplist) {
	assert(pplist);
	if (!*pplist)return;
	SLN* cur = *pplist;
	SLN* pev = NULL;
	while (cur) {
		pev = cur;
		cur = cur->next;
		free(pev);
		pev = NULL;
	}
	*pplist = NULL;
}