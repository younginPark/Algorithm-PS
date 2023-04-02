#include <iostream>
#include <queue>
using namespace std;

int N,M;
int arr[1001][1001];
int xx[5] = {0, 0, -1, 1};
int yy[5] = {-1, 1, 0, 0};
queue<pair<pair<int,int>, int> > q;

int bfs(){
	int cnt;

	while(!q.empty()){
		int frontx = q.front().first.first;
		int fronty = q.front().first.second;
		cnt = q.front().second;
		q.pop();

		for(int i = 0; i < 4; i++){
			int nx = frontx+xx[i];
			int ny = fronty+yy[i];
			if(nx < 0 || nx >= N || ny < 0 || ny >= M){
				continue;
			}
			if(arr[nx][ny] == 0){
				q.push(make_pair(make_pair(nx,ny),cnt+1));
				arr[nx][ny] = 1;
			}
		}
	}
	return cnt;
}

int main(){
	int result = 0;

	cin >> M >> N;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			cin >> arr[i][j];
		}
	}
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			if(arr[i][j] == 1){
				q.push(make_pair(make_pair(i,j),0));
			}
		}
	}
	result = bfs();

	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			if(arr[i][j] == 0){
				result = -1;
			}
		}
	}
	cout << result;
	return 0;
}