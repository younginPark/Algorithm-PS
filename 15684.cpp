#include <iostream>
using namespace std;

int N, M, H;
int arr[31][11];
int a, b;
int ret;

bool check(){
	bool result = true;

	for(int i = 1; i <= N; i++){
		int pos = i;
		for(int j = 1; j <= H; j++){
			if(arr[j][pos] == 1){
				pos++;
			}
			else if(arr[j][pos-1] == 1){
				pos--;
			}
		}
		if(pos != i){
			result = false;
			return result;
		}
	}
	return result;
}

void dfs(int cnt, int y, int x){
	if(cnt >= ret){
		return;
	}
	if(check()){
		ret = cnt;
		return;
	}
	if(cnt == 3){
		return;
	}

	for(int i = y; i <= H; i++){
		for(int j = x; j < N; j++){
			if(arr[i][j] == 0 && arr[i][j-1] == 0 && arr[i][j+1] == 0){
				arr[i][j] = 1;
				dfs(cnt+1, i, j);
				arr[i][j] = 0;
			}
		}
		x = 1;
	}
}

int main(){
	cin >> N >> M >> H;
	for(int i = 0; i < M; i++){
		cin >> a >> b;
		arr[a][b] = 1;
	}
	ret = 4;
	dfs(0, 1, 1);

	if(ret == 4){
		ret = -1;
	}

	cout << ret;
	return 0;
}