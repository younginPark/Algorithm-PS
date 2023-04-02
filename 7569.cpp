#include <iostream>
#include <queue>
using namespace std;

int N, M, H;
int arr[101][101][101];
int xx[4] = {0,0,1,-1};
int yy[4] = {1,-1,0,0};

queue<pair<pair<pair<int, int>, int>, int> > q; //x y h cnt

int bfs(){
	int cnt = 0;
	int nx, ny;
	while(!q.empty()){
		int frontx = q.front().first.first.first;
		int fronty = q.front().first.first.second;
		int fronth = q.front().first.second;
		//cout << fronth << "," << frontx << "," << fronty << "\n";
		cnt = q.front().second;
		q.pop();

		//4방향
		for(int i = 0; i < 4; i++){
			nx = frontx + xx[i];
			ny = fronty + yy[i];

			if(nx < 0 || ny < 0 || nx >= N || ny >= M){
				continue;
			}
			if(arr[fronth][nx][ny] == 0){
				q.push(make_pair(make_pair(make_pair(nx,ny),fronth),cnt+1));
				arr[fronth][nx][ny] = 1;
			}

		}
		//윗층
		if(fronth > 0 && arr[fronth-1][frontx][fronty] == 0){
				q.push(make_pair(make_pair(make_pair(frontx,fronty),fronth-1),cnt+1));
				arr[fronth-1][frontx][fronty] = 1;
		}
		//아랫층
		if(fronth+1 < H && arr[fronth+1][frontx][fronty] == 0){
				q.push(make_pair(make_pair(make_pair(frontx,fronty),fronth+1),cnt+1));
				arr[fronth+1][frontx][fronty] = 1;
		}

	}

	return cnt;
}


int main(){
	cin >> M >> N >> H;
	int result = 0;
	for(int i = 0; i < H; i++){
		for(int j = 0; j < N; j++){
			for(int k = 0; k < M; k++){
				cin >> arr[i][j][k];
				if(arr[i][j][k] == 1){
					q.push(make_pair(make_pair(make_pair(j,k),i),0));
				}
			}
		}
	}

	result = bfs();

	for(int i = 0; i < H; i++){
		for(int j = 0; j < N; j++){
			for(int k = 0; k < M; k++){
				if(arr[i][j][k] == 0){
					result = -1;
				}
			}
		}
	}

	cout << result;

	return 0;
}