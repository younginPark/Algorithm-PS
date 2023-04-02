#include <iostream>
#include <algorithm>
using namespace std;
int N;
int arr[1001];
int dp[1001];
int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d", &arr[i]);
        dp[i] = 1;
    }
    for(int i = N-1; i >= 0; i--){
        for(int j = N-1; j > i; j--){
            if(arr[j] < arr[i]){
                dp[i] = max(dp[i], dp[j]+1);
            }
        }
    }
    sort(dp, dp+N);
    printf("%d\n", dp[N-1]);
    return 0;
}