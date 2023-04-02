#include <iostream>
using namespace std;

int N, M;
int arr[10] = { 0, };

void func(int cnt){
	if(cnt == M){
		for(int i = 0; i < M; i++){
			cout << arr[i] << " ";
		}
		cout << "\n";
		return;
	}

	for(int i = 1; i <= N; i++){
		arr[cnt] = i;
		func(cnt+1);
	}
}

int main(){
	cin >> N >> M;
	func(0);

	return 0;
}