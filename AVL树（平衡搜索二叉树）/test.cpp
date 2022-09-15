#define _CRT_SECURE_NO_WARNINGS 1
#include"AVLTree.h"
#include <iostream>
#include<random>
#include<time.h>
template <class f,class s>
pair<f, s> make_pair(f fi, s se) {
	return pair<f, s>(fi, se);
}
int main() {
	srand(time(0));
	AVLTree<int, int >tree;
	int arr[] = {5,5,3,4,14,5 };
	for (int i=1000000;i ;i--)
			tree.insert(make_pair(rand(), 1));
	//for(auto e:arr)
	//tree.insert(make_pair(e, 1));
	//tree.LevelOrder();
	cout<<tree.IsBalanceTree();
	return 0;
}