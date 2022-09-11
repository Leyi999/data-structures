#define _CRT_SECURE_NO_WARNINGS 1
#include"RBTree.h"
void TestRBTree1()
{
	//int a[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	int a[] = { 30, 29, 28, 27, 26, 25, 24, 11, 8, 7, 6, 5, 4, 3, 2, 1 };
	RBTree<int, int> t;
	for (auto e : a)
	{
	t.Height();
		t.insert(make_pair(e, e));
	}
	t.LevelOrder();
	t.InOrder();
}

void TestRBTree2()
{
	const size_t N = 1024 * 1024;
	vector<int> v;
	v.reserve(N);
	srand(time(0));
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(rand());
		//v.push_back(i);
	}

	RBTree<int, int> t;
	for (auto e : v)
	{
		t.insert(make_pair(e, e));
	}

	//t.levelOrder();
	//cout << endl;
	cout << "ÊÇ·ñÆ½ºâ?" << t.IsBalanceTree() << endl;
	t.Height();

	//t.InOrder();
}
int main() {

	TestRBTree2();
	return 0;
}