#include <iostream>
#include <cstring>
using namespace std;

int dy[4] = { -1, 0, +1, 0 };
int dx[4] = { 0, -1, 0, +1 };

int dy2[4] = { -1, -1, +1, +1 };
int dx2[4] = { -1, +1, -1, +1 };

int N, M, K, C;
int board[25][25];
int medicine[25][25];
int diedTree = 0;

void userInput(){
    cin >> N >> M >> K >> C;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> board[i][j];
        }
    }
}

void growTree(){
    int new_board[25][25];
    memset(new_board, 0, sizeof(new_board));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(board[i][j] > 0){
                for(int dir = 0; dir < 4; dir++){
                    int ny = i + dy[dir];
                    int nx = j + dx[dir];
                    if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                        continue;
                    }
                    if(board[ny][nx] > 0){
                        new_board[ny][nx] += 1;
                    }
                }
            }
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            board[i][j] += new_board[i][j];
        }
    }
}

void copyTree(){
    int new_board[25][25];
    memset(new_board, 0, sizeof(new_board));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(board[i][j] > 0){
                int cnt = 0;
                for(int dir = 0; dir < 4; dir++){
                    int ny = i + dy[dir];
                    int nx = j + dx[dir];
                    if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                        continue;
                    }
                    if(board[ny][nx] == -1 || board[ny][nx] > 0 || medicine[ny][nx] > 0){
                        continue;
                    }
                    cnt++;
                }
                if(cnt == 0){continue;}
                int value = board[i][j] / cnt;
                for(int dir = 0; dir < 4; dir++){
                    int ny = i + dy[dir];
                    int nx = j + dx[dir];
                    if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                        continue;
                    }
                    if(board[ny][nx] == -1 || board[ny][nx] > 0 || medicine[ny][nx] > 0){
                        continue;
                    }
                    new_board[ny][nx] += value;
                }
            }
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            board[i][j] += new_board[i][j];
        }
    }
}

void dieTree(int y, int x, int order){
    diedTree += board[y][x];
    board[y][x] = 0;
    medicine[y][x] = order+C;
    for(int dir = 0; dir < 4; dir++){
        for(int k = 1; k <= K; k++){
            int ny = y + dy2[dir] * k;
            int nx = x + dx2[dir] * k;
            if(ny < 0 || nx < 0 || ny >= N | nx >= N){
                break;
            }
            if(board[ny][nx] <= 0){
                medicine[ny][nx] = order+C;
                break;
            }
            diedTree += board[ny][nx];
            board[ny][nx] = 0;
            medicine[ny][nx] = order+C;
        }
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(medicine[j][j] <= order){
                medicine[i][j] = 0;
            } 
        }
    }
}


void findDieTreeSpot(int order){
    int bestY, bestX;
    int bestCnt = -1;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            int cnt = board[i][j];
            for(int dir = 0; dir < 4; dir++){
                for(int k = 1; k <= K; k++){
                    int ny = i + dy2[dir] * k;
                    int nx = j + dx2[dir] * k;
                    if(ny < 0 || nx < 0 || ny >= N | nx >= N){
                        break;
                    }
                    if(board[ny][nx] <= 0){
                        break;
                    }
                    cnt += board[ny][nx];
                }
            }
            if(cnt > bestCnt){
                bestY = i;
                bestX = j;
                bestCnt = cnt;
            }
        }
    }
    // cout << bestY << ", " << bestX << " " << bestCnt << "\n";
    dieTree(bestY, bestX, order);
}

void printBoard(){
    cout << "------------\n";
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

void solution(){
    memset(medicine, 0, sizeof(medicine));
    for(int i = 0; i < M; i++){
        growTree();
        copyTree();
        findDieTreeSpot(i);
    }
}

int main(){
    userInput();
    solution();
    cout << diedTree;
    return 0;
}