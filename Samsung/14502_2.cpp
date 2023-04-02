#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

int dy[4] = { -1, 0, +1, 0 };
int dx[4] = { 0, -1, 0, +1 };

int board[10][10];
int ans = -1;
int N, M;

void userInput(){
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> board[i][j];
        }
    }
}

void printBoard(){
    cout << "\n";
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

void spreadVirus(){
    int tmp_board[10][10];
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            tmp_board[i][j] = board[i][j];
        }
    }

    // tmp_board로 bfs 돌리기
    queue<pair<int, int> > q;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(tmp_board[i][j] == 2){
                q.push(make_pair(i, j));
            }
        }
    }
    while(!q.empty()){
        int frontY = q.front().first;
        int frontX = q.front().second;
        q.pop();
        for(int dir = 0; dir < 4; dir++){
            int ny = frontY + dy[dir];
            int nx = frontX + dx[dir];
            if(ny < 0 || nx < 0 || ny >= N || nx >= M || tmp_board[ny][nx] != 0){
                continue;
            }
            tmp_board[ny][nx] = 2;
            q.push(make_pair(ny, nx));
        }
    }

    // 0인 빈칸 수 구해서 정답 변수 업데이트
    int count = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(tmp_board[i][j] == 0){
                count++;
            }
        }
    }
    ans = max(ans, count);
}

void dfs(int cnt, int pos){
    if(cnt == 3){
        spreadVirus();
        return;
    }
    for(int i = pos; i < N*M; i++){
        int y = i / M;
        int x = i % M;
        if(board[y][x] == 0){
            board[y][x] = 5;
            dfs(cnt+1, i+1);
            board[y][x] = 0;
        }
    }
}

int main(){
    userInput();
    for(int i = 0; i < N*M; i++){
        int y = i / M;
        int x = i % M;
        if(board[y][x] == 0){
            board[y][x] = 5;
            dfs(1, i+1);
            board[y][x] = 0;
        }
    }
    cout << ans;
    return 0;
}