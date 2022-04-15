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

//初始化队列
void QueueInit(Queue* pq);
//销毁队列
void QueueDestroy(Queue* pq);
//尾插
void QueuePush(Queue* pq, QueueNodeDataType x);
//头删
void QueuePop(Queue* pq);
//检查队列是否为空
bool QueueEmpty(Queue* pq);	
//获取队内元素个数
size_t QueueSize(Queue* pq);
//获取队首元素
QueueNodeDataType QueueFront(Queue* pq);
//获取队尾元素
QueueNodeDataType QueueBack(Queue* pq);