#include <iostream>
#define MAX_NUM 501
using namespace std;

int min(int a, int b){
	return a > b ? b : a;
}

int main(){

	int tc = 0;
	int N = 0;
	int arr[MAX_NUM] = { 0, };
	int sum[MAX_NUM] = { 0, };
	int dp[MAX_NUM][MAX_NUM] = { 0, };

	cin >> tc;
	for(int p = 0; p < tc; p++){
		cin >> N;
		for(int i = 1; i <= N; i++){
			cin >> arr[i];
			sum[i] = sum[i-1] + arr[i];
		}

		for(int i = 2; i <= N; i++){
			for(int j = i-1; j > 0; j--){
				dp[j][i] = 10000000;
				for(int k = j; k <= i; k++){
					dp[j][i] = min(dp[j][i], dp[j][k] + dp[k+1][i]);
				}
				dp[j][i] += sum[i] - sum[j-1];
			}
		}
		cout << dp[1][N] << "\n";
	}
	return 0;
}