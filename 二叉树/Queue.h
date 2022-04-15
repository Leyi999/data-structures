#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

typedef struct BinaryTreeNode* QueueNodeDataType;

typedef struct QueueNode{
	QueueNodeDataType val;
	struct QueueNode* next;
} QueueNode;

typedef struct Queue {
	QueueNode* head;
	QueueNode* tail;
	size_t size;
}Queue;

//��ʼ������
void QueueInit(Queue* pq);
//���ٶ���
void QueueDestroy(Queue* pq);
//β��
void QueuePush(Queue* pq, QueueNodeDataType x);
//ͷɾ
void QueuePop(Queue* pq);
//�������Ƿ�Ϊ��
bool QueueEmpty(Queue* pq);	
//��ȡ����Ԫ�ظ���
size_t QueueSize(Queue* pq);
//��ȡ����Ԫ��
QueueNodeDataType QueueFront(Queue* pq);
//��ȡ��βԪ��
QueueNodeDataType QueueBack(Queue* pq);