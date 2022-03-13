#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
typedef int SLDataType;//元素数据类型
//动态顺序表

typedef struct SeqList {
	size_t size;//存储数据个数
	size_t capacity;//存储空间大小
	SLDataType arr[];
} SL, SeqList;

void SeqListInit(SeqList** psl);
void SeqListCheakCapacity(SeqList** psl);
void SeqListDestory(SeqList** psl);

void SeqListPushBack(SeqList** psl,SLDataType x);
void SeqListPopBack(SeqList** psl);
void SeqListPushFront(SeqList** psl,SLDataType x);
void SeqListPopFront(SeqList** psl);
void SeqListPrint(SeqList** psl);

int SeqListFind(SeqList** psl, SLDataType x);
void SeqListInsert(SeqList** psl, size_t pos, SLDataType x);
void SeqListErase(SeqList** psl, size_t pos);
void SeqListModify(SeqList** psl, size_t pos, SLDataType x);
