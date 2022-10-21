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
	two_bitset<10> tbs;
	int arr[] = { 1,1,2,6,9,4,1,5,6,9,8 };
	for (auto e : arr)
		tbs.set(e);
	for (auto e : arr) {
		if (tbs.is_once(e))
			cout << e << ' ';
	}
}
int main() {
	float ret = 0;
	for (int i = 1; i <= 100; i++) {
		float rs = (float)1 / (float)i;
		if (i % 2 == 0)
			rs = rs * -1;
		ret = ret + rs;
	}
	printf("%lf", ret);
	//test_towbitset();

	return 0;
}