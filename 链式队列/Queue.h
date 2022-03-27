#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

typedef int QueueNodeDataType;

typedef struct QueueNode{
	QueueNodeDataType val;
	struct QueueNode* next;
} QueueNode;

typedef struct Queue {
	QueueNode* head;
	QueueNode* tail;
	size_t size;
}Queue;

void QueueInit(Queue* pq);
void QueueDestroy(Queue* pq);
void QueuePush(Queue* pq, QueueNodeDataType x);
void QueuePop(Queue* pq);

bool QueueEmpty(Queue* pq);	

size_t QueueSize(Queue* pq);

QueueNodeDataType QueueFront(Queue* pq);
QueueNodeDataType QueueBack(Queue* pq);