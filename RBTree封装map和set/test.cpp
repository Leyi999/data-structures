#define _CRT_SECURE_NO_WARNINGS 1
#include"map.h"
#include"set.h"
using namespace std;
void test_map1()
{
	map<string, int> m;
	m.insert(make_pair("111", 1));
	m.insert(make_pair("555", 5));
	m.insert(make_pair("333", 3));
	m.insert(make_pair("222", 2));

	map<string, int>::iterator it = m.begin();
	while (it != m.end())
	{
		cout << it->first << ":" << it->second << endl;
		++it;
	}
	cout << endl;

	for (auto& kv : m)
	{
		cout << kv.first << ":" << kv.second << endl;
	}
	cout << endl;
}

void test_map2()
{
	string arr[] = { "2", "2", "3", "3", "2", "2", "2", "2", "1", "1", "5" };

	map<string, int> countMap;
	for (auto& str : arr)
	{
		countMap[str]++;
	}

	for (const auto& kv : countMap)
	{
		cout << kv.first << ":" << kv.second << endl;
	}
}
void test_set1()
{
	set<int> s;
	s.insert(8);
	s.insert(6);
	s.insert(11);
	s.insert(5);
	s.insert(6);
	s.insert(7);
	s.insert(10);
	s.insert(13);
	s.insert(12);
	s.insert(15);

	set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << endl;
}

int main() {
	/* map<int, int > m1;
	m1.insert(make_pair(1, 2));
	m1.insert(make_pair(3, 2));
	m1.insert(make_pair(2, 2));
	m1.insert(make_pair(4, 2));
	m1.insert(make_pair(6, 2));
	m1.insert(make_pair(5,2));
	for (auto e : m1)
		cout << e.first << ' ';
	cout << endl;
	set<int>s1;
	s1.insert(1);
	s1.insert(3);
	s1.insert(2);
	s1.insert(4);
	s1.insert(6);
	s1.insert(5);
	s1.LevelOrder();
	cout << endl;
	cout << (*(m1.find(4))).first;*/
	test_map1();
	test_map2();
	test_set1();
	return 0;
}