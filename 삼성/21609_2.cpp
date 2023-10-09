#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int dy[4] = { -1, 0, +1, 0 };
int dx[4] = { 0, -1, 0, +1 };

int N, M;
int board[25][25];

int blockY, blockX;

int ans = 0;

void userInput(){
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> board[i][j];
        }
    }
}

void printBoard(){
    cout << "---------------\n";
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

bool findBlockGroup(){
    int biggestCnt = -1;
    int standardY = -1, standardX = -1;
    int standardRainbow = 0;
    int visited[25][25];
    memset(visited, -1, sizeof(visited));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            queue<pair<int, int> > q;
            int cnt = 0, rainbow_cnt = 0;
            int color;
            if(1 <= board[i][j] && board[i][j] <= M && visited[i][j] == -1){
                q.push(make_pair(i, j));
                visited[i][j] = 1;
                cnt++;
                color = board[i][j];
                int rainbow_visited[25][25];
                memset(rainbow_visited, -1, sizeof(rainbow_visited));
                while(!q.empty()){
                    int y = q.front().first;
                    int x = q.front().second;
                    q.pop();
                    for(int dir = 0; dir < 4; dir++){
                        int ny = y + dy[dir];
                        int nx = x + dx[dir];
                        if(ny < 0 || nx < 0 || ny >= N || nx >= N || visited[ny][nx] == 1){
                            continue;
                        }
                        if((rainbow_visited[ny][nx] == -1 && board[ny][nx] == 0) || board[ny][nx] == color){
                            if(board[ny][nx] == 0){
                                rainbow_cnt++;
                                rainbow_visited[ny][nx] = 1;
                                q.push(make_pair(ny, nx));
                                cnt++;      
                            }
                            else{
                                q.push(make_pair(ny, nx));
                                visited[ny][nx] = 1;
                                cnt++;
                            }
                        }
                    }
                }
                if(biggestCnt < cnt){
                    standardY = i;
                    standardX = j;
                    biggestCnt = cnt;
                    standardRainbow = rainbow_cnt;
                }
                else if(biggestCnt == cnt){
                    if(standardRainbow <= rainbow_cnt){
                        standardY = i;
                        standardX = j;
                        standardRainbow = rainbow_cnt;
                    }
                    // else if(standardRainbow == rainbow_cnt){
                    //     if(standardY < i || (standardY == i && standardX < j)){
                    //         standardY = i;
                    //         standardX = j;
                    //     }
                    // }
                }
            }
        }
    }
    if(standardY != -1 && standardX != -1 && biggestCnt >= 2){
        blockY = standardY;
        blockX = standardX;
        ans += (biggestCnt * biggestCnt);
        return true;
    }
    return false;
}

void removeBlockGroup(){
    queue<pair<int, int> > q;
    q.push(make_pair(blockY, blockX));
    int visited[25][25];
    memset(visited, -1, sizeof(visited));
    int color = board[blockY][blockX];
    visited[blockY][blockX] = 1;
    board[blockY][blockX] = -3;
    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        for(int dir = 0; dir < 4; dir++){
            int ny = y + dy[dir];
            int nx = x + dx[dir];
            if(ny < 0 || nx < 0 || ny >= N || nx >= N || visited[ny][nx] == 1){
                continue;
            }
            if(board[ny][nx] == 0 || board[ny][nx] == color){
                q.push(make_pair(ny, nx));
                visited[ny][nx] = 1;
                board[ny][nx] = -3;
            }
        }
    }
}

void boardGravity(){
    for(int x = 0; x < N; x++){
        for(int y = N-2; y >= 0; y--){
            if(0 <= board[y][x] && board[y][x] <= M){
                int val = board[y][x];
                int tmpY = y;
                while(0 <= tmpY && tmpY < N-1 && board[tmpY+1][x] == -3){
                    board[tmpY+1][x] = val;
                    board[tmpY][x] = -3;
                    tmpY++;
                }
            }
        }
    }
}

void reverseRotation90(){
    int copy_board[25][25];
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            copy_board[N-1-j][i] = board[i][j];
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            board[i][j] = copy_board[i][j];
        }
    }
}

int main(){
    userInput();
    while(1){
        if(findBlockGroup() == false){
            break;
        }
        removeBlockGroup();
        boardGravity();
        reverseRotation90();
        boardGravity();
    }
    cout << ans;
    return 0;
}