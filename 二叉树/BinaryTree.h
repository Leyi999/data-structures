#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"Queue.h"
#include<stdlib.h>

typedef char BinaryTreeDataType ;

typedef struct BinaryTreeNode {
	BinaryTreeDataType data;
	struct BinaryTreeNode* leftchild;
	struct BinaryTreeNode* rightchild;
}BinaryTreeNode, BTNode;

//��������һ��ֵΪx�Ķ������ڵ�
BinaryTreeNode* BuyBinaryTreeNode(BinaryTreeDataType x);
//����ǰ����������鹹��������
BinaryTreeNode* BinaryTreeCreate(BinaryTreeDataType*array,size_t* pos);
//���ٶ�����
void BinaryTreeDestroy(BinaryTreeNode* root);
//��ȡ�ڵ����
size_t BinaryTreeSize(BinaryTreeNode* root);
//��ȡҶ�ӽڵ����
size_t BinaryTreeLeafSize(BinaryTreeNode* root);
//��ȡ��k��ڵ����
size_t BinaryTreeLevelKSize(BinaryTreeNode* root, size_t k);
//ǰ������ֵΪx�Ľڵ�
BinaryTreeNode* BinaryTreeFind(BinaryTreeNode* root, BinaryTreeDataType x);
//ǰ�����
void BinaryTreePrevOrder(BinaryTreeNode* root);
//�������
void BinaryTreeInOrder(BinaryTreeNode* root);
//�������
void BinaryTreePostOrder(BinaryTreeNode* root);
//�������
void BinaryTreeLevelOrder(BinaryTreeNode* root);
//����Ƿ�Ϊ��������
bool BinaryTreeComplete(BinaryTreeNode* root);