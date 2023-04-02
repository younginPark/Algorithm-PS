#include <iostream>
using namespace std;

int N, M;
int arr[9] = { 0, };
int visit[9] = { false, };
//int check[9] = { false, };

void func(int cnt, int start){
	if(cnt == M){
		for(int i = 0; i < M; i++){
			cout << arr[i] << " ";
		}
		cout << "\n";
		return;
	}

	for(int i = start; i <= N; i++){
		arr[cnt] = i;
		func(cnt+1, i);
	}
}

int main(){
	cin >> N >> M;
	func(0, 1);
	return 0;
}