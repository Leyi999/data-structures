#define _CRT_SECURE_NO_WARNINGS 1
#include"stack.h"
void StackInit(Stack* ps) 
{
	assert(InitCapacity);
	assert(ps);
	ps->arr = (StackDataType*)malloc(InitCapacity * sizeof(StackDataType));
	ps->top = 0;
	ps->capacity = InitCapacity;
}

void StackDestory(Stack* ps) 
{
	assert(ps);
	free(ps->arr);
}

void StackPush(Stack* ps, StackDataType x) 
{
	assert(ps);
	if (ps->top == ps->capacity) {
		StackDataType* ret;
		assert(ret = (StackDataType*)realloc(ps->arr, (unsigned int)2 * ps->capacity * sizeof(StackDataType)));
		ps->arr = ret;
		ps->capacity *= 2;
	}
	ps->arr[ps->top++] = x;
}

void StackPop(Stack* ps)
{
	assert(ps);
	if (ps->top) {
		ps->top--;
	}
}

bool StackEmpty(Stack* ps)
{
	assert(ps);
	return ps->top==0;
}

StackDataType StackTop(Stack* ps)
{
	assert(ps);
	assert(ps->top);
	return ps->arr[ps->top-1];
}

size_t StackSize(Stack* ps)
{
	assert(ps);
	return ps->top;
}