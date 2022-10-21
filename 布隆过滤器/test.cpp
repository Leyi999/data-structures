#define _CRT_SECURE_NO_WARNINGS 1
#include"BloomFilter.h"
void testBloomFilter1()
{
	
	// 插入10个值
	// 哈希函数 k
	// 插入n个值
	// 位数为n*( k/0.69);
	//BloomFilter<44, string, BKDRHash, APHash, DJBHash> bf;
	bloomfilter<43,string,BKDRHash,APHash,DJBHash> bf;

	string a[] = { "苹果", "香蕉", "西瓜", "111111111", "eeeeeffff", "草莓", "休息", "继续", "查找", "set" };

	for (auto& e : a)
	{
		bf.set(e);
	}

	for (auto& e : a)
	{
		cout << bf.test(e) << endl;
	}
	cout << endl;

	cout << bf.test("芒果") << endl;
	cout << bf.test("string") << endl;
	cout << bf.test("ffffeeeee") << endl;
	cout << bf.test("31341231") << endl;
	cout << bf.test("ddddd") << endl;
	cout << bf.test("3333343") << endl;

}
int main() {
	testBloomFilter1();
	return 0;
}