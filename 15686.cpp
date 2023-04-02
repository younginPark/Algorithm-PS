#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int N, M;
int map[51][51] = { 0, };
int chik_now = 0;
int result = 99999;

int check(){
	int home_x = 0, home_y = 0;
	int ret = 0;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(map[i][j] == 1){
				home_y = i; home_x = j;
				int find = 99999;
				for(int k = 0; k < N; k++){
					for(int h = 0; h < N; h++){
						if(map[k][h] == 2){
							find = min(find, abs(k - home_y) + abs(h - home_x));
						}
					}
				}
				ret += find;
			}
		}
	}
	return ret;
}

void dfs(int cnt, int y, int x){
	//cout << "cnt: " << cnt << "\n";
	if(cnt == M){
		int tmp = check();
		//cout << "delete: " << y << ", " << x << "\n";
		//cout << tmp << "\n";
		result = min(result, tmp);
		return;
	}
	else if(cnt > M){
		// if(cnt == 4){
		// 	cout << "y, x: " << y << "," << x << "\n"; 
		// 	for(int i = 0; i < N; i++){
		// 		for(int j = 0; j < N; j++){
		// 			cout << map[i][j] << " ";
		// 		}
		// 		cout << "\n";
		// 	}
		// 	cout << "\n";
		// }
		for(int i = y; i < N; i++){
			for(int j = 0; j < N; j++){
				if(map[i][j] == 2){
					map[i][j] = 0;
					dfs(cnt-1, i, j);
					map[i][j] = 2;
				}
			}
		}
	}
}

int main(){
	cin >> N >> M;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			cin >> map[i][j];
			if(map[i][j] == 2){
				chik_now++;
			}
		}
	}
	//cout << "chik_now: " << chik_now << "\n";
	dfs(chik_now, 0, 0);
	cout << result;

	return 0;
}