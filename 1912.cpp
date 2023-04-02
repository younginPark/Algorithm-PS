#include <iostream>
#define MAX_NUM 100001
using namespace std;

int max(int a, int b){
	return a > b ? a : b;
}

int main(){

	int arr[MAX_NUM] = { 0, };
	int dp[MAX_NUM] = { 0, };
	int result = 0;
	int N = 0;
	cin >> N;
	for(int i = 0; i < N; i++){
		cin >> arr[i];
	}
	dp[0] = arr[0];
	result = dp[0];
	for(int i = 1; i < N; i++){
		dp[i] = max(dp[i-1]+arr[i], arr[i]);
		//cout << dp[i] << " ";
		result = max(result, dp[i]);
	}

	cout << result;

	return 0;
}