#define _CRT_SECURE_NO_WARNINGS 1
#include"bitset.h"
using namespace std;
void test_bitset(){
	bitset<999999999> bs;
	bs.set(0);
	bs.set(999999999);
	bs.set(0);
	bs.set(0);

	cout << bs.test(0);
	cout << bs.test(1);
	cout << bs.test(999999999);
	
}
void test_towbitset() {
	two_bitset<999> tbs;
	int arr[] = { 1,1,2,6,9,4,1,5,6,9,8,999,999,999,999,12,12,12,7,7,7,874 };
	for (auto e : arr)
		tbs.set(e);
	for (auto e : arr) {
		if (tbs.is_once(e))
			cout << e << ' ';
	}
	cout << endl;
	for (auto e : arr) {
		if (tbs.is_twice(e))
			cout << e << ' ';
	}
	cout << endl;
	for (auto e : arr) {
		if (tbs.is_more_than_three_times(e))
			cout << e << ' ';
	}
}
int main() {

	test_towbitset();

	return 0;
}