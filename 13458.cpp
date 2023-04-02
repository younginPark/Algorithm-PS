#include <iostream>
using namespace std;

int main(){

	int N;
	int arr[1000001] = { 0, };
	int ans[1000001] = { 0, };
	long long total = 0;
	int B, C;

	cin >> N;
	for(int i = 0; i < N; i++){
		cin >> arr[i];
	}
	cin >> B >> C;

	for(int i = 0; i < N; i++){
		arr[i] -= B; //총 감독 수 만큼 빼주기
	}

	for(int i = 0; i < N; i++){
		if(arr[i] > 0){
			if((arr[i] % C) > 0){
				ans[i] = (arr[i] / C) + 1;
			}
			else{
				ans[i] = arr[i] / C;
			}
		}
	}

	for(int i = 0; i < N; i++){
		total += (ans[i] + 1);
	}
	cout << total << "\n";
	return 0;
}