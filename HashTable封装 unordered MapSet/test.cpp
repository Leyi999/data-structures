#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include"HashTable.h"
#include"unordered_map.h"
#include"unordered_set.h"
using namespace std;
//
//void TestHT3()
//{
//	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };
//
//	//HashTable<string, int, StringHash> countHT;
//	HashTable<string, pair<string,int>,> countHT;
//
//	for (auto& str : arr)
//	{
//		auto ret = countHT.Find(str);
//		if (ret)
//		{
//			ret->_kv.second++;
//		}
//		else
//		{
//			countHT.Insert(make_pair(str, 1));
//		}
//	}
//
//}
void test_map()
{
	
	unordered_map<string, int> uoMap;
	
	uoMap["2b"] = 666;
	uoMap["123"] = 123;
	uoMap["2a"] = 665;

	for (const auto& kv : uoMap)
	{
		cout << kv.first << ":" << kv.second << endl;
	}
}
int main() {
	int a[] = { 20,5,8,99999,10,30,50,60,70,52,79,10,31,1498,90 };
	 unordered_map<int ,int>  HT;
	for (const auto& e : a)
		HT.insert(make_pair(e, e));
	for (const auto& n : HT)
		cout << n.first<<endl;

	unordered_set<int>  HTs;
	for (const auto& e : a)
		HTs.insert(e);
	for (const auto& n : HT)
		cout << n.first << endl;
	test_map();
	//cout << HT.Find(99999)->_kv.first << endl;
	//HT.erase(20);
	//cout << HT.Find(20) << endl;
	//cout << HT.Find(99999)->_kv.first;

	return 0;
}