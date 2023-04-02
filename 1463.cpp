#include <iostream>
#define MAX_NUM 1000002
using namespace std;

int main(){

	int arr[MAX_NUM];
	int N = 0;
	for(int i = 0; i <= 1000000; i++){
		arr[i] = 999999;
	}
	arr[0] = 0;
	arr[1] = 0;
	cin >> N;
	for(int i = 1; i <= 1000000; i++){
		if((i*2 <= 1000000) && arr[i*2] > arr[i]+1){
			arr[i*2] = arr[i]+1;
		}
		if((i*3 <= 1000000) && arr[i*3] > arr[i]+1){
			arr[i*3] = arr[i]+1;
		}
		if((i+1 <= 1000000) && arr[i+1] > arr[i]+1){
			arr[i+1] = arr[i]+1;
		}
	}
	cout << arr[N];



	return 0;
}