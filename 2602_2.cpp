#include <iostream>
using namespace std;

int C, N;
int ans = 0;
int arr[101][101] = { 0, };
bool visit[101] = { false, };

void dfs(int s){
	visit[s] = true;
	for(int i = 1; i <= C; i++){
		if(arr[s][i] && !visit[i]){
			ans++;
			dfs(i);
		}
	}
}

int main(){
	scanf("%d %d", &C, &N);
	for(int i = 0; i < N; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		arr[a][b] = 1;
		arr[b][a] = 1;
	}

	dfs(1);
	printf("%d", ans);
	return 0;
}