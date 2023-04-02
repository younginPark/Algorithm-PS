#include <iostream>
using namespace std;

int main(){

	int arr[15][15] = {0, };
	int now = 0;

	for(int i = 0; i < 15; i++){
		for(int j = 1; j < 15; j++){
			if(i == 0){
				arr[i][j] = j;
			}
			else{
				for(int k = 1; k <= j; k++){
					now += arr[i-1][k];
				}
				arr[i][j] = now;
				now = 0;
			}
		}
	}

	int tc = 0;
	int k, n;
	cin >> tc;
	for(int i = 0; i < tc; i++){
		cin >> k >> n;
		cout << arr[k][n] << "\n";
	}

	return 0;
}