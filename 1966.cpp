#include <iostream>
#include <queue>
using namespace std;

int main(){
	int tc = 0;
	int N = 0, who = 0;
	int cnt = 0;

	cin >> tc;
	for(int t = 0; t < tc; t++){
		cnt = 0;
		queue <pair<int,int> > q;
		priority_queue<int> pq;
		cin >> N >> who;
		for(int i = 0; i < N; i++){
			int tmp = 0;
			cin >> tmp;
			q.push(make_pair(tmp, i));
			pq.push(tmp);
		}
		while(!q.empty()){
			int now = q.front().first;
			int idx = q.front().second;
			q.pop();
			if(pq.top() == now){
				pq.pop();
				cnt++;
				if(idx == who){
					cout << cnt << "\n";
					break;
				}
			}
			else{
				q.push(make_pair(now, idx));
			}
		}

	}

	return 0;
}