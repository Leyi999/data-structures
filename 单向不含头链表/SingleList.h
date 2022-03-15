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

SLN* SingleListFind(SLN* pplist, SLNDataType x);
void SingleListInsert(SLN* pplist, SLN* pos, SLNDataType x);
void SingleListInsertBefore(SLN** pplist, SLN* pos, SLNDataType x);
void SingleListErase(SLN** pplist, SLN* pos);
void SingleListEraseAfter(SLN* pos);
void SingleListMotify(SLN* pos, SLNDataType x);

void PrintSList(SLN*plist);
void SingleListDestroy(SLN** pplist);