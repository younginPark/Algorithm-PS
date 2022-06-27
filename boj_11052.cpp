#include <iostream>
#include <algorithm>
using namespace std;

int N;
int arr[1001];
int dp[1001];

int main(){

    cin >> N;
    for(int i = 1; i <= N; i++){
        cin >> arr[i];
    }
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= i; j++){
            dp[i] = max(dp[i], arr[j] + dp[i-j]);
        }
    }

    cout << dp[N];
    return 0;
}