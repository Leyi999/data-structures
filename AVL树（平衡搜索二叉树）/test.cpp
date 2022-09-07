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
	int arr[] = {5,5,3,2,14,5 };
	for (int i=0;i<1000 ;i++)
			tree.insert(make_pair(rand(), 1));
	//for(auto e:arr)
	//tree.insert(make_pair(e, 1));
	tree.LevelOrder();
	return 0;
}