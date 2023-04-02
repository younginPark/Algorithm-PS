#include <iostream>
using namespace std;

int main(){
	int num = 0;
	int board[101][101] = {0, };
	int x[21], y[21] = 0;
	int start[21] = 0, gen[21] = {0, };
	int now = 0, nowx = 0, nowy = 0;
	int result = 0;

	cin >> num;
	for(int i = 0; i < num; i++){
		cin >> x[i] >> y[i] >> start[i] >> gen[i];
	}

	for(int i = 0; i < num; i++){
		now = start[i];
		nowx = x[i]; nowy = y[i];
		board[nowx][nowy] = 1
		for(int j = 0; j < gen[i]; j++){
			
			if(now == 0){
				nowx++;
				board[nowx][nowy] = 1;
				now = 3;
			}
			else if(now == 1){
				nowy--;
				board[nowx][nowy] = 1;
				now = 0;
			}
			else if(now == 2){
				nowx--;
				board[nowx][nowy] = 1;
				now = 1;
			}
			else if(now == 3){
				nowy++;
				board[nowx][nowy] = 1;
				now = 2;
			}
		}
	}
	for(int i = 0; i < 100; i++){
		for(int j = 0; j < 100; j++){
			if(board[i][j] == 1){
				result++;
			}
			else{
				continue;
			}
		}
	}

	cout << result;
	return 0;
}