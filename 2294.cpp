#include <iostream>
#include <algorithm>
using namespace std;
int n, k;
int dp[10001];
int main(){
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n; i++){
        int cost;
        scanf("%d", &cost);
        if(cost <= k){
            dp[cost] = 1;
            for(int j = cost+cost; j <= k; j+=cost){
                if(dp[j] > 0){
                    dp[j] = min(dp[j], j/cost);
                }
                else{
                    dp[j] = j/cost;
                }
            }
        }
    }
    for(int i = 1; i <= k; i++){
        for(int j = 1; j < i; j++){
            if(dp[j] > 0 && dp[i-j] > 0){
                if(dp[i] > 0){
                    dp[i] = min(dp[i], dp[j]+dp[i-j]);
                }
                else{
                    dp[i] = dp[j]+dp[i-j];
                }
            }
        }
    }
    if(dp[k] > 0){
        printf("%d\n", dp[k]);
    }
    else{
        printf("-1\n");
    }
    return 0;
}