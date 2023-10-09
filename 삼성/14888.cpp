#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int N;
int board[15];
int opt[15];
int visit[15];
int first = 0;
long long max_ans;
long long min_ans;

void userInput(){
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> board[i];
    }
    int idx = 0;
    for(int i = 0; i < 4; i++){ // 0:+, 1:-, 2:x, 3:/
        int cnt;
        cin >> cnt;
        for(int j = 0; j < cnt; j++){
            opt[idx] = i;
            idx++;
        }
    }
}

void dfs(long long cur, int idx, int sign){
    // cout << cur << ", " << idx << "\n";
    long long calc;
    if(sign == 0){
        calc = cur + board[idx];
    }
    else if(sign == 1){
        calc = cur - board[idx];
    }
    else if(sign == 2){
        calc = cur * board[idx];
    }
    else if(sign == 3){
        calc = cur / board[idx];
    }
    // cout << "calc: " << calc << "\n";
    if(idx >= N-1){
        if(first == 0){
            max_ans = calc;
            min_ans = calc;
            first = 1;
        }
        else{
            max_ans = max(max_ans, calc);
            min_ans = min(min_ans, calc);
        }
        return;
    }
    for(int i = 0; i < N-1; i++){
        if(visit[i] == 0){
            visit[i] = 1;
            dfs(calc, idx+1, opt[i]);
            visit[i] = 0;
        }
    }
}

int main(){
    userInput();
    memset(visit, 0, sizeof(visit));
    for(int i = 0; i < N-1; i++){
        visit[i] = 1;
        dfs(board[0], 1, opt[i]);
        visit[i] = 0;
    }
    cout << max_ans << "\n" << min_ans;
    return 0;
}