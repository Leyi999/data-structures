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

void HeapInit(Heap* ph);//��ʼ��
void HeapDestroy(Heap* ph);//����

void HeapCheckCapacity(Heap* ph);//�������

void Swap(HeapDataType* parent, HeapDataType* child);//����Ԫ��

void AdjustUp(HeapDataType* arr, size_t pos);//��pos�����ϵ���
void AdjustDown(HeapDataType* arr, size_t leaf,size_t pos);//��pos�����µ���

void HeapPush(Heap* ph, HeapDataType x);//���Ԫ��
void HeapPop(Heap* ph);//ɾ��Ԫ��

HeapDataType HeapTop(Heap* ph);//���ʶѶ�Ԫ��
size_t HeapSize(Heap* ph);//��ȡ�Ѵ�С

bool HeapEmpty(Heap* ph);//�����Ƿ�Ϊ��


