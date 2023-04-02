#include <iostream>
#define MAX_NUM 10001
using namespace std;

int max2(int a, int b){
	return a > b ? a : b;
}
int max3(int a, int b, int c){
	int result = 0;
	if(a > b){
		if(c > a){
			result = c;
		}
		else{
			result = a;
		}
	}
	else{
		if(c > b){
			result = c;
		}
		else{
			result = b;
		}
	}

	return result;
}

int main(){
	int arr[MAX_NUM] = { 0, };
	int dp[MAX_NUM] = { 0, };
	int N = 0;
	int maxx = 0;

	cin >> N;
	for(int i = 1; i <= N; i++){
		cin >> arr[i];
	}
	dp[1] = arr[1];
	dp[2] = arr[1]+ arr[2];
	for(int i = 3; i <= N; i++){
		dp[i] = max3(dp[i-3] + arr[i-1] + arr[i], dp[i-1] ,dp[i-2] + arr[i]);
	}

	// for(int i = 1; i <= N; i++){
	// 	cout << dp[i] << " ";
	// }


	for(int i = 1; i <= N; i++){
		if(maxx < dp[i]){
			maxx = dp[i];
		}
	}
	cout << maxx;
	return 0;
}