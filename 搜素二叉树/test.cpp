#define _CRT_SECURE_NO_WARNINGS 1
#include"SBTree.hpp"
#include<iostream>
int main() {
	SBTree <int>sbt2;
	int a[] = { 5,3,4,1,7,8,2,6,0,9 };
	//int b = 4;
	//printf("%d", *b);
	//printf("%d", *a);
	//printf("%d", *(a + 1));
	for (auto e : a)
		sbt2.RInsert(e);
	sbt2.InOder();
	cout << endl;
	//SBTree<int>sbt1(sbt2);
	//sbt1.InOder();
	//std::cout << std::endl;
	//sbt1.Erase(7);
	//sbt1.InOder();
	//for (auto e : a) {
	//	sbt1.Erase(e);
	//	std::cout << std::endl;
	//	sbt1.InOder();
	//}
	//const SBNode<int>* ret = sbt1.Find(8);
	//if(ret)
	sbt2.InOder();
	cout << endl;
	for (auto r : a) {
		sbt2.RErase(r);
		sbt2.InOder();
		cout << endl;
	}
	//	sbt2.RErase(3);
	//sbt2.InOder();
	//cout << endl;
	//std::cout << (sbt2.RFind(r))->_key<<' ';
	return 0;
}