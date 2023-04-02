#include <iostream>
using namespace std;

int main(){

	int tc = 0;
	int N = 0;
	long long arr[101] = { 1, 1, 1, 2, 2, 0, };
	int f_index = 0, s_index = 4;

	for(int j = 6; j <= 100; j++){
		arr[j-1] = arr[f_index]+arr[s_index];
		f_index++;
		s_index++;
	}
	cin >> tc;

	for(int i = 0; i < tc; i++){
		cin >> N;
		cout << arr[N-1] << "\n";
	}
	return 0;
}