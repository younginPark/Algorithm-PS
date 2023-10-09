#include <iostream>
#include <queue>
#include <string>
using namespace std;

int arr[1001][1001] = { 0, };
int xx[4] = {0,0,-1,1};
int yy[4] = {-1,1,0,0};
int N, M;
queue<pair<pair<pair<int,int>,int>,int > >q;

int bfs(){
	q.push(make_pair(make_pair(make_pair(0,0),1),0));
	arr[0][0] = 5;

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
				if(0<=frontx+xx[i]&&frontx+xx[i]<N && 0<=fronty+yy[i]&&fronty+yy[i]<M){
					if(arr[frontx+xx[i]][fronty+yy[i]] == 0){
						q.push(make_pair(make_pair(make_pair(frontx+xx[i],fronty+yy[i]),cnt+1),breaky));
						arr[frontx+xx[i]][fronty+yy[i]] = 5;
					}
					else if(arr[frontx+xx[i]][fronty+yy[i]] == 1 && breaky == 0){
						q.push(make_pair(make_pair(make_pair(frontx+xx[i],fronty+yy[i]),cnt+1),1));
						arr[frontx+xx[i]][fronty+yy[i]] = 5;
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