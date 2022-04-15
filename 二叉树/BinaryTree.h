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

//建立创建一个值为x的二叉树节点
BinaryTreeNode* BuyBinaryTreeNode(BinaryTreeDataType x);
//根据前序遍历的数组构建二叉树
BinaryTreeNode* BinaryTreeCreate(BinaryTreeDataType*array,size_t* pos);
//销毁二叉树
void BinaryTreeDestroy(BinaryTreeNode* root);
//获取节点个数
size_t BinaryTreeSize(BinaryTreeNode* root);
//获取叶子节点个数
size_t BinaryTreeLeafSize(BinaryTreeNode* root);
//获取第k层节点个数
size_t BinaryTreeLevelKSize(BinaryTreeNode* root, size_t k);
//前序搜素值为x的节点
BinaryTreeNode* BinaryTreeFind(BinaryTreeNode* root, BinaryTreeDataType x);
//前序遍历
void BinaryTreePrevOrder(BinaryTreeNode* root);
//中序遍历
void BinaryTreeInOrder(BinaryTreeNode* root);
//后序遍历
void BinaryTreePostOrder(BinaryTreeNode* root);
//层序遍历
void BinaryTreeLevelOrder(BinaryTreeNode* root);
//检查是否为满二叉树
bool BinaryTreeComplete(BinaryTreeNode* root);