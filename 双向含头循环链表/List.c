#define _CRT_SECURE_NO_WARNINGS 1
#include"List.h"

ListNode* BuyListNode(ListNodeDataType x) {
	ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));
	assert(newnode);
	newnode->val = x;
	newnode->next = NULL;
	newnode->prev = NULL;
	return newnode;
}
ListNode* ListInit() {
	ListNode* head = BuyListNode(-1);
	head->next = head;
	head->prev = head;
	return head;
}
void ListDestory(ListNode* head) {
	assert(head);
	ListNode* cur = head->next;
	while (cur != head) {
		ListNode* next = cur->next;
		free(cur);
		cur = next;
	}
	free(cur);
}
void ListPrint(ListNode* head) {
	assert(head);
	ListNode* cur = head->next;
	if (cur == head) 
		printf("                         (NULL)                        \n");
	while (cur != head) {
		printf("%d ", cur->val);
		cur = cur->next;
	}
	printf("\n");
}
void ListPushBack(ListNode* head,ListNodeDataType x) {
	assert(head);
	ListNode * newnode= BuyListNode(x);
	assert(newnode);
	ListNode* tail = head->prev;
	tail->next = newnode;
	newnode->next = head;
	head->prev = newnode;
	newnode->prev = tail;
}
void ListPopBack(ListNode* head) {
	assert(head);
	if (head->prev == head) return;
	ListNode* tail = head->prev;
	head->prev = tail->prev;
	tail->prev->next = head;
	free(tail);
	tail = NULL;
}
void ListPushFront(ListNode* head, ListNodeDataType x) {
	assert(head);
	ListNode* newnode = BuyListNode(x);
	assert(newnode);
	ListNode* first = head->next;
	head->next = newnode;
	newnode->next = first;
	first->prev = newnode;
	newnode->prev = head;
}
void ListPopFront(ListNode* head) {
	assert(head);
	if (head->next == head) return;
	ListNode* first = head->next;
	head->next = first->next;
	first->next->prev=head;
	free(first);
	first = NULL;
}
ListNode* ListFind(ListNode* head, ListNodeDataType x){
	ListNode* cur = head->next;
	while (cur != head) {
		if (cur->val == x)
			return cur;
		cur = cur->next;
	}
	return NULL;
}
void ListInsert(ListNode* pos, ListNodeDataType x) {
	assert(pos);
	ListNode* newnode = BuyListNode(x);
	ListNode* pev = pos->prev;
	pos->prev = newnode;
	newnode->next = pos;
	pev->next = newnode;
	newnode->prev = pev;
}
void ListErase(ListNode* pos) {
	assert(pos);
	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;
	free(pos);
	pos = NULL;
}

