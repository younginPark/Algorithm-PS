#include <iostream>
#include <cmath>
#define MAX_NUM 101
using namespace std;

bool make_road_poss(int arr[][MAX_NUM], int y, int x, int L){
	int num = arr[y][x+1];
	for(int i = x+1; i < x+1+L; i++){
		if(arr[y][i] != num){
			return false;
		}
	}
	return true;
}

int count_road(int arr[][MAX_NUM], int N, int L){
	int result_num = 0;

	for(int i = 0; i < N; i++){
		int conti = 1;
		bool can_road = true;
		for(int j = 0; j < N-1; j++){
			if(arr[i][j] == arr[i][j+1]){
				conti++;
			}
			else if(arr[i][j] + 1 == arr[i][j+1]){ //다음꺼가 더 크면 지금 평평한것까지의 길이가 L이상인지 확인
				if(conti >= L){
					conti = 1;
				}
				else{
					can_road = false; //차이는 나는데 경사로 못두니까 false
					break;
				}
			}
			else if(arr[i][j] == arr[i][j+1] + 1){ //이전꺼가 더 크면
				if(make_road_poss(arr, i, j, L) == true){
					j = j + L - 1;
					conti = 0;
				}
				else{
					can_road = false;
					break;
				}
			}
			else if(abs(arr[i][j] - arr[i][j+1]) >= 2){
				can_road = false;
				break;
			}
		}
		if(can_road == true){
			result_num++;
		}
	}
	//cout << result_num << "\n";
	return result_num;
}

int main(){

	int N, L;
	int arr[MAX_NUM][MAX_NUM] = { 0, };
	int arr2[MAX_NUM][MAX_NUM] = { 0, };
	int result = 0;

	cin >> N >> L;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			cin >> arr[i][j];
			arr2[j][i] = arr[i][j];
		}
	}

	int a = count_road(arr, N, L);
	int b = count_road(arr2, N, L);
	result = a+b;
	cout << result;

	return 0;
}