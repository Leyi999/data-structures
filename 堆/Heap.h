#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

typedef int HeapDataType;
typedef struct Heap {
	HeapDataType* arr;
	size_t size;
	size_t capacity;
}Heap;

void HeapInit(Heap* ph);//初始化
void HeapDestroy(Heap* ph);//销毁

void HeapCheckCapacity(Heap* ph);//检查容量

void Swap(HeapDataType* parent, HeapDataType* child);//交换元素

void AdjustUp(HeapDataType* arr, size_t pos);//从pos处向上调整
void AdjustDown(HeapDataType* arr, size_t leaf,size_t pos);//从pos处向下调整

void HeapPush(Heap* ph, HeapDataType x);//添加元素
void HeapPop(Heap* ph);//删除元素

HeapDataType HeapTop(Heap* ph);//访问堆顶元素
size_t HeapSize(Heap* ph);//获取堆大小

bool HeapEmpty(Heap* ph);//检查堆是否为空


