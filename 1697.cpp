#include <iostream>
#include <queue>
using namespace std;

int N,K;
int arr[100001] = { 0, };
queue<pair<int,int> > q;

void bfs(){
	int cnt = 0;

	while(!q.empty()){
		int now = q.front().first;
		cnt = q.front().second;
		//cout << now << " ";
		q.pop();

		if(now == K){
			break;
		}
		else{
			if(now-1 >= 0 && arr[now-1] == 0){
				q.push(make_pair(now-1, cnt+1));
				arr[now-1] = 1;
			}
			if(now+1 <= 100000 && arr[now+1] == 0){
				q.push(make_pair(now+1, cnt+1));
				arr[now+1] = 1;
			}
			if(now*2 <= 100000 && arr[now*2] == 0){
				q.push(make_pair(now*2, cnt+1));
				arr[now*2] = 1;
			}
		}
	}

	cout << cnt;
}

int main(){
	cin >> N >> K;
	q.push(make_pair(N,0));
	arr[N] = 1;
	bfs();
	return 0;
}