#include <iostream>
using namespace std;

int main(){
	int arr[101] = { 0, };
	int tot = 0;
	int N, M;
	int max = 0;
	cin >> N >> M;

	for(int i = 0; i < N; i++){
		cin >> arr[i];
	}

	for(int i = 0; i < N-2; i++){
		for(int j = i+1; j < N-1; j++){
			for(int k = j+1; k < N; k++){
				tot = 0;
				tot = arr[i] + arr[j] + arr[k];
				if(max < tot && tot <= M){
					max = tot;
					//cout << arr[i] << " " << arr[j] << " " << arr[k] << "\n";
				}
			}
		}
	}
	cout << max;
	return 0;
}