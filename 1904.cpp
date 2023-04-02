#include <iostream>
using namespace std;

int main(){

	int a0 = 1;
	int a1 = 2;

	int N;
	int result = 0;
	int first = 0, second = 0;

	cin >> N;

	if(N == 1){
		result = a0 % 15746;
	}
	else if(N == 2){
		result = a1 % 15746;
	}
	else{
		for(int i = 0; i < N; i++){
			if(i == 0){
				first = a0;
			}
			else if(i == 1){
				second = a1;
			}
			else{
				result = (first + second) % 15746;
				first = second;
				second = result;
			}
		}
	}

	cout << result;

	return 0;
}