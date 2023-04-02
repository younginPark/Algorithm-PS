#include <iostream>
#include <queue>
using namespace std;

int arr[1001][1001] = {0, };
bool visit[1001] = { false, };
int N ,M ,V;

void init(){
	for(int i = 0; i <= 1000; i++){
		visit[i] = false;
	}
}

void dfs(int s){

	cout << s << " ";
	visit[s] = true;

	for(int i = 1; i <= N; i++){
		if(arr[s][i] && !visit[i]){
			dfs(i);
		}
	}
}

void bfs(int s){
	queue<int> q;

	q.push(s);
	visit[s] = true;

	while(!q.empty()){
		int front = q.front();
		visit[front] = true;
		cout << front << " ";
		q.pop();

		for(int i = 1; i <= N; i++){
			if(arr[front][i] && !visit[i]){
				visit[i] = true;
				q.push(i);
			}
		}
	}

}


int main(){

	int src, dst;
	cin >> N >> M >> V;

	for(int i = 0; i < M; i++){
		cin >> src >> dst;
		arr[src][dst] = 1;
		arr[dst][src] = 1;
	}

	dfs(V);
	cout << "\n";

	init();
	bfs(V);

	return 0;
}