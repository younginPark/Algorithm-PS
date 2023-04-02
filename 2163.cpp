#include <iostream>
using namespace std;

int main(){

	long long arr[69] = { 1, 1, 2, 4, 0, };
	int t;
	int tmp = 0;

	for(int j = 4; j < 68; j++){
		arr[j] = arr[j-1] + arr[j-2] + arr[j-3] + arr[j-4];
	}

	cin >> t;

	for(int i = 0; i < t; i++){

		cin >> tmp;

		cout << arr[tmp] << "\n";

	}

	return 0;
}