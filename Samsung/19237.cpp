#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

int dy[4] = { -1, +1, 0, 0 };
int dx[4] = { 0, 0, -1, +1 };

struct BOARD{
    int number, time;
};
struct SHARK {
    int y, x, dir;
};

BOARD board[25][25];
SHARK shark[405];
int priority[405][5][5];
int ans = 0;

int N, M, K;

void userInput(){
    cin >> N >> M >> K;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            int tmp;
            cin >> tmp;
            if(tmp != 0){
                shark[tmp-1].y = i;
                shark[tmp-1].x = j;
            }
        }
    }
    for(int i = 0; i < M; i++){
        cin >> shark[i].dir;
        shark[i].dir--;
    }
    for(int i = 0; i < M; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                cin >> priority[i][j][k];
                priority[i][j][k]--;
            }
        }
    }
}

void solution(){
    while(ans <= 1001){
        int shark_board[25][25];
        memset(shark_board, -1, sizeof(shark_board));
        ans++;
        // 현재 위치에 자신의 냄새 뿌림
        for(int i = 0; i < M; i++){
            if(shark[i].y == -1){
                continue;
            }
            int y = shark[i].y;
            int x = shark[i].x;
            board[y][x].number = i;
            board[y][x].time = K;
        }
        // 상어가 상하좌우 중에 우선순위에 맞춰서 방향 틀어 이동
        for(int i = 0; i < M; i++){
            int cy = shark[i].y;
            int cx = shark[i].x;
            int cdir = shark[i].dir;
            int moveY = 0; // 이동 할 칸을 찾았는지 flag
            // 아무 냄새 없는 칸 먼저 찾기
            for(int dir = 0; dir < 4; dir++){
                int ndir = priority[i][cdir][dir];
                int ny = cy + dy[ndir];
                int nx = cx + dx[ndir];
                if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                    continue;
                }
                if(board[ny][nx].time > 0){
                    continue;
                }
                moveY = 1;
                if(shark_board[ny][nx] == -1){
                    shark[i].y = ny;
                    shark[i].x = nx;
                    shark[i].dir = ndir;
                    shark_board[ny][nx] = i;
                }
                else{
                    shark[i].y = -1;
                    shark[i].x = -1;
                    shark[i].dir = -1;
                }
                break;
            }
            // 냄새 없는 칸 없으면 자기 냄새 있는 칸 다시 찾음 
            if(moveY == 0){
                for(int dir = 0; dir < 4; dir++){
                    int ndir = priority[i][cdir][dir];
                    int ny = cy + dy[ndir];
                    int nx = cx + dx[ndir];
                    if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                        continue;
                    }
                    if(board[ny][nx].number == i){
                        moveY = 1;
                        if(shark_board[ny][nx] == -1){
                            shark[i].y = ny;
                            shark[i].x = nx;
                            shark[i].dir = ndir;
                            shark_board[ny][nx] = i;
                        }
                        else{
                            shark[i].y = -1;
                            shark[i].x = -1;
                            shark[i].dir = -1;
                        }
                        break;
                    }
                }
            }
            if(moveY == 0){ // 자기가 이동 할 칸에 이미 상어가 들어있으면 그냥 격자에 못들어옴 (작은 번호 상어부터 넣었으므로)
                shark[i].y = -1;
                shark[i].x = -1;
                shark[i].dir = -1;
            }
        }
        // 상어 격자 어디에 있는지 출력
        // cout << "--------------\n";
        // for(int i = 0; i < N; i++){
        //     for(int j = 0; j < N; j++){
        //         cout << shark_board[i][j] << " ";
        //     }
        //     cout << "\n";
        // }
        // // 향 출력
        // cout << "*************\n";
        // for(int i = 0; i < N; i++){
        //     for(int j = 0; j < N; j++){
        //         cout << board[i][j].time << " ";
        //     }
        //     cout << "\n";
        // }
        // 1번 상어가 격자에 혼자 남았는지 체크 
        int remain = 0;
        for(int i = 1; i < M; i++){
            if(shark[i].y != -1){
                remain++;
            }
        }
        if(remain == 0){
            return;
        }
        // 지금 이동이 1회 이상 && 격자에 냄새가 1 이상 => -1씩 해주기
        if(ans >= 1){
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    if(board[i][j].time == 1){
                        board[i][j].time = 0;
                        board[i][j].number = -1;
                    }
                    else if(board[i][j].time > 1){
                        board[i][j].time--;
                    }
                }
            }
        }
    }
}

int main(){
    userInput();
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            board[i][j].number = -1;
        }
    }
    solution();
    if(ans > 1000){
        cout << -1;
    }
    else{
        cout << ans;
    }
    return 0;
}