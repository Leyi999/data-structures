#include "Heap.h"

#define _CRT_SECURE_NO_WARNINGS 1

void HeapInit(Heap* ph)
{
	assert(ph);
	ph->arr = NULL;
	ph->capacity = ph->size = 0;
}

void HeapDestroy(Heap* ph)
{
	assert(ph);
	free(ph->arr);
}

void HeapCheckCapacity(Heap* ph)
{
	assert(ph);
	if (ph->size == ph->capacity) {
		HeapDataType* tmp;
		assert(tmp = realloc(ph->arr, (ph->capacity ? 2 * ph->capacity : 4 )* sizeof(HeapDataType)));
		ph->arr = tmp;
		ph->capacity = ph->capacity ? 2 * ph->capacity : 4;
	}
}

void Swap(HeapDataType* parent, HeapDataType* child)
{
	assert(parent && child);
	HeapDataType tmp = *parent;
	*parent = *child;
	*child = tmp;
}

void AdjustUp(HeapDataType* arr, size_t pos)
{
	assert(arr);
	size_t parent = (pos - 1) / 2;
	while (pos && arr[parent] > arr[pos]) {
		Swap(arr + parent, arr + pos);
		pos = parent;
		parent = (pos - 1) / 2;
	}
}

void AdjustDown(HeapDataType* arr, size_t leaf, size_t pos)
{
	size_t leftchild = 2 * pos + 1;
	while (leftchild<=leaf) {
		if (leftchild + 1 <= leaf && arr[leftchild] > arr[leftchild + 1])
			leftchild++;
		if (arr[pos] > arr[leftchild]) {
			Swap(arr + pos, arr + leftchild);
			pos = leftchild;
			leftchild = 2 * pos + 1;
		}
		else 
			break;
	}
}

void HeapPush(Heap* ph,HeapDataType x)
{
	assert(ph);
	HeapCheckCapacity(ph);
	ph->arr[ph->size++] = x;
	AdjustUp(ph->arr, ph->size - 1);
}

void HeapPop(Heap* ph)
{
	assert(ph);
	if (!ph->size)return;
	Swap(ph->arr, ph->arr + --ph->size);
	AdjustDown(ph->arr,ph->size-1,0);
}

HeapDataType HeapTop(Heap* ph)
{
	assert(ph);
	assert(ph->arr);
	return *ph->arr;
}

size_t HeapSize(Heap* ph)
{
	assert(ph);
	return ph->size;
}

bool HeapEmpty(Heap* ph)
{
	assert(ph);
	return !HeapSize(ph);
}

