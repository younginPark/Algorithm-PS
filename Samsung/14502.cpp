#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int N;
int day[20];
int t[20];
int p[20];
int dp[20];

void userInput(){
    cin >> N;
    for(int i = 1; i <= N; i++){
        cin >> t[i] >> p[i];
    }
}

void solution(){
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= N; i++){
        if(i+t[i]-1 <= N){
            dp[i+t[i]-1] = max(dp[i+t[i]-1], dp[i-1] + p[i]);
        }
        dp[i] = max(dp[i], dp[i-1]);
    }
}

int main(){
    userInput();
    solution();
    cout << dp[N];
    return 0;
}