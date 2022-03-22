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

ListNode* ListInit();//返回一个头结点

void ListDestory(ListNode* head);//销毁一个链表

void ListPrint(ListNode* head);//打印链表

void ListPushBack(ListNode* head, ListNodeDataType x);//尾插

void ListPopBack(ListNode* head);//尾删

void ListPushFront(ListNode* head, ListNodeDataType x);//头插

void ListPopFront(ListNode* head);//头删

ListNode* ListFind(ListNode* head, ListNodeDataType x);//查找

void ListInsert(ListNode* pos, ListNodeDataType x);//插入

void ListErase(ListNode* pos);//删除
