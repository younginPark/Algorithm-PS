#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
/*
1. 나무 성장:
모든 나무에 대해 동시에 인접한 4개의 칸 중 나무가 있는 칸의 수만큼 나무 성장
2. 나무 번식:
나무의 4방향으로 벽(-1), 다른 나무, 제초제 모두 없는 칸에 번식을 진행하고, 
기준 나무 수에서 번식이 가능한 칸의 개수만큼 나눈 나무 그루수가 번식됨 (나머지 버림)
3. 제초제 뿌림: 
나무가 가장 많이 박멸되는 칸에 뿌림, 
대각선 방향으로 K칸만큼 전파, 
전파되는 도중에 벽이 있거나 나무가 아예 없는 칸인 경우 그 칸까지만 뿌려지고 더이상 뿌리지 X, 
제초제는 c년만큼 존재하고 c+1년째가 될 때 사라짐,
제초제 뿌린 곳에 다시 뿌리면 다시 c년동안 제초제 유지됨

가장 많이 박멸되는 양과 y,x 좌표 갖고 있다가 해당 값으로 다시 한번 정말 박멸시킴, 
박멸되는 양을 ans 변수에 += 함
*/

int dy[4] = { -1, 0, +1, 0 };
int dx[4] = { 0, -1, 0, +1 };

int dy2[4] = { -1, -1, +1, +1 };
int dx2[4] = { -1, +1, -1, +1 };

int N, M, K, C;
int board[21][21];
int copy_board[21][21];
int medicine[21][21];
int ans = 0;

void userInput(){
    cin >> N >> M >> K >> C;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> board[i][j];
        }
    }
}


void copyBoard(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            copy_board[i][j] = board[i][j];
        }
    }
}

void rollbackBoard(){
for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            board[i][j] = copy_board[i][j];
        }
    }
}

// 모든 나무에 대해 동시에 인접한 4개의 칸 중 나무가 있는 칸의 수만큼 나무 성장
void growTree(){
    copyBoard();
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(board[i][j] > 0){
                int neighbor = 0;
                for(int dir = 0; dir < 4; dir++){
                    int ny = i + dy[dir];
                    int nx = j + dx[dir];
                    if(ny >= 0 && nx >= 0 && ny < N && nx < N && board[ny][nx] > 0){
                        neighbor++;
                    }
                }
                copy_board[i][j] += neighbor;
            }
        }
    }
    rollbackBoard();
}

// 나무의 4방향으로 벽(-1), 다른 나무, 제초제 모두 없는 칸에 번식을 진행하고, 
// 기준 나무 수에서 번식이 가능한 칸의 개수만큼 나눈 나무 그루수가 번식됨 (나머지 버림)
void moreTree(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(board[i][j] > 0){
                int neighbor = 0;
                for(int dir = 0; dir < 4; dir++){
                    int ny = i + dy[dir];
                    int nx = j + dx[dir];
                    if(ny < 0 || nx < 0 || ny >= N || nx >= N || board[ny][nx] == -1 || board[ny][nx] > 0 || medicine[ny][nx] > 0){
                        continue;
                    }
                    neighbor++;
                }
                if(neighbor > 0){
                    int moreTreeCnt = board[i][j] / neighbor;
                    for(int dir = 0; dir < 4; dir++){
                        int ny = i + dy[dir];
                        int nx = j + dx[dir];
                        if(ny < 0 || nx < 0 || ny >= N || nx >= N || board[ny][nx] == -1 || board[ny][nx] > 0 || medicine[ny][nx] > 0){
                            continue;
                        }
                        copy_board[ny][nx] += moreTreeCnt;
                    }
                }
            }
        }
    }
}

/*
나무가 가장 많이 박멸되는 칸에 뿌림, 
대각선 방향으로 K칸만큼 전파,
전파되는 도중에 벽이 있거나 나무가 아예 없는 칸인 경우 그 칸까지만 뿌려지고 더이상 뿌리지 X, => 벽 혹은 나무가 아예 없는 칸도 뿌리기는 해야함, 제초제 존재하므로
제초제는 c년만큼 존재하고 c+1년째가 될 때 사라짐,
제초제 뿌린 곳에 다시 뿌리면 다시 c년동안 제초제 유지됨
*/

int spreadMedicine(int y, int x){
    int totalDiedTreeCnt = 0;
    if(copy_board[y][x] > 0 && medicine[y][x] == 0){
        totalDiedTreeCnt += copy_board[y][x];
    }
    else{
        return totalDiedTreeCnt;
    }
    for(int dir = 0; dir < 4; dir++){
        for(int k = 1; k <= K; k++){
            int ny = y + dy2[dir] * k;
            int nx = x + dx2[dir] * k;
            if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                break;
            }
            else if(copy_board[ny][nx] == 0 || copy_board[ny][nx] == -1){
                break;
            }
            else if(copy_board[ny][nx] > 0){
                totalDiedTreeCnt += copy_board[ny][nx];
            }
        }
    }
    return totalDiedTreeCnt;
}

void realSpreadMedicine(int y, int x, int time){
    int totalDiedTreeCnt = 0;
    if(copy_board[y][x] > 0 && medicine[y][x] == 0){
        copy_board[y][x] = 0;
        medicine[y][x] = time+C;
    }
    else{
        medicine[y][x] = time+C;
        return;
    }
    for(int dir = 0; dir < 4; dir++){
        for(int k = 1; k <= K; k++){
            int ny = y + dy2[dir] * k;
            int nx = x + dx2[dir] * k;
            if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                break;
            }
            else if(copy_board[ny][nx] == 0 || copy_board[ny][nx] == -1){
                medicine[ny][nx] = time+C;
                break;
            }
            else if(copy_board[ny][nx] > 0){
                copy_board[ny][nx] = 0;
                medicine[ny][nx] = time+C;
            }
        }
    }
}

void dieTree(int time){
    int max_cnt = 0;
    int max_y = -1, max_x = -1;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            int returnCnt = spreadMedicine(i, j);
            if(returnCnt > max_cnt){
                max_cnt = returnCnt;
                max_y = i, max_x = j;
            }
        }
    }
    if(max_y != -1 && max_x != -1){
        ans += max_cnt;
        realSpreadMedicine(max_y, max_x, time);
    }
    rollbackBoard();
}

void decreaseMedicine(int time){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(medicine[i][j] == time){
                medicine[i][j] = 0;
            }
        }
    }
}

 int main(){
     userInput();
     for(int i = 0; i < M; i++){
         memset(copy_board, 0, sizeof(copy_board));
         growTree();
         moreTree();
         dieTree(i);
         decreaseMedicine(i);
     }
     cout << ans;
     return 0;
 }