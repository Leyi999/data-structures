#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

typedef int QueueNodeType;

typedef struct QueueNode{
	QueueNodeType val;
	struct QueueNode* next;
} QueueNode;

typedef struct Queue {
	QueueNode* head;
	QueueNode* tail;
	size_t size;
}Queue;

void QueueInit(Queue* pq);
void QueueDestroy(Queue* pq);
void QueuePush(Queue* pq, QueueNodeType x);
void QueuePop(Queue* pq);

bool QueueEmpty(Queue* pq);	

size_t QueueSize(Queue* pq);

QueueNodeType QueueFront(Queue* pq);
QueueNodeType QueueBack(Queue* pq);