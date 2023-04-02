#include <iostream>
using namespace std;

struct CCTV
{
	int type, y, x;
};

int map[9][9];
int N, M, ret;
int cctv_size = 0;
CCTV cctv[9];
int rot_size[6] = { 4, 2, 4, 4, 1};

void map_copy(int src[9][9], int dest[9][9]){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			dest[i][j] = src[i][j];
		}
	}
}

void update(int dir, CCTV cctv){
	dir = (dir % 4);

	if(dir == 0){
		for(int x = cctv.x + 1; x < M; x++){
			if(map[cctv.y][x] == 6){
				break;
			}
			map[cctv.y][x] = -1;
		}
	}
	if(dir == 1){
		for(int y = cctv.y + 1; y < N; y++){
			if(map[y][cctv.x] == 6){
				break;
			}
			map[y][cctv.x] = -1;
		}
	}
	if(dir == 2){
		for(int x = cctv.x - 1; x >= 0; x--){
			if(map[cctv.y][x] == 6){
				break;
			}
			map[cctv.y][x] = -1;
		}
	}
	if(dir == 3){
		for(int y = cctv.y - 1; y >= 0; y--){
			if(map[y][cctv.x] == 6){
				break;
			}
			map[y][cctv.x] = -1;
		}
	}
}

void dfs(int cctv_idx){
	if(cctv_idx == cctv_size){
		int cnt = 0;
		for(int y = 0; y < N; y++){
			for(int x = 0; x < M; x++){
				if(map[y][x] == 0){
					cnt++;
				}
			}
		}
		if(cnt < ret){
			ret = cnt;
		}
		return;
	}

	int backup[9][9];
	int type = cctv[cctv_idx].type;
	for(int dir = 0; dir < rot_size[type]; dir++){
		map_copy(map, backup);
		if(type == 0){
			update(dir, cctv[cctv_idx]);
		}
		else if(type == 1){
			update(dir, cctv[cctv_idx]);
			update(dir+2, cctv[cctv_idx]);
		}
		else if(type == 2){
			update(dir, cctv[cctv_idx]);
			update(dir+1, cctv[cctv_idx]);
		}
		else if(type == 3){
			update(dir, cctv[cctv_idx]);
			update(dir+1, cctv[cctv_idx]);
			update(dir+2, cctv[cctv_idx]);
		}
		else if(type == 4){
			update(dir, cctv[cctv_idx]);
			update(dir+1, cctv[cctv_idx]);
			update(dir+2, cctv[cctv_idx]);
			update(dir+3, cctv[cctv_idx]);
		}
		dfs(cctv_idx+1);
		map_copy(backup, map);
	}
}

int main(){

	cin >> N >> M;
	for(int y = 0; y < N; y++){
		for(int x = 0; x < M; x++){
			cin >> map[y][x];
			if(map[y][x] != 0 && map[y][x] != 6){
				cctv[cctv_size].type = map[y][x] - 1;
				cctv[cctv_size].y = y;
				cctv[cctv_size].x = x;
				cctv_size++;
			}
		}
	}

	ret = 100;
	dfs(0);
	cout << ret;
	return 0;
}