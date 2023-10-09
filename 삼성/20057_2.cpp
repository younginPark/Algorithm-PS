#include <iostream>
using namespace std;

int dy[4] = { 0, +1, 0, -1 };
int dx[4] = { -1, 0, +1, 0 };

// 5 10 10 2 2 7 7 1 1 a
int order[10] = { 5, 10, 10, 2, 2, 7, 7, 1, 1 };
int scatterY[4][10] = {{0, -1, 1, -2, 2, -1, 1, -1, 1, 0}, 
                        {2, 1, 1, 0, 0, 0, 0, -1, -1, 1}, 
                        {0, -1, 1, -2, 2, -1, 1, -1, 1, 0}, 
                        {-2, -1, -1, 0, 0, 0, 0, 1, 1, -1}};
int scatterX[4][10] = {{-2, -1, -1, 0, 0, 0, 0, 1, 1, -1}, 
                        {0, -1, 1, -2, 2, -1, 1, -1, 1, 0}, 
                        {2, 1, 1, 0, 0, 0, 0, -1, -1, 1}, 
                        {0, -1, 1, -2, 2, -1, 1, -1, 1, 0}};

int N;
int board[500][500];
int out = 0;

void userInput(){
    cin >> N;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> board[i][j];
        }
    }
}

void solution(){
    int dir = 0;
    int cy = N/2, cx = N/2;
    for(int i = 1; i < N; i++){
        for(int j = 0; j < 3; j++){
            if(i < N-1 && j == 2){
                continue;
            }
            for(int k = 1; k <= i; k++){
                cy += dy[dir];
                cx += dx[dir];
                int curSand = board[cy][cx];
                int a = curSand;
                board[cy][cx] = 0;
                for(int l = 0; l < 9; l++){
                    int sandPosY = cy + scatterY[dir][l];
                    int sandPosX = cx + scatterX[dir][l];
                    if(sandPosY < 0 || sandPosX < 0 || sandPosY >= N || sandPosX >= N){
                        out += curSand * order[l] / 100;
                        a -= curSand * order[l] / 100;
                        continue;
                    }
                    board[sandPosY][sandPosX] += curSand * order[l] / 100;
                    a -= curSand * order[l] / 100;
                }
                int sandPosY = cy + scatterY[dir][9];
                int sandPosX = cx + scatterX[dir][9];
                if(sandPosY < 0 || sandPosX < 0 || sandPosY >= N || sandPosX >= N){
                    out += a;
                }
                else{
                    board[sandPosY][sandPosX] += a;
                }
            }
            dir = (dir+1) % 4;
        }
    }
}

int main(){
    userInput();
    solution();
    cout << out;
    return 0;
}