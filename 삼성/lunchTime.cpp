#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <cmath>
using namespace std;

struct USER{
    int y, x;
};
struct STAIR{
    int y, x, len;
};

int N;
int ans_minLen = 999999999;
int board[11][11];
int visited[105];
int dp[1000];

vector<USER> user;
vector<STAIR> stair; 

void init(){
    N = 0;
    ans_minLen = 999999999;
    memset(board, 0, sizeof(board));
    memset(visited, 0, sizeof(visited));
    memset(dp, 0, sizeof(dp));
    user.clear();
    stair.clear();
}

void userInput(){
    cin >> N;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> board[i][j];
            if(board[i][j] == 1){
                USER tmp_user;
                tmp_user.y = i, tmp_user.x = j;
                user.push_back(tmp_user);
            }
            else if(board[i][j] >= 2){
                STAIR tmp_stair;
                tmp_stair.y = i, tmp_stair.x = j, tmp_stair.len = board[i][j];
                stair.push_back(tmp_stair);
            }
        }
    }
}

void dfs(int cur_idx){
    if(cur_idx >= user.size()){
        // 마지막 사람까지 팀이 정해졌으면 팀이 각각 첫번째 계단을 갔을 경우, 두번째 계단을 갔을 경우를 나눠서 최장 시간을 업데이트 함
        priority_queue<int, vector<int>, greater<int> > team1_1; // 사람과 계단 사이의 거리를 넣어줌
        priority_queue<int, vector<int>, greater<int> > team1_2;
        priority_queue<int, vector<int>, greater<int> > team2_1; // 사람과 계단 사이의 거리를 넣어줌
        priority_queue<int, vector<int>, greater<int> > team2_2;
        for(int i = 0; i < user.size(); i++){
            int y = user[i].y;
            int x = user[i].x;
            int dist1 = abs(y-stair[0].y) + abs(x-stair[0].x);
            int dist2 = abs(y-stair[1].y) + abs(x-stair[1].x);
            if(visited[i] == 0){
                team1_1.push(dist1);
                team2_2.push(dist2);
            }
            else if(visited[i] == 1){
                team1_2.push(dist2);
                team2_1.push(dist1);
            }
        }

        // visited가 0인 사람들은 첫번째 계단, 1인 사람들은 두번째 계단
        int firstCaseLen = 0, secondCaseLen = 0, cur;
        memset(dp, 0, sizeof(dp));
        int team1_size = team1_1.size();
        for(int loop = 0; loop < team1_size; loop++){
            cur = team1_1.top()+1;
            while(1){
                if(dp[cur] < 3){
                    for(int i = 0; i < stair[0].len; i++){
                        dp[cur+i]++;
                    }
                    team1_1.pop();
                    break;
                }
                else{
                    cur++;
                }
            }
            if(loop == team1_size-1){
                firstCaseLen = cur+stair[0].len-1;
                for(int i = 0; i <= firstCaseLen; i++){
                }
            }
        }
        memset(dp, 0, sizeof(dp));
        int team2_size = team1_2.size();
        for(int loop = 0; loop < team2_size; loop++){
            cur = team1_2.top()+1;
            while(1){
                if(dp[cur] < 3){
                    for(int i = 0; i < stair[1].len; i++){
                        dp[cur+i]++;
                    }
                    team1_2.pop();
                    break;
                }
                else{
                    cur++;
                }
            }
            if(loop == team2_size-1){
                secondCaseLen = cur+stair[1].len-1;
                for(int i = 0; i <= secondCaseLen; i++){
                }
            }
        }
        // 적은 값으로 정답 업데이트
        if(firstCaseLen >= secondCaseLen){
            ans_minLen = min(ans_minLen, firstCaseLen);
        }
        else if(firstCaseLen < secondCaseLen){
            ans_minLen = min(ans_minLen, secondCaseLen);
        }
    // ********************************************************
        // visited가 1인 사람들은 첫번째 계단, 0인 사람들은 두번째 계단
        firstCaseLen = 0, secondCaseLen = 0;
        memset(dp, 0, sizeof(dp));
        team2_size = team2_1.size();
        for(int loop = 0; loop < team2_size; loop++){
            cur = team2_1.top()+1;
            while(1){
                if(dp[cur] < 3){
                    for(int i = 0; i < stair[0].len; i++){
                        dp[cur+i]++;
                    }
                    team2_1.pop();
                    break;
                }
                else{
                    cur++;
                }
            }
            if(loop == team2_size-1){
                firstCaseLen = cur+stair[0].len-1;
                for(int i = 0; i <= firstCaseLen; i++){
                }
            }
        }
        memset(dp, 0, sizeof(dp));
        team1_size = team2_2.size();
        for(int loop = 0; loop < team1_size; loop++){
            cur = team2_2.top()+1;
            while(1){
                if(dp[cur] < 3){
                    for(int i = 0; i < stair[1].len; i++){
                        dp[cur+i]++;
                    }
                    team2_2.pop();
                    break;
                }
                else{
                    cur++;
                }
            }
            if(loop == team1_size-1){
                secondCaseLen = cur+stair[1].len-1;
                for(int i = 0; i <= secondCaseLen; i++){
                }
            }
        }
        // 적은 값으로 정답 업데이트
        if(firstCaseLen >= secondCaseLen){
            ans_minLen = min(ans_minLen, firstCaseLen);
        }
        else if(firstCaseLen < secondCaseLen){
            ans_minLen = min(ans_minLen, secondCaseLen);
        }

        return;
    }
    for(int i = cur_idx; i < user.size(); i++){
        visited[i] = 1;
        dfs(i+1);
        visited[i] = 0;
    }
}

void solution(){
    // 계단은 2개 뿐이므로 dfs를 이용하여 조합으로 2팀으로 나눔
    for(int i = 0; i < user.size(); i++){
        visited[i] = 1;
        dfs(i+1);
        visited[i] = 0;
    }
}

void solve(){
    int tc;
    cin >> tc;
    for(int t = 1; t <= tc; t++){
        init();
        userInput();
        solution();
        cout << "#" << t << " " << ans_minLen+1 << "\n";
    }
}

int main(){
    solve();    
    return 0;
}