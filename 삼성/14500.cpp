#include <iostream>
#include <algorithm>
using namespace std;

int dy[20][4] = {
    { 0, 0, 0, 0 },
    { 0, 1, 2, 3 },
    { 0, 0, 1, 1 },
    { 0, 1, 2, 2 },
    { 0, 1, 2, 2 },
    { 0, 0, 1, 2 },
    { 0, 0, 1, 2 },
    { 0, 0, 0, 1 },
    { 0, 1, 1, 1 },
    { 0, 1, 1, 1 },
    { 0, 0, 0, 1 }, //
    { 0, 1, 1, 2 },
    { -1, -1, 0, 0 },
    { 0, 1, 1, 2 },
    { 0, 0, 1, 1 },
    { 0, 0, 0, 1 },
    { -1, 0, 0, 1 },
    { -1, 0, 0, 1 },
    { 0, 1, 1, 1 }
};

int dx[20][4] = {
    { 0, 1, 2, 3 },
    { 0, 0, 0, 0 },
    { 0, 1, 0, 1 },
    { 0, 0, 0, 1 },
    { 0, 0, 0, -1 },
    { 0, 1, 0, 0 },
    { 0, 1, 1, 1 },
    { 0, 1, 2, 0 },
    { 0, -2, -1, 0 },
    { 0, 0, 1, 2 },
    { 0, 1, 2, 2 }, //
    { 0, 0, 1, 1 },
    { 1, 2, 0, 1 },
    { 0, -1, 0, -1 },
    { 0, 1, 1, 2 },
    { 0, 1, 2, 1 },
    { 1, 0, 1, 1 },
    { 0, 0, 1, 0 },
    { 0, -1, 0, 1 }
};

int N, M;
int board[505][505];
int ans = 0;

void userInput(){
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> board[i][j];
        }
    }
}

int main(){
    userInput();
    for(int i = 0; i < 19; i++){
        for(int y = 0; y < N; y++){
            for(int x = 0; x < M; x++){
                int total= 0;
                for(int pos = 0; pos < 4; pos++){
                    int ny = y + dy[i][pos];
                    int nx = x + dx[i][pos];
                    if(ny < 0 || nx < 0 || ny >= N || nx >= M){
                        total = -1;
                        break;
                    }
                    total += board[ny][nx];
                }
                ans = max(ans, total);
            }
        }
    }
    cout << ans;
    return 0;
}