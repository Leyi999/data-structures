#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
typedef int SLNDataType;

typedef struct SingleListNode {
	SLNDataType data;
	struct SingleListNode* next;
} SingleListNode, SLNote, SLN,SL;

SLN* BuySListNode(SLNDataType x);

void SingleListPushBack(SLN**pplist,SLNDataType x);
void SingleListPopBack(SLN** pplist);
void SingleListPushFront(SLN** pplist,SLNDataType x);
void SingleListPopFront(SLN** pplist);

void PrintSList(SLN*plist);
SLN* SingleListFind(SLN* pplist, SLNDataType x);
void SingleListInsertAfter(SLN* pplist, SLN* pos, SLNDataType x);
void SingleListInsertBefore(SLN** pplist, SLN* pos, SLNDataType x);
