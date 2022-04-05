#define _CRT_SECURE_NO_WARNINGS 1
#include"Heap.h"
void test1() {
	Heap test;
	HeapInit(&test);
	HeapPush(&test, 3);
	HeapPush(&test, 4);
	HeapPush(&test, 2);
	HeapPush(&test, 1);
	HeapPush(&test, 0);
	HeapDestroy(&test);
}
void test2() {
	Heap test;
	HeapInit(&test);
	HeapPush(&test, 3);
	HeapPush(&test, 4);
	HeapPush(&test, 2);
	HeapPush(&test, 1);
	HeapPush(&test, 0);

	HeapPop(&test);
	HeapPush(&test, 5);
	HeapPop(&test);
	HeapPop(&test);
	HeapPop(&test);
	HeapPop(&test);
	HeapPop(&test);
	HeapPop(&test);
	HeapPop(&test);
	HeapPop(&test);

	printf("%d ", HeapEmpty(&test));
	printf("%d ", HeapSize(&test));
	HeapPush(&test, 3);
	printf("%d ", HeapSize(&test));
	printf("%d ", HeapEmpty(&test));

	printf("%d ", HeapSize(&test));
	HeapPush(&test, 4);
	printf("%d ", HeapSize(&test));
	HeapPush(&test, 2);
	printf("%d ", HeapSize(&test));
	HeapPush(&test, 1);
	printf("%d ", HeapSize(&test));
	HeapPush(&test, 0);
	printf("%d ", HeapSize(&test));
	HeapPop(&test);
	printf("%d ", HeapSize(&test));
	HeapPush(&test, 5);
	printf("%d ", HeapSize(&test));
	HeapDestroy(&test);
}
void test3() {
	Heap test;
	HeapInit(&test);

	HeapPush(&test, 3);
	printf("%d ", HeapTop(&test));
	HeapPush(&test, 4);
	printf("%d ", HeapTop(&test));
	HeapPush(&test, 2);
	printf("%d ", HeapTop(&test));
	HeapPush(&test, 1);
	printf("%d ", HeapTop(&test));
	HeapPush(&test, 0);
	printf("%d ", HeapTop(&test));
	HeapPop(&test);
	printf("%d ", HeapTop(&test));
	HeapPush(&test, 5);
	printf("%d ", HeapTop(&test));

	HeapDestroy(&test);
}
int main() {
	test3();
}