#include <iostream>
#define MAX_COIN 101
#define MAX_PRICE 10001
using namespace std;

int main(){

	int arr[MAX_COIN] = { 0, };
	int dp[MAX_PRICE] = { 0, };
	int N, total;
	cin >> N >> total;

	for(int i = 1; i <= N; i++){
		cin >> arr[i];
	}
	dp[0] = 1;
	for(int i = 1; i <= N; i++){
		for(int j = 0; j <= total; j++){
			if(arr[i] <= j){
				dp[j] += dp[j-arr[i]];
			}
		}
	}

	cout << dp[total];

	return 0;
}