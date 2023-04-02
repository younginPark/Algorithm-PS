#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

int dy[4] = { 0, 0, +1, -1 }; // 동서남북
int dx[4] = { +1, -1, 0, 0, };

int dice[6] = { 2, 1, 5, 6, 4, 3 };

int N, M, K;
int board[25][25];
int ans = 0;
int cy = 0, cx = 0, cd = 0; // 동쪽 방향으로 초기화

void userInput(){
    cin >> N >> M >> K;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> board[i][j];
        }
    }
}

// 주사위 구르는 방향에 따른 값의 위치 변화
void moveDiceResult(int dir){
    // 동
    if(dir == 0){
        swap(dice[1], dice[4]);
        swap(dice[3], dice[5]);
        swap(dice[4], dice[5]);
    }
    // 서
    if(dir == 1){
        swap(dice[1], dice[5]);
        swap(dice[3], dice[4]);
        swap(dice[4], dice[5]);
    }
    // 남
    if(dir == 2){
        int tmp0 = dice[0], tmp1 = dice[1], tmp2 = dice[2], tmp3 = dice[3];
        dice[1] = tmp0;
        dice[2] = tmp1;
        dice[3] = tmp2;
        dice[0] = tmp3;
    }
    // 북
    if(dir == 3){
        int tmp0 = dice[0], tmp1 = dice[1], tmp2 = dice[2], tmp3 = dice[3];
        dice[0] = tmp1;
        dice[1] = tmp2;
        dice[2] = tmp3;
        dice[3] = tmp0;
    }
}

// 주사위가 이동 방향으로 한 칸 굴러간다. 만약, 이동 방향에 칸이 없다면, 이동 방향을 반대로 한 다음 한 칸 굴러간다.
void moveDice(){
    // 이동 방향에 칸이 있는지 체크 후 있다면 한칸 굴리기
    // 만약 칸이 없다면 방향 반대로 하여 한칸 굴리기
    int ny = cy + dy[cd];
    int nx = cx + dx[cd];
    if(ny < 0 || nx < 0 || ny >= N || nx >= M){
        if(cd == 0){
            cd = 1;
        }
        else if(cd == 1){
            cd = 0;
        }
        else if(cd == 2){
            cd = 3;
        }
        else if(cd == 3){
            cd = 2;
        }
        ny = cy + dy[cd];
        nx = cx + dx[cd];
    }
    cy = ny, cx = nx;
    moveDiceResult(cd);
}

// 주사위가 도착한 칸 (x, y)에 대한 점수를 획득한다.
// 칸 (x, y)에 대한 점수 구하기
    // (x, y)에 있는 정수를 B, (x, y)에서 동서남북 방향의 칸에 연속해서 정수 B 값이 있어 이동할 수 있는 칸의 수 C
    // bfs를 돌면서 B가 있는 칸만 수 더 하면서 계속 돎
    // 점수 = B * C 

void getScore(){
    int B = board[cy][cx];
    int cnt = 1;
    queue<pair<int, int> > q;
    int visited[25][25];
    memset(visited, 0, sizeof(visited));
    visited[cy][cx] = 1;
    q.push(make_pair(cy, cx));
    while(!q.empty()){
        int frontY = q.front().first;
        int frontX = q.front().second;
        q.pop();
        for(int dir = 0; dir < 4; dir++){
            int ny = frontY + dy[dir];
            int nx = frontX + dx[dir];
            if(ny < 0 || nx < 0 || ny >= N || nx >= M || visited[ny][nx] == 1){
                continue;
            }
            if(board[ny][nx] == B){
                cnt++;
                q.push(make_pair(ny, nx));
                visited[ny][nx] = 1;
            }
        }
    }
    ans += (B * cnt);
}

// 주사위의 아랫면에 있는 정수 A와 주사위가 있는 칸 (x, y)에 있는 정수 B를 비교해 이동 방향을 결정한다.
    // A > B인 경우 이동 방향을 90도 시계 방향으로 회전시킨다.
    // A < B인 경우 이동 방향을 90도 반시계 방향으로 회전시킨다.
    // A = B인 경우 이동 방향에 변화는 없다.
void decideDir(){
    // 주사위의 아랫면은 idx = 3
    int A = dice[3];
    int B = board[cy][cx];
    if(A > B){
        if(cd == 0){
            cd = 2;
        }
        else if(cd == 1){
            cd = 3;
        }
        else if(cd == 2){
            cd = 1;
        }
        else if(cd == 3){
            cd = 0;
        }
    }
    else if(A < B){
        if(cd == 0){
            cd = 3;
        }
        else if(cd == 1){
            cd = 2;
        }
        else if(cd == 2){
            cd = 0;
        }
        else if(cd == 3){
            cd = 1;
        }
    }
}


void solution(){
    // K번 반복
    for(int i = 0; i < K; i++){
        moveDice();
        getScore();
        decideDir();
    }
    cout << ans;
}

int main(){
    userInput();
    solution();
    return 0;
}