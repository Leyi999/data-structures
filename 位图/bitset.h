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
	void set(size_t num) {
		_vt[num / 8] |= 1 << num % 8;
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
		//00 01 11
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