#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
typedef int ListNodeDataType;
typedef struct ListNode {
	ListNodeDataType val;
	struct ListNode* prev;
	struct ListNode* next;
}ListNode,LN,List;

ListNode* BuyListNode(ListNodeDataType x);

ListNode* ListInit();//����һ��ͷ���

void ListDestory(ListNode* head);//����һ������

void ListPrint(ListNode* head);//��ӡ����

void ListPushBack(ListNode* head, ListNodeDataType x);//β��

void ListPopBack(ListNode* head);//βɾ

void ListPushFront(ListNode* head, ListNodeDataType x);//ͷ��

void ListPopFront(ListNode* head);//ͷɾ

ListNode* ListFind(ListNode* head, ListNodeDataType x);//����

void ListInsert(ListNode* pos, ListNodeDataType x);//����

void ListErase(ListNode* pos);//ɾ��
