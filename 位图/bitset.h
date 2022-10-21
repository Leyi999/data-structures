#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;
template<size_t N>
class bitset {
public:
	bitset() {
		_vt.resize(N / 8 + 1, 0);
	}
	void set(size_t num) {//采取直接映射的方式 //0~7 8~15 ...
		_vt[num / 8] |= 1 << num % 8;//将直接映射的那一位置为1
	}
	void reset(size_t num) {
		_vt[num / 8] &= ~(1 << num % 8);
	}
	bool test(size_t num) {
		return _vt[num / 8] & 1 << num % 8;
	}
private:
	vector<char> _vt;
};
template<size_t N>
class two_bitset {
public:
	void set(size_t num) {
		bool in1 = bs1.test(num);
		bool in2 = bs2.test(num);
		//00 01 11 可表示三种状态 出现一次 出现两次 和三次及以上 可根据需求改为能表示四种状态
		if (in1 == false && in2 == false)
			bs2.set(num);
		if (in1 == false && in2 == true)
			bs1.set(num);
	}
	bool is_once(size_t num) {
		return !bs1.test(num) && bs2.test(num);
	}
private:
	bitset<N> bs1;
	bitset<N> bs2;
};