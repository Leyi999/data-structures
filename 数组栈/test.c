#define _CRT_SECURE_NO_WARNINGS 1
#include"stack.h"
int main() {
	Stack test;
	StackInit(&test);
	StackPush(&test, 1);
	StackPush(&test, 2);
	StackPush(&test, 3);
	StackPush(&test, 4);
	StackPop(&test);
	StackPush(&test, 5);
	printf("%u\n", StackSize(&test));
	if (!StackEmpty(&test)) {
		printf("%d\n", StackTop(&test));
	}
	return 0;

}