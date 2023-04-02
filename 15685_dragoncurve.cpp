#include <iostream>
#include <cmath>
using namespace std;

int main(){
	int num = 0;
	int x[21], y[21], dir[21], gen[21];
	int draw[1026], copy[1026];
	int board[101][101];
	int tmp = 0;
	int nowx = 0, nowy = 0, now = 0;
	int result = 0;

	cin >> num;
	for(int i = 0; i < num; i++){
		cin >> x[i] >> y[i] >> dir[i] >> gen[i];
	}//입력끝

	for(int i = 0; i < num; i++){
		for(int j = 0; j < pow(2,gen[i]); j++){
			if(j == 0){
				draw[j] = dir[i];
			}
			else{
				//일단 카피
				for(int k = 0; k < pow(2, j-1); k++){
					copy[k] = draw[k];
				}
				tmp = pow(2,j)/2;
				for(int k = 0; k < (pow(2,j)/2); k++){
					draw[tmp+k] = (copy[tmp - k - 1]+1) % 4;
				}

			}
		}

		nowx = x[i], nowy = y[i], now = dir[i];
		board[nowx][nowy] = 1;
		for(int j = 0; j < pow(2,gen[i]); j++){
			if(draw[j] == 0){
				nowx++;
				board[nowx][nowy] = 1;
			}
			else if(draw[j] == 1){
				nowy--;
				board[nowx][nowy] = 1;
			}
			else if(draw[j] == 2){
				nowx--;
				board[nowx][nowy] = 1;
			}
			else if(draw[j] == 3){
				nowy++;
				board[nowx][nowy] = 1;
			}
		}
	}
	for(int i = 0; i < 99; i++){
		for(int j = 0; j < 99; j++){
			if(board[i][j] == 1 && board[i+1][j] == 1 &&board[i][j+1] == 1 && board[i+1][j+1] == 1){
				result++;
			}
		}
	}
	cout << result;

	return 0;
}