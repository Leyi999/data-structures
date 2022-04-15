#define _CRT_SECURE_NO_WARNINGS 1
#include"BinaryTree.h"

void test() {
	BinaryTreeDataType arr[18] = "ABD##E##CF##G##";
	size_t i = 0;
	BTNode* test = BinaryTreeCreate(arr, &i);
	BinaryTreePrevOrder(test);
	printf("\n");
	BinaryTreeInOrder(test);
	printf("\n");
	BinaryTreePostOrder(test);
	printf("\n");
	BinaryTreeLevelOrder(test);
	printf("\n");
	printf("%d", BinaryTreeComplete(test));
	BinaryTreeDestroy(test);
}
int main() {
	test();
	return 0;
}