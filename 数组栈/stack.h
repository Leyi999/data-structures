#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<stdbool.h>
#define InitCapacity 2//初始栈容量

typedef int StackDataType;

typedef struct Stack {
	StackDataType* arr;
	size_t top;
	size_t capacity;
}Stack;

void StackInit(Stack* ps);//初始化

void StackDestory(Stack* ps);//销毁

void StackPush(Stack* ps, StackDataType x);//压栈

void StackPop(Stack* ps);//出栈

bool StackEmpty(Stack* ps);//判断是否为空栈

StackDataType StackTop(Stack* ps);//访问栈顶元素

size_t StackSize(Stack* ps);//获取栈的大小
