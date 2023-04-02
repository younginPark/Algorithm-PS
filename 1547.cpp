#include <iostream>
using namespace std;

int main(){
	int M = 0;
	int num1, num2;
	int tmp;
	int arr[4] = { 0, 1, 2, 3};

	cin >> M;
	for(int i = 0; i < M; i++){
		cin >> num1 >> num2;
		tmp = arr[num1];
		arr[num1] = arr[num2];
		arr[num2] = tmp;
	}
	for(int i = 1; i <= 3; i++){
		if(arr[i] == 1){
			cout << i << "\n";
			break;
		}
	}

	return 0;
}