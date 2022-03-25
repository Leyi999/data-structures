#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<stdbool.h>
#define InitCapacity 2//��ʼջ����

typedef int StackDataType;

typedef struct Stack {
	StackDataType* arr;
	size_t top;
	size_t capacity;
}Stack;

void StackInit(Stack* ps);//��ʼ��

void StackDestory(Stack* ps);//����

void StackPush(Stack* ps, StackDataType x);//ѹջ

void StackPop(Stack* ps);//��ջ

bool StackEmpty(Stack* ps);//�ж��Ƿ�Ϊ��ջ

StackDataType StackTop(Stack* ps);//����ջ��Ԫ��

size_t StackSize(Stack* ps);//��ȡջ�Ĵ�С
