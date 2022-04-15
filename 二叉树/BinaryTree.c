#define _CRT_SECURE_NO_WARNINGS 1

#include"BinaryTree.h"
BinaryTreeNode* BuyBinaryTreeNode(BinaryTreeDataType x)
{
	BinaryTreeNode* newnode = malloc(sizeof(BinaryTreeNode));
	assert(newnode);
	newnode->data = x;
	newnode->leftchild = newnode->rightchild = NULL;
	return newnode;
}

BinaryTreeNode* BinaryTreeCreate(BinaryTreeDataType* array, size_t* pos)
{
	if (array[*pos]=='#') {
		*pos+=1;
		return NULL;
	}
	BinaryTreeNode* newnode = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
	assert(newnode);
	newnode->data = array[(*pos)++];
	newnode->leftchild = BinaryTreeCreate(array, pos);
	newnode->rightchild = BinaryTreeCreate(array, pos);

	return newnode;
}


void BinaryTreeDestroy(BinaryTreeNode* root)
{
	if (root) {
		BinaryTreeDestroy(root->leftchild);
		BinaryTreeDestroy(root->rightchild);
		free(root);
	}
}


size_t BinaryTreeSize(BinaryTreeNode* root)
{
	if(root)
	return 1+BinaryTreeSize(root->leftchild)+BinaryTreeSize(root->rightchild);
	return 0;
}

size_t BinaryTreeLeafSize(BinaryTreeNode* root)
{
	if (!root)
		return 0;
	if (!root->leftchild && !root->rightchild)
		return 1;
	return BinaryTreeLeafSize(root->leftchild)+BinaryTreeLeafSize(root->rightchild);
}

size_t BinaryTreeLevelKSize(BinaryTreeNode* root, size_t k)
{
	if (root) {
		if (k - 1) {
			return BinaryTreeLevelKSize(root->leftchild, k - 1) + BinaryTreeLevelKSize(root->rightchild, k - 1);
		}
		return 1;
	}
	return 0;
}

BTNode* BinaryTreeFind(BinaryTreeNode* root, BinaryTreeDataType x)
{
	if (!root)
		return NULL;
	if (root->data == x)
		return root;
	BTNode* lret = BinaryTreeFind(root->leftchild, x);
	if (lret)
		return lret;
	return BinaryTreeFind(root->rightchild, x);
}

void BinaryTreePrevOrder(BinaryTreeNode* root)
{
	if (!root) {
		printf("NULL ");
		return;
	}
	printf("%c ", root->data);
	BinaryTreePrevOrder(root->leftchild);
	BinaryTreePrevOrder(root->rightchild);
}

void BinaryTreeInOrder(BinaryTreeNode* root)
{
	if (!root) {
		printf("NULL ");
		return;
	}
	BinaryTreeInOrder(root->leftchild);
	printf("%c ", root->data);
	BinaryTreeInOrder(root->rightchild);
}

void BinaryTreePostOrder(BinaryTreeNode* root)
{
	if (!root) {
		printf("NULL ");
		return;
	}
	BinaryTreePostOrder(root->leftchild);
	BinaryTreePostOrder(root->rightchild);
	printf("%c ", root->data);
}

void BinaryTreeLevelOrder(BinaryTreeNode* root)
{
	if (root == NULL) {
		printf("NULL ");
		return;
	}
	Queue pr;
	QueueInit(&pr);
	QueuePush(&pr, root);
	while (!QueueEmpty(&pr)) {
		if (QueueFront(&pr)) {
			printf("%c ", QueueFront(&pr)->data);
			QueuePush(&pr, QueueFront(&pr)->leftchild);
			QueuePush(&pr, QueueFront(&pr)->rightchild);
		}
		else
			printf("NULL ");
		QueuePop(&pr);
	}
	QueueDestroy(&pr);

}

bool BinaryTreeComplete(BinaryTreeNode* root)
{
	Queue pt;
	QueueInit(&pt);
	if (root) {
		QueuePush(&pt, root);
		while (!QueueEmpty(&pt)) {
			if (QueueFront(&pt)) {
				BinaryTreeNode* front = QueueFront(&pt);
				QueuePop(&pt);
				QueuePush(&pt, front->leftchild);
				QueuePush(&pt, front->rightchild);
			}
			else {
				while (!QueueEmpty(&pt)) {
					if (QueueFront(&pt))
						return false;
					QueuePop(&pt);
				}
			}
		}
	}
	return true;
}
