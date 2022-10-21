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
class bloomfilter {//一个值用多个哈希值表示 能快速判断在不在 允许一定的误判
public:			   //常见场景 检查名字是否注册过 在 去数据库确认 不在 允许注册
							//是否在黑名单 在去确认 不在放行
					//能充当一个过滤中间层的角色，空间消耗小的情况极下的同时提高效率
	void set(T num) {
		bs.set(HashFunc1()(num)%N);
		bs.set(HashFunc2()(num)%N);
		bs.set(HashFunc3()(num)%N);
	}
	bool test(T num) {
		return bs.test(HashFunc1()(num) % N) && bs.test(HashFunc2()(num) % N) && bs.test(HashFunc3()(num) % N);//允许一定的误判
	}
private:
	bitset<N> bs;
};