#include <iostream>
#include <algorithm>
using namespace std;

int min(int a, int b){
	return a < b ? a : b;
}

int main(){

	int N;
	int color[1001][3];
	int dp[1001][3];
	int last[3];
	cin >> N;
	for(int i = 0; i < N; i++){
		cin >> color[i][0] >> color[i][1] >> color[i][2];
	}

	dp[0][0] = color[0][0];
	dp[0][1] = color[0][1];
	dp[0][2] = color[0][2];

	for(int i = 1; i < N; i++){
		dp[i][0] = min(dp[i-1][1], dp[i-1][2]) + color[i][0];
		dp[i][1] = min(dp[i-1][0], dp[i-1][2]) + color[i][1];
		dp[i][2] = min(dp[i-1][0], dp[i-1][1]) + color[i][2];
	}

	for(int i = 0; i < 3; i++){
		last[i] = dp[N-1][i];
		//cout << last[i] << " ";
	}
	//cout << "\n";

	sort(last, last+3);
	cout << last[0];

	return 0;
}