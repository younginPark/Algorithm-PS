#include <iostream>
using namespace std;
//1000000000
int main(){
	int N;
	long long result = 0;
	long long arr[101][11] = { 0, };
	cin >> N;

	for(int i = 1; i <= 9; i++){
		arr[1][i] = 1;
	}

	for(int i = 2; i <= N; i++){
		for(int j = 0; j <= 9; j++){
			if(j == 0){
				arr[i][j] = arr[i-1][j+1];
			}
			else if(j == 9){
				arr[i][j] = arr[i-1][j-1];
			}
			else{
				arr[i][j] = arr[i-1][j-1] + arr[i-1][j+1];
				arr[i][j] %= 1000000000;
			}
		}
	}

	for(int i = 0; i <= 9; i++){
		result += arr[N][i];
	}

	cout << result % 1000000000;

	return 0;
}