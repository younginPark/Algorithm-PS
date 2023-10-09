#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

/*
각각의 식재료 별로 시너지 값을 입력으로 받음
dfs를 돌면서 식재료를 2로 나눔, dfs의 종료 조건은 N/2개가 되었을 때임 (visited로 체크중임)
2개의 팀으로 나누어졌으면 visited가 1인 것과 2인 것을 나누어서 각각 한번씩 시너지의 값을 구함
2중 for문을 돌면서 현재 visited가 1인 값과 그 다음 visited가 1인 값을 순서 바꾸면서 다 더함
visited가 0인 값도 똑같이 해주고 각 값의 차의 절대값을 구해서 현재가 더 작으면 정답 변수 업데이트
*/

int N;
long long ans = -1;
long long synergy[17][17];
int visited[17];

void init(){
    ans = -1;
    memset(synergy, 0, sizeof(synergy));
    memset(visited, 0, sizeof(visited));
}

void userInput(){
    cin >> N;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> synergy[i][j];
        }
    }
}

void getSynergy(){
    long long num1 = 0, num2 = 0;
    for(int i = 0; i < N; i++){
        for(int j = i+1; j < N; j++){
            if(visited[i] == 1 && visited[j] == 1){
                num1 += synergy[i][j];
                num1 += synergy[j][i];
            }
            else if(visited[i] == 0 && visited[j] == 0){
                num2 += synergy[i][j];
                num2 += synergy[j][i];
            }
        }
    }
    long long tmp_ans = abs(num1 - num2);
    if(ans == -1){
        ans = tmp_ans;
    }
    else if(ans > tmp_ans){
        ans = tmp_ans;
    }
}

void dfs(int cnt, int idx){
    if(cnt == N/2){
        getSynergy();
        return;
    }
    for(int i = idx; i < N-1; i++){
        if(visited[i] == 0){
            visited[i] = 1;
            dfs(cnt+1, i+1);
            visited[i] = 0;
        }
    }
}

void solution(){
    for(int i = 0; i < N-1; i++){
        if(visited[i] == 0){
            visited[i] = 1;
            dfs(1, i+1);
            visited[i] = 0;
        }
    }
}

void solve(){
    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++){
        init();
        userInput();
        solution();
        cout << "#" << tc << " " << ans << "\n";
    }
}

int main(){
    solve();
    return 0;
}