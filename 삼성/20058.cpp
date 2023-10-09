#include <iostream>
#include <cmath>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

int dy[4] = { -1, 0, +1, 0 };
int dx[4] = { 0, -1, 0, +1 };

int N, Q;
int b_size;
int board[65][65];
int cmd[1001];

void userInput(){
    cin >> N >> Q;
    b_size = pow(2, N);
    for(int i = 0; i < b_size; i++){
        for(int j = 0; j < b_size; j++){
            cin >> board[i][j];
        }
    }
    for(int i = 0; i < Q; i++){
        cin >> cmd[i];
    }
}

void printBoard(){
    cout << "------------\n";
    for(int i = 0; i < b_size; i++){
        for(int j = 0; j < b_size; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

void smallRotation(int y, int x, int mySize){
    int copy_board[65][65];
    int after_board[65][65];
    for(int r = y, i = 0; r < y + mySize; r++, i++){
        for(int c = x, j = 0; c < x + mySize; c++, j++){
            copy_board[i][j] = board[r][c];
        }
    }
    for(int r = 0; r < mySize; r++){
        for(int c = 0; c < mySize; c++){
            after_board[c][mySize-1-r] = copy_board[r][c];
        }
    }
    for(int r = y, i = 0; r < y + mySize; r++, i++){
        for(int c = x, j = 0; c < x + mySize; c++, j++){
            board[r][c] = after_board[i][j];
        }
    }
}

void rotation90(int L){
    int mySize = pow(2, L);
    for(int r = 0; r < b_size; r += mySize){
        for(int c = 0; c < b_size; c += mySize){
            smallRotation(r, c, mySize);
        }
    }
}

bool checkInBoard(int ny, int nx){
    if(ny < 0 || nx < 0 || ny >= b_size || nx >= b_size){
        return false;
    }
    return true;
}

void meltIce(){
    int copy_board[65][65];
    for(int i = 0; i < b_size; i++){
        for(int j = 0; j < b_size; j++){
            copy_board[i][j] = board[i][j];
        }
    }
    for(int i = 0; i < b_size; i++){
        for(int j = 0; j < b_size; j++){
            if(board[i][j] > 0){
                int cnt = 4;
                for(int dir = 0; dir < 4; dir++){
                    int ny = i + dy[dir];
                    int nx = j + dx[dir];
                    if(checkInBoard(ny, nx) == false || (checkInBoard(ny, nx) == true && board[ny][nx] == 0)){
                        cnt--;
                    }
                }
                if(cnt < 3){
                    copy_board[i][j]--;
                }
            }
        }
    }
    for(int i = 0; i < b_size; i++){
        for(int j = 0; j < b_size; j++){
            board[i][j] = copy_board[i][j];
        }
    }
}

int getRemainIce(){
    int total = 0;
    for(int i = 0; i < b_size; i++){
        for(int j = 0; j < b_size; j++){
            total += board[i][j];
        }
    }
    return total;
}

int bfs(int y, int x){
    int total = 0;
    int visited[65][65];
    memset(visited, 0, sizeof(visited));
    queue<pair<int, int> > q;
    q.push(make_pair(y, x));
    visited[y][x] = 1;

    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        total++;
        q.pop();
        for(int dir = 0; dir < 4; dir++){
            int ny = y + dy[dir];
            int nx = x + dx[dir];
            if(checkInBoard(ny, nx) == false || visited[ny][nx] == 1 || board[ny][nx] == 0){
                continue;
            }
            q.push(make_pair(ny, nx));
            visited[ny][nx] = 1;
        }
    }
    return total;
}

int getBlockSize(){
    int blockSize = 0;
    for(int i = 0; i < b_size; i++){
        for(int j = 0; j < b_size; j++){
            if(board[i][j] > 0){
                int result = bfs(i, j);
                blockSize = max(blockSize, result);
            }
        }
    }
    return blockSize;
}

void solution(){
    for(int i = 0; i < Q; i++){
        rotation90(cmd[i]);
        meltIce();   
    }
    int total = getRemainIce();
    int blockSize = getBlockSize();
    cout << total << "\n" << blockSize;
}

int main(){
    userInput();
    solution();
    return 0;
}