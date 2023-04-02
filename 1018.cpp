#include <iostream>
#include <string>
using namespace std;

int N, M;
char arr[51][51] = { 0, };

int main(){
	
	string tmp;
	int min = 3000;
	int bet = 0;
	int cntW = 0, cntB = 0;
	cin >> N >> M;
	for(int i = 0; i < N; i++){
		cin >> tmp;
		for(int j = 0; j < M; j++){
			arr[i][j] = tmp[j];
		}
	}

	for(int i = 0; i < N-7; i++){
		for(int j = 0; j < M-7; j++){
			cntW = 0, cntB = 0;
			for(int k = i; k <= i+7; k++){
				for(int h = j; h <= j+7; h++){
					if((k+h) % 2 == 0 && arr[k][h] == 'B'){
						cntW++;
					}
					else if((k+h) % 2 == 1 && arr[k][h] == 'W'){
						cntW++;
					}
					
					if((k+h) % 2 == 0 && arr[k][h] == 'W'){
						cntB++;
					}
					else if((k+h) % 2 == 1 && arr[k][h] == 'B'){
						cntB++;
					}
				}
			}
			if(cntB > cntW){
				bet = cntW;
			}
			else{
				bet = cntB;
			}
			if(min > bet){
				min = bet;
			}
		}
	}
	cout << min;

	return 0;
}