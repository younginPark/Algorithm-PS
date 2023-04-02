#include <iostream>
#define MAX_RC 21
using namespace std;

int yy[5] = { 0, 0, 0, -1, 1};//0 동 서 북 남
int xx[5] = { 0, 1, -1, 0, 0};
int y = 0, x = 0;
int r = 0, c = 0;
int arr[MAX_RC][MAX_RC] = { 0, };
int dice[7] = { 0, };
int doit[1001] = { 0, };

void change(int a){
	int copy[7] = { 0, };
	for(int i = 0; i < 6; i++){
		copy[i] = dice[i];
	}
	int newX = x+xx[a];
	int newY = y+yy[a];
	if(0 <= newY && newY < r && 0 <= newX && newX < c){
		x = newX;
		y = newY;
		if(a == 1){//동
			dice[0] = copy[3];
			dice[2] = copy[0];
			dice[3] = copy[5];
			dice[5] = copy[2];
		}
		else if(a == 2){//서
			dice[0] = copy[2];
			dice[2] = copy[5];
			dice[3] = copy[0];
			dice[5] = copy[3];
		}
		else if(a == 3){//북
			dice[0] = copy[4];
			dice[1] = copy[0];
			dice[4] = copy[5];
			dice[5] = copy[1];
		}
		else if(a == 4){//남
			dice[0] = copy[1];
			dice[1] = copy[5];
			dice[4] = copy[0];
			dice[5] = copy[4];
		}

		if(arr[y][x] == 0){
			arr[y][x] = dice[5];
		}
		else if(arr[y][x] != 0){
			dice[5] = arr[y][x];
			arr[y][x] = 0;
		}

		cout << dice[0] << "\n";
	}
}

int main(){

	int num = 0; //명령 갯수

	cin >> r >> c >> y >> x >> num;
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			cin >> arr[i][j];
		}
	}
	for(int i = 0; i < num; i++){
		cin >> doit[i];
	}

	for(int i = 0; i < num; i++){
		int dir = doit[i];
		change(dir);
	}

	return 0;
}