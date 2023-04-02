#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

int dy[4] = { 0, -1, 0, 1 };
int dx[4] = { 1, 0, -1, 0 };

struct DICE {
    int y, x, dir;
};
DICE dice;
int N, M, K;
int board[21][21];
int dice_arr[6] = { 4, 3, 1, 6, 2, 5 };
int ans = 0;

void userInput(){
    cin >> N >> M >> K;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> board[i][j];
        }
    }
}

void move(){
    // 주사위 굴러가기
    int dir = dice.dir;
    int ny = dice.y + dy[dir];
    int nx = dice.x + dx[dir];
    if(ny < 0 || ny >= N || nx < 0 || nx >= M){
        dir = (dir + 2) % 4;
        ny = dice.y + dy[dir];
        nx = dice.x + dx[dir];
    }
    dice.dir = dir;
    dice.y = ny;
    dice.x = nx;
    // 주사위 전개도 변경
    if(dir == 0){
        swap(dice_arr[2], dice_arr[3]);
        swap(dice_arr[0], dice_arr[2]);
        swap(dice_arr[1], dice_arr[3]);
    }
    else if(dir == 1){
        swap(dice_arr[4], dice_arr[5]);
        swap(dice_arr[2], dice_arr[4]);
        swap(dice_arr[3], dice_arr[5]);
    }
    else if(dir == 2){
        swap(dice_arr[0], dice_arr[1]);
        swap(dice_arr[0], dice_arr[2]);
        swap(dice_arr[1], dice_arr[3]);
    }
    else if(dir == 3){
        swap(dice_arr[2], dice_arr[3]);
        swap(dice_arr[2], dice_arr[4]);
        swap(dice_arr[3], dice_arr[5]);
    }
}

void getScore(){
    int num = board[dice.y][dice.x];
    int cnt = 1;
    queue<pair<int, int> > q;
    int visit[21][21];
    memset(visit, 0, sizeof(visit));
    q.push(make_pair(dice.y, dice.x));
    visit[dice.y][dice.x] = 1;

    while(!q.empty()){
        int frontY = q.front().first;
        int frontX = q.front().second;
        q.pop();
        for(int d = 0; d < 4; d++){
            int ny = frontY + dy[d];
            int nx = frontX + dx[d];
            if(ny < 0 || ny >= N || nx < 0 || nx >= M){
                continue;
            }
            if(board[ny][nx] == num && visit[ny][nx] == 0){
                q.push(make_pair(ny, nx));
                visit[ny][nx] = 1;
                cnt++;
            }
        }
    }
    ans += (num * cnt);
}

void changeDir(){
    int a = dice_arr[3];
    int b = board[dice.y][dice.x];
    if(a < b){
        dice.dir = ((dice.dir+1) + 4) % 4;
    }
    else if(a > b){
        dice.dir = ((dice.dir-1) + 4) % 4;
    }
}

int main(){
    dice.y = 0, dice.x = 0, dice.dir = 0;
    userInput();
    for(int times = 0; times < K; times++){
        move();
        getScore();
        changeDir();
    }
    cout << ans;
    return 0;
}