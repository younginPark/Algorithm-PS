#include <iostream>
using namespace std;


int main(){

	int num = 0;
	int arr[10000][7] = {0, };
	int student[10000][7] = {0, };
	int stuarr[10000] = {0, };
	int max = 0;
	int result = 0;

	cin >> num;
	for(int i = 0; i < num; i++){
		for(int j = 0; j < 5; j++){
			cin >> arr[i][j];
		}
	}

	for(int i = 0; i < num; i++){//고정학생 순번
		for(int j = 0; j < 5; j++){ //학년
			for(int k = 0; k < num; k++){ //고정학생 포함 비교 학생 순서
				if(arr[i][j] == arr[k][j]){
					student[i][k] = 1;
				}
			}
		}
	}

	for(int i = 0; i < num; i++){
		stuarr[i] = 0;
		for(int j = 0; j < 5; j++){
			if(student[i][j] == 1){
				stuarr[i]++;
			}
		}
	}

	max = stuarr[0];
	for(int i = 0; i < num; i++){
		if(stuarr[i] > max){
			max = stuarr[i];
			result = i;
		}
	}

	cout << result+1;



	return 0;
}























