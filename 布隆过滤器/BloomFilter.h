#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<bitset>
#include<string>
using namespace std;
struct BKDRHash
{
	size_t operator()(const string& s)
	{
		// BKDR
		size_t value = 0;
		for (auto ch : s)
		{
			value *= 31;
			value += ch;
		}
		return value;
	}
};

struct APHash
{
	size_t operator()(const string& s)
	{
		size_t hash = 0;
		for (long i = 0; i < s.size(); i++)
		{
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ s[i] ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ s[i] ^ (hash >> 5)));
			}
		}
		return hash;
	}
};

struct DJBHash
{
	size_t operator()(const string& s)
	{
		size_t hash = 5381;
		for (auto ch : s)
		{
			hash += (hash << 5) + ch;
		}
		return hash;
	}
};


struct JSHash
{
	size_t operator()(const string& s)
	{
		size_t hash = 1315423911;
		for (auto ch : s)
		{
			hash ^= ((hash << 5) + ch + (hash >> 2));
		}
		return hash;
	}
};

template <size_t N,class T=string, class HashFunc1=BKDRHash, class HashFunc2=APHash, class HashFunc3=DJBHash>
class bloomfilter {//һ��ֵ�ö����ϣֵ��ʾ �ܿ����ж��ڲ��� ����һ��������
public:			   //�������� ��������Ƿ�ע��� �� ȥ���ݿ�ȷ�� ���� ����ע��
							//�Ƿ��ں����� ��ȥȷ�� ���ڷ���
					//�ܳ䵱һ�������м��Ľ�ɫ���ռ�����С��������µ�ͬʱ���Ч��
	void set(T num) {
		bs.set(HashFunc1()(num)%N);
		bs.set(HashFunc2()(num)%N);
		bs.set(HashFunc3()(num)%N);
	}
	bool test(T num) {
		return bs.test(HashFunc1()(num) % N) && bs.test(HashFunc2()(num) % N) && bs.test(HashFunc3()(num) % N);//����һ��������
	}
private:
	bitset<N> bs;
};