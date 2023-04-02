#include <iostream>
#define NUM 8
using namespace std;

int main(){
	int N = 0;
	int result = 0;
	int arr[NUM] = { 0, };
	cin >> N;

	for(int i = 0; i < NUM; i++){
		arr[i] = N % 2;
		N /= 2;
	}

	for(int i = 0; i < NUM; i++){
		if(arr[i] == 1){
			result++;
		}
	}

	cout << result;
	return 0;
}