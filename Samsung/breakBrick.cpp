#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

/*
dfs와 시뮬레이션 결합 문제

N: 벽돌개수, W: 가로, H: 세로

- 주의할 점
- dfs 시 인덱스를 넘기지 않고, visited도 체크도 안함 => 왜냐하면 구슬을 여러개 같은 곳에 떨어트릴 수 있고 떨어트리는 순서에 따라 map의 모양이 변함
- 떨어트릴 위치를 순서대로 visited에 넣어줌, 그리고 그 visited를 N만큼 순회하면서 구슬 떨어트릴거임 
- 내가 정한 위치의 열에 아예 깰 벽돌이 없으면 그 조합은 그냥 넘어가야함,해당 값 체크하지 않음

1. dfs
1-1) dfs를 돌면서 크기가 N인 조합들을 만든다.
1-2) 크기가 N인 조합이 하나 완성되면 그때 벽돌을 조합 순서대로 깨고 땡기고를 N만큼 반복

2. 벽돌 깨는거 구현
2-1) 기존 격자를 복사해서 복사해둔거에서 진행하기
2-2) 벽돌이 떨어지는 위치에서 4방향(위 방향 뺴도 될듯)에 있는 벽돌들을 다 부숨 
2-3) 맨 아래 행부터 빈칸이면 위에 벽돌 땡겨서 내려옴
2-4) N번만큼 깨고 땡기기를 반복했으면 남은 벽돌의 개수를 정답 변수와 비교해서 현재 정답보다 작다면 업데이트

*/

int dy[4] = { -1, 0, +1, 0 };
int dx[4] = { 0, -1, 0, +1 };

int N, W, H;
int board[20][20];
int copy_board[20][20];
queue<pair<pair<int, int>,int> > q;
int order[5];
int ans = 99999999;

void init(){
    memset(board, 0, sizeof(board));
    memset(copy_board, 0, sizeof(copy_board));
    memset(order, 0, sizeof(order));
    ans = 99999999;
}

void userInput(){
    cin >> N >> W >> H;
    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            cin >> board[i][j];
        }
    }
}

void breakMore(){
    while(!q.empty()){
        int cy = q.front().first.first;
        int cx = q.front().first.second;
        int clen = q.front().second;
        q.pop();
        for(int dir = 0; dir < 4; dir++){
            for(int len = 0; len < clen; len++){
                int ny = cy + (dy[dir] * len);
                int nx = cx + (dx[dir] * len);
                if(ny < 0 || nx < 0 || ny >= H || nx >= W){
                    break;
                }
                if(copy_board[ny][nx] > 0){
                    q.push(make_pair(make_pair(ny, nx), copy_board[ny][nx]));
                    copy_board[ny][nx] = 0;
                }
            }
        }
    }
}

void breakBricks(){
    memset(copy_board, 0, sizeof(copy_board));
    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            copy_board[i][j] = board[i][j];
        }
    }
    for(int cur_idx = 0; cur_idx < N; cur_idx++){
        // 터트리기
        int cx = order[cur_idx];
        //cout << cx << " ";
        int cy = -1, clen;
        for(int i = 0; i < H; i++){
            if(copy_board[i][cx] > 0){
                cy = i;
                clen = copy_board[i][cx];
                break;
            }
        }
        if(cy == -1){
            break;
        }
        for(int dir = 0; dir < 4; dir++){
            for(int len = 0; len < clen; len++){
                int ny = cy + (dy[dir] * len);
                int nx = cx + (dx[dir] * len);
                if(ny < 0 || nx < 0 || ny >= H || nx >= W){
                    break;
                }
                if(copy_board[ny][nx] > 0){
                    q.push(make_pair(make_pair(ny, nx), copy_board[ny][nx]));
                    copy_board[ny][nx] = 0;
                }
            }
        }
        breakMore();
        // printBoard
        // cout << "땡기기전----------------\n";
        // for(int y = 0; y < H; y++){
        //     for(int x = 0; x < W; x++){
        //         cout << copy_board[y][x] << " ";
        //     }
        //     cout <<"\n";
        // }
        // 아래로 떙기기
        for(int j = 0; j < W; j++){
            for(int i = H-1; i >= 0; i--){
                if(copy_board[i][j] == 0){
                    int y = i;
                    while(y >= 1 && copy_board[y][j] == 0){
                        y--;
                    }
                    copy_board[i][j] = copy_board[y][j];
                    copy_board[y][j] = 0;
                }
            }
        }
        
    }
    int total_bricks = 0;
    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            if(copy_board[i][j] > 0){
                total_bricks++;
            }
        }
    }
    // printBoard
    // cout << "땡긴후-----------\n";
    // for(int y = 0; y < H; y++){
    //     for(int x = 0; x < W; x++){
    //         cout << copy_board[y][x] << " ";
    //     }
    //     cout <<"\n";
    // }
    //cout << "=> " << total_bricks << "\n"; 
    ans = min(ans, total_bricks);
}

void dfs(int idx){
    if(idx >= N){
        breakBricks();
        return;
    }
    for(int i = 0; i < W; i++){
        order[idx] = i;
        dfs(idx+1);
    }
}   

void simulation(){
    for(int i = 0; i < W; i++){
        order[0] = i;
        dfs(1);
    }
}

void solution(){
    int T;
    cin >> T;
    for(int tc = 0; tc < T; tc++){
        init();
        userInput();
        simulation();
        cout << "#" << tc+1 << " " << ans << "\n";
    }
}

int main(){
    solution();
    return 0;
}