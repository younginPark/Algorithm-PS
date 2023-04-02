#include <iostream>
#include <queue>
#include <string>
using namespace std;

int arr[1001][1001] = { 0, };
bool visit[2][1001][1001] = { 0, };
int xx[4] = {0,0,-1,1};
int yy[4] = {-1,1,0,0};
int N, M;
queue<pair<pair<pair<int,int>,int>,int > >q;

int bfs(){
	q.push(make_pair(make_pair(make_pair(0,0),1),0));
	arr[0][0] = 5;
	visit[1][0][0] = true;
	visit[0][0][0] = true;

	while(!q.empty()){
		int frontx = q.front().first.first.first;
		int fronty = q.front().first.first.second;
		int cnt = q.front().first.second;
		int breaky = q.front().second;
		q.pop();

		if(frontx == N-1 && fronty == M-1){
			return cnt;
		}
		else{
			for(int i = 0; i < 4; i++){
				int newX = frontx+xx[i];
				int newY = fronty+yy[i];
				if(0 <= newX && newX < N && 0 <= newY && newY < M){
					if(arr[newX][newY] == 1){
						if(breaky == 1){
							continue;
						}
						else{
							if(visit[breaky][newX][newY] == false){
								visit[breaky][newX][newY] = true;
								q.push(make_pair(make_pair(make_pair(newX, newY), cnt+1), 1));
							}
						}
					}
					else{
						if(visit[breaky][newX][newY] == false){
							visit[breaky][newX][newY] = true;
							q.push(make_pair(make_pair(make_pair(newX, newY), cnt+1), breaky));
						}
					}
				}
			}
		}
	}
	return -1;
}

int main(){
	string tmp;
	cin >> N >> M;
	for(int i = 0; i < N; i++){
		cin >> tmp;
		for(int j = 0; j < M; j++){
			arr[i][j] = tmp[j] - '0';
		}
	}

	int result = bfs();

	cout << result;
	return 0;
}