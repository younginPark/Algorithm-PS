#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

int N,M;
int arr[101][101] = { 0, };
int result = 0;

void bfs(){
	queue< pair<pair<int,int>, int > > q;
	q.push(make_pair(make_pair(0,0), 1));
	arr[0][0] = 5;

	while(!q.empty()){

		int frontx = q.front().first.first;
		int fronty = q.front().first.second;
		int cnt = q.front().second;
		//cout << frontx << ", " << fronty << "\n";
		q.pop();

		if(frontx == N-1 && fronty == M-1){
			cout << cnt;
			break;
		}
		else{
			if(frontx > 0 && arr[frontx-1][fronty] == 1){
				q.push(make_pair(make_pair(frontx-1, fronty),cnt+1));
				arr[frontx-1][fronty] = 5;
			}
			if(fronty > 0 && arr[frontx][fronty-1] == 1){
				q.push(make_pair(make_pair(frontx, fronty-1),cnt+1));
				arr[frontx][fronty-1] = 5;
			}
			if(frontx + 1 < N && arr[frontx+1][fronty] == 1){
				q.push(make_pair(make_pair(frontx+1, fronty),cnt+1));
				arr[frontx+1][fronty] = 5;
			}
			if(fronty + 1 < M && arr[frontx][fronty+1] == 1){
				q.push(make_pair(make_pair(frontx, fronty+1),cnt+1));
				arr[frontx][fronty+1] = 5;
			}
		}
	} 
}

int main(){

	string tmp;
	int stop = 0;
	cin >> N >> M;

	for(int i = 0; i < N; i++){
		cin >> tmp;
		for(int j = 0; j < M; j++){
			arr[i][j] = tmp[j] - '0';
		}
	}

	bfs();

	

	return 0;

}