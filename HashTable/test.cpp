#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include"HashTable.h"
using namespace std;
using namespace OpenHash;
void TestHT3()
{
	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };

	//HashTable<string, int, StringHash> countHT;
	HashTable<string, int> countHT;

	for (auto& str : arr)
	{
		auto ret = countHT.Find(str);
		if (ret)
		{
			ret->_kv.second++;
		}
		else
		{
			countHT.Insert(make_pair(str, 1));
		}
	}

}

int main() {
	//int a[] = { 20,5,8,99999,10,30,50,60,70,52,79,10,31,1498,90 };
	//HashTable<int, int >HT;
	//for (const auto& e : a)
	//	HT.Insert(make_pair(e, e));
	//cout << HT.Find(99999)->_kv.first << endl;
	//HT.erase(20);
	//cout << HT.Find(20) << endl;
	//cout << HT.Find(99999)->_kv.first;
	TestHT3();
	return 0;
}