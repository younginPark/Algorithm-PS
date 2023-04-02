#include <iostream>
using namespace std;

int arr[101][101] = {0, };
bool visit[101] = { false, };
int N, M;
int cnt = 0;

void dfs(int s){
	visit[s] = true;

	for(int i = 1; i <= N; i++){
		if(arr[s][i] == 1 && visit[i] == false){
			cnt++;
			//cout << "!" << s << " , " << i << "\n";
			dfs(i);
		}
	}
}

int main(){

	int src, dst;
	cin >> N >> M;

	for(int i = 0; i < M; i++){
		cin >> src >> dst;
		arr[src][dst] = 1;
		arr[dst][src] = 1;
	}

	dfs(1);
	cout << cnt;

	return 0;
}