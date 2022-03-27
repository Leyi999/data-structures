#define _CRT_SECURE_NO_WARNINGS 1
#include"Queue.h"
int main() {
	Queue test;
	Queue* ptest=&test;
	QueueInit(ptest);
	QueuePush(ptest,1);
	QueuePush(ptest,2);
	QueuePop(ptest);
	QueuePop(ptest);
	QueuePop(ptest);
	QueuePush(ptest, 1);
	QueuePush(ptest, 2);
	printf("%u ", test.size);
	QueueDestroy(ptest);
	printf("%u ", QueueEmpty(ptest));

	return 0;




}