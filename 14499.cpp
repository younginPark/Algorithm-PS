#include <iostream>
using namespace std;

void dice_change(int dir, int dice[]){ 
	int tmp1, tmp2, tmp3, tmp4;

	if(dir == 1){ //동
		tmp1 = dice[1];
		tmp2 = dice[3];
		tmp3 = dice[4];
		tmp4 = dice[6];

		dice[3] = tmp1;
		dice[6] = tmp2;
		dice[1] = tmp3;
		dice[4] = tmp4;
	}
	else if(dir == 2){ //서
		tmp1 = dice[1];
		tmp2 = dice[3];
		tmp3 = dice[4];
		tmp4 = dice[6];

		dice[4] = tmp1;
		dice[1] = tmp2;
		dice[6] = tmp3;
		dice[3] = tmp4;
	}
	else if(dir == 3){ //북
 		tmp1 = dice[1];
		tmp2 = dice[2];
		tmp3 = dice[5];
		tmp4 = dice[6];

		dice[2] = tmp1;
		dice[6] = tmp2;
		dice[1] = tmp3;
		dice[5] = tmp4;
		
	}
	else if(dir == 4){ //남
		tmp1 = dice[1];
		tmp2 = dice[2];
		tmp3 = dice[5];
		tmp4 = dice[6];

		dice[5] = tmp1;
		dice[1] = tmp2;
		dice[6] = tmp3;
		dice[2] = tmp4;
		
	}
	
}


int main(){

	int map[21][21] = { 0, };
	int col = 0, row = 0;
	int nowX = 0, nowY = 0;
	int num = 0;
	int dir[1001] = {0, };
	int now = 0; //지금 지도위치 숫자
	int dice[8] = {0,};

	cin >> row >> col >> nowX >> nowY >> num;

	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			cin >> map[i][j];
		}
	}

	for(int i = 0; i < num; i++){
		cin >> dir[i];
	}


	for(int i = 0; i < num; i++){
		if(dir[i] == 1){
			if(0 <= nowY+1 && nowY+1 <= col-1){
				dice_change(dir[i], dice);
				nowY += 1;
				//cout << "현재 주사위 윗면 : " << dice[1] << "\n" <<" 현재 위치 : (" << nowX << "," << nowY  << ") 숫자: " << map[nowX][nowY] << "\n";
				now = map[nowX][nowY];
				if(now == 0){
					map[nowX][nowY] = dice[6]; //인덱스기준
				}
				else{
					dice[6] = map[nowX][nowY];
					map[nowX][nowY] = 0;
				}
				cout <<dice[1] <<"\n";
			}
			else{
				continue;
			}	

		}
		else if(dir[i] == 2){
			if(0 <= nowY-1 && nowY-1 <= col-1){
				dice_change(dir[i], dice);
				nowY -= 1;
				//cout << "현재 주사위 윗면 : " << dice[1] << "\n" <<" 현재 위치 : (" << nowX << "," << nowY  << ") 숫자: " << map[nowX][nowY] << "\n";
				now = map[nowX][nowY];
				if(now == 0){
					map[nowX][nowY] = dice[6]; //인덱스기준
				}
				else{
					dice[6] = map[nowX][nowY];
					map[nowX][nowY] = 0;
				}
				cout <<dice[1] <<"\n";
			}
			else{
				continue;
			}
			
		}
		else if(dir[i] == 4){
			if(0 <= nowX+1 && nowX+1 <= row-1){
				dice_change(dir[i], dice);
				nowX += 1;
				//cout << "현재 주사위 윗면 : " << dice[1] << "\n" <<" 현재 위치 : (" << nowX << "," << nowY  << ") 숫자: " << map[nowX][nowY] << "\n";
				now = map[nowX][nowY];
				if(now == 0){
					map[nowX][nowY] = dice[6]; //인덱스기준
				}
				else{
					dice[6] = map[nowX][nowY];
					map[nowX][nowY] = 0;
				}
				cout <<dice[1] <<"\n";
			}
			else{
				continue;
			}
			
		}
		else if(dir[i] == 3){
			if(0 <= nowX-1 && nowX-1 <= row-1){
				dice_change(dir[i], dice);
				nowX -= 1;
				//cout << "현재 주사위 윗면 : " << dice[1] << "\n" <<" 현재 위치 : ("<< nowX << "," << nowY  << ") 숫자: " << map[nowX][nowY] << "\n";
				now = map[nowX][nowY];
				if(now == 0){
					map[nowX][nowY] = dice[6]; //인덱스기준
				}
				else{
					dice[6] = map[nowX][nowY];
					map[nowX][nowY] = 0;
				}
				cout <<dice[1] <<"\n";
			}
			else{
				continue;
			}
		}
	}
	return 0;
}