#include <iostream>
#include <cmath>
using namespace std;

int main(){
	int M, N;
	cin >> M >> N;

	bool arr[1000001];
	for(int i = 0; i <= N; i++){
		arr[i] = true;
	}
	arr[0] = false;
	arr[1] = false;
	for(int i = 2; i <= sqrt(N); i++){
		if(arr[i] == false){
			continue;
		}
		for(int j = i+i; j <= N; j+=i){
			arr[j] = false;
		}
	}
	for(int i = M; i <= N; i++){
		if(arr[i] == true){
			cout << i << "\n";
		}
	}

	return 0;
}