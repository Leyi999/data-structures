#define _CRT_SECURE_NO_WARNINGS 1
#include"BloomFilter.h"
void testBloomFilter1()
{
	
	// ����10��ֵ
	// ��ϣ���� k
	// ����n��ֵ
	// λ��Ϊn*( k/0.69);
	//BloomFilter<44, string, BKDRHash, APHash, DJBHash> bf;
	bloomfilter<43,string,BKDRHash,APHash,DJBHash> bf;

	string a[] = { "ƻ��", "�㽶", "����", "111111111", "eeeeeffff", "��ݮ", "��Ϣ", "����", "����", "set" };

	for (auto& e : a)
	{
		bf.set(e);
	}

	for (auto& e : a)
	{
		cout << bf.test(e) << endl;
	}
	cout << endl;

	cout << bf.test("â��") << endl;
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