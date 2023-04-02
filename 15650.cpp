#include <iostream>
using namespace std;

int N, M;
int arr[9] = { 0, };
bool visit[9][9];

void func(int cnt, int start){
	if(cnt == M){
		for(int i = 0; i < M; i++){
			cout << arr[i] << " ";
		}
		cout << "\n";
	}

	for(int i = start; i <= N; i++){
		arr[cnt] = i;
		func(cnt+1, i+1);
	}
}

int main(){

	cin >> N >> M;
	func(0, 1);

	return 0;
}

//cnt는 index역할, 
//start는 시작하는 수로 재귀로 +1 해가면서 함수호출 하니까 
//현재 start보다 큰 수만 들어감