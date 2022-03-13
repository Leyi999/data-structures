#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
typedef int SLNDataType;

typedef struct SingleListNode {
	SLNDataType data;
	struct SingleListNode* next;
} SingleListNode, SLNote, SLN;

SLN* BuySListNode(SLNDataType x);

void SingleListPushBack(SLN**pplist,SLNDataType x);
void SingleListPopBack(SLN** pplist);
void SingleListPopFront(SLN** pplist);

void PrintSList(SLN*plist);