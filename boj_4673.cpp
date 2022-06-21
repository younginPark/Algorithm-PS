#include <iostream>
#include <string>
using namespace std;

int num[10001];

void functionD(int n) {
	int tmp_num = n;
	string str1 = to_string(n);
	for (int i = 0; i < str1.size(); i++) {
		tmp_num += str1[i] - '0';
	}
	if (tmp_num >= 10001) {
		return;
	}
	num[tmp_num] = 1;
}

int main() {
	for (int i = 1; i <= 10000; i++) {
		functionD(i);
	}
	for (int i = 1; i <= 10000; i++) {
		if (num[i] != 1) {
			cout << i << "\n";
		}
	}

	return 0;
}