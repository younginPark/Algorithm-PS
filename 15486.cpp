#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N;
vector<pair<int, int> > v;
int answer;
int dp[1500001];
int main(){
    v.push_back(make_pair(0, 0));
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        int tmp1, tmp2;
        scanf("%d %d", &tmp1, &tmp2);
        v.push_back(make_pair(tmp1, tmp2));
    }
    //dp[i]는 i-1일 전까지 일해서 번 돈
    for(int i = 1; i <= N+1; i++){
        answer = max(answer, dp[i]);
        if(i + v[i].first > N + 1){
            continue;
        }
        dp[i+v[i].first] = max(dp[i+v[i].first], answer + v[i].second);
    }

    printf("%d\n", answer);
    return 0;
}