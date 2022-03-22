#define _CRT_SECURE_NO_WARNINGS 1
#include"List.h"
void testpushpop(){
	List* head = ListInit();
	ListPushFront(head, 1);
	ListPushFront(head, 2);
	ListPushFront(head, 3);
	ListPopBack(head);
	ListPopFront(head);
	ListDestory(head);
}
void testprint(){
	List* head = ListInit();
	ListPushBack(head, 1);
	ListPushBack(head, 2);
	ListPushBack(head, 3);
	ListPrint(head);
	ListDestory(head);
}
void testfind() {
	List* head = ListInit();
	ListPushBack(head, 1);
	ListPushBack(head, 2);
	ListPushBack(head, 3);
	ListNode* ret = ListFind(head, 2);
	if (ret) {
		printf("%d ", ret->val);
	}
	else printf("ret==NULL ");
	ret = ListFind(head, 8);
	if (ret) {
		printf("%d ", ret->val);
	}
	else printf("ret==NULL ");
	ListDestory(head);
}
void testinsert() {
	List* head = ListInit();
	ListInsert(head, 1);
	ListPushBack(head, 2);
	ListPushBack(head, 3);
	ListInsert(head, 0);
	ListPrint(head);
	ListDestory(head);
}
void testerase() {
	List* head = ListInit();
	ListInsert(head, 1);
	ListPushBack(head, 2);
	ListPushBack(head, 3);
	ListInsert(head, 0);
	ListPrint(head);
	ListErase(head->next->next->next);
	ListPrint(head);
	ListDestory(head);
}
int main() {
	return 0;
}