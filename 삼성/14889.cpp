#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

int N;
int board[25][25];
int visit[25];
int ans = INT_MAX;

void userInput(){
    cin >> N;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> board[i][j];
        }
    }
}

void getDiff(){
    int score1 = 0;
    int score2 = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(visit[i] == 1 && visit[j] == 1){
                score1 += board[i][j];
            }
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(visit[i] == 0 && visit[j] == 0){
                score2 += board[i][j];
            }
        }
    }
    for(int i = 0; i < N; i++){
        cout << visit[i] << " ";
    }
    cout << "\n";
    cout << score1 << ", " << score2 << "\n";
    if(score1 >= score2){
        ans = min(ans, score1-score2);
    }
    else{
        ans = min(ans, score2-score1);
    }
}

void dfs(int cnt, int idx){
    if(cnt == N/2){
        getDiff();
        return;
    }
    for(int i = idx; i < N-1; i++){
        if(visit[i] == 0){
            visit[i] = 1;
            dfs(cnt+1, i+1);
            visit[i] = 0;
        }
    }
}

int main(){
    userInput();
    for(int i = 0; i < N; i++){
        visit[i] = 1;
        dfs(1, i+1);
        visit[i] = 0;
    }
    cout << ans;
    return 0;
}