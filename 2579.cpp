#include <iostream>
using namespace std;

int max(int a, int b){
	return a > b ? a : b;
}

int main () {

    int N;
    int arr[300];
    int dp[300];

    cin >> N;
    
    for (int i = 0; i < N; i++){
    	cin >> arr[i];
    }

    dp[0] = arr[0];
    dp[1] = max(arr[0]+arr[1], arr[1]);
    dp[2] = max(arr[0]+arr[2], arr[1]+arr[2]);

    for (int i = 3; i < N; i++) {
    	dp[i] = max(dp[i-2] + arr[i], dp[i-3] + arr[i-1] + arr[i]);
    }
    
    cout << dp[N-1];

    return 0;
}