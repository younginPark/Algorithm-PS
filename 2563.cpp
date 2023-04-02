#include <iostream>
using namespace std;

int main(){
	int num = 0;
	int arr[101][101] = {0, };
	int row = 0, col = 0, col2 = 0;
	int result = 0;

	cin >> num;

	for(int i = 0; i < num; i++){
		cin >> row >> col;

		for(int j = 0; j < 10; j++){
			col2 = col;
			for(int k = 0; k < 10; k++){
				arr[row][col2] = 1;
				col2++;
			}
			row++;
		}
	}

	for(int i = 0; i < 100; i++){
		for(int j = 0; j < 100; j++){
			if(arr[i][j] == 1){
				result++;
			}
		}
	}

	cout << result << "\n";

	return 0;
}