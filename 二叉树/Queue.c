#include "Queue.h"

void QueueInit(Queue* pq)
{
	assert(pq);
	pq->head = pq->tail = NULL;
	pq->size = 0;
}

void QueueDestroy(Queue* pq)
{
	assert(pq);
	QueueNode* head = pq->head;
	pq->head = pq->tail = NULL;
	while (head) {
		QueueNode* next = head->next;
		free(head);
		head = next;
	}
}

void QueuePush(Queue* pq,QueueNodeDataType x)
{
	assert(pq);
	QueueNode* newnode;
	assert(newnode = (QueueNode*)malloc(sizeof(QueueNode)));
	newnode->val = x;
	newnode->next = NULL;
	if (pq->tail == NULL){
		assert(pq->head == NULL);
		pq->tail = pq->head = newnode;
	}
	else {
		pq->tail->next = newnode;
		pq->tail = newnode;
	}
	pq->size++;
}

void QueuePop(Queue* pq)
{
	assert(pq);
	if (pq->head) {
		QueueNode*next = pq->head->next;
		if (pq->head == pq->tail)
			pq->tail = NULL;
		free(pq->head);
		pq->head = next;
		pq->size--;
	}
}

bool QueueEmpty(Queue* pq)
{
	assert(pq);
	return pq->head==NULL;
}

size_t QueueSize(Queue* pq)
{
	assert(pq);
	////size_t size=0;
	////QueueNode* cur = pq->head;
	////while (cur) {
	////	size++;
	////	cur = cur->next;
	////}
	////return size;
	return pq->size;
}

QueueNodeDataType QueueFront(Queue* pq)
{	
	assert(pq);
	assert(pq->head);
	return pq->head->val;
}

QueueNodeDataType QueueBack(Queue* pq)
{
	assert(pq);
	assert(pq->tail);
	return pq->tail->val;
}
