#include <iostream>
#include <algorithm>
using namespace std;

int maax(int a, int b){
	return a > b ? a : b;
}

int main(){

	int N;
	int dp[501][501] = { 0, };
	int last[501] = { 0, };
	int max = 0;
	cin >> N;
	for(int i = 1; i <= N; i++){
		for(int j = 1; j <= i; j++){
			cin >> dp[i][j];
			if(j == 1){
				dp[i][j] = dp[i-1][j] + dp[i][j];
			}
			else if(j == i){
				dp[i][j] = dp[i-1][j-1] + dp[i][j];
			}
			else{
				dp[i][j] = maax(dp[i-1][j-1], dp[i-1][j]) + dp[i][j];
			}
		}
	}

	for(int i = 0; i < N; i++){
		last[i] = dp[N][i+1];
	}

	sort(last, last+N);

	cout << last[N-1];
	return 0;
}