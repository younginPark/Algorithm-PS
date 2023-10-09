#include <iostream>
using namespace std;

int dy[4] = { 0, 0, -1, +1 };
int dx[4] = { +1, -1, 0, 0 };

int N, M, K;
int board[25][25];
int cmd[1005];
int dice_arr[7] = { 0, 0, 0, 0, 0, 0 };

struct DICE {
    int y, x;
};

DICE dice;

void userInput(){
    cin >> N >> M >> dice.y >> dice.x >> K;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> board[i][j];
        }
    }
    for(int i = 0; i < K; i++){
        cin >> cmd[i];
        cmd[i]--;
    }
}

void moveDice(int dir){
    if(dir == 0){ // 동 ->
        int copy_arr[7];
        for(int i = 0; i < 6; i++){
            copy_arr[i] = dice_arr[i];
        }
        dice_arr[5] = copy_arr[1];
        dice_arr[4] = copy_arr[3];
        dice_arr[1] = copy_arr[4];
        dice_arr[3] = copy_arr[5];
    }
    else if(dir == 1){ // 서 <-
        int copy_arr[7];
        for(int i = 0; i < 6; i++){
            copy_arr[i] = dice_arr[i];
        }
        dice_arr[4] = copy_arr[1];
        dice_arr[5] = copy_arr[3];
        dice_arr[3] = copy_arr[4];
        dice_arr[1] = copy_arr[5];
    }
    else if(dir == 2){ // 북 ^
        int copy_arr[7];
        for(int i = 0; i < 6; i++){
            copy_arr[i] = dice_arr[i];
        }
        dice_arr[3] = copy_arr[0];
        dice_arr[0] = copy_arr[1];
        dice_arr[1] = copy_arr[2];
        dice_arr[2] = copy_arr[3];
    }
    else if(dir == 3){ // 남 v
        int copy_arr[7];
        for(int i = 0; i < 6; i++){
            copy_arr[i] = dice_arr[i];
        }
        dice_arr[1] = copy_arr[0];
        dice_arr[2] = copy_arr[1];
        dice_arr[3] = copy_arr[2];
        dice_arr[0] = copy_arr[3];
    }
}

void solution(){
    for(int times = 0; times < K; times++){
        int ny = dice.y + dy[cmd[times]];
        int nx = dice.x + dx[cmd[times]];
        if(ny < 0 || nx < 0 || ny >= N || nx >= M){
            continue;
        }
        // cmd로 이동할 위치를 가지고 주사위를 굴린다.
        dice.y = ny;
        dice.x = nx;
        moveDice(cmd[times]);
        if(board[dice.y][dice.x] == 0){
            board[dice.y][dice.x] = dice_arr[3];
        }
        else {
            dice_arr[3] = board[dice.y][dice.x];
            board[dice.y][dice.x] = 0;
        }
        cout << dice_arr[1] << "\n";
    }
}

int main(){
    userInput();
    solution();
    return 0;
}