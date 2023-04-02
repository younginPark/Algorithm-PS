#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int dp[100001] = { 0, };

    for(int i = 1; i < n+1; i++){
        dp[i] = i;
        for(int j = 1; j*j <= i; j++){
            dp[i] = min(dp[i], dp[i-j*j]+1);
        }
    }
    printf("%d\n", dp[n]);
}
