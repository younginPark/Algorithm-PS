#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int dy[5] = { 0, -1, 1, 0, 0 };
int dx[5] = { 0, 0, 0, -1, 1 };

int moveY[4] = { 0, 1, 0, -1 };
int moveX[4] = { -1, 0, 1, 0 };

int N, M;
int board[55][55];
int flatBoard[2605];
int changeFlatBoard[2605];
int shark_y, shark_x;
vector<pair<int, int> > command;

int number1 = 0, number2 = 0, number3 = 0;

void makeFlat(){
    memset(flatBoard, 0, sizeof(flatBoard));
    int dir = -1; 
    int curY = shark_y, curX = shark_x;
    int block = 0;
    for(int i = 1; i < N; i++){
        for(int j = 0; j < 3; j++){
            if(i != N-1 && j == 2){
                break;
            }
            dir = (dir+1) % 4;
            for(int k = 0; k < i; k++){
                curY += moveY[dir];
                curX += moveX[dir];
                flatBoard[block] = board[curY][curX];
                block++;
            }
        }
    }
}

void userInput(){
    cin >> N >> M;
    shark_y = (N+1) / 2;
    shark_x = (N+1) / 2;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            cin >> board[i][j];
        }
    }
    for(int i = 0; i < M; i++){
        int d, s;
        cin >> d >> s;
        command.push_back(make_pair(d, s));
    }
}

void removeBall(int dir, int space){
    for(int i = 1; i <= space; i++){
        int ny = shark_y + (dy[dir] * i);
        int nx = shark_x + (dx[dir] * i);
        if(ny <= 0 || ny > N || nx <= 0 || nx > N){
            continue;
        }
        board[ny][nx] = 0;
    }
}

void moveBall(){
    for(int i = 1; i < N*N; i++){
        int now = i;
        while(now-1 >= 0 && flatBoard[now-1] == 0){
            flatBoard[now-1] = flatBoard[now];
            flatBoard[now] = 0;
            now--;
        }
    }
}

void bombBall(){
    while(1){
        int chk = 0;
        int cnt = 1;
        int color = flatBoard[0];
        for(int i = 1; i < N*N; i++){
            if(color != 0 && flatBoard[i] == color){
                cnt++;
            }
            else{
                if(cnt >= 4){
                    chk = 1;
                    for(int j = cnt; j > 0; j--){
                        flatBoard[i-j] = 0;
                    }
                    if(color == 1){
                        number1 += cnt;
                    }
                    else if(color == 2){
                        number2 += cnt;
                    }
                    else if(color == 3){
                        number3 += cnt;
                    }
                }
                color = flatBoard[i];
                cnt = 1;
            }
        }
        if(chk == 0){
            break;
        }
        moveBall();
    }
}

void changeBall(){
    memset(changeFlatBoard, 0, sizeof(changeFlatBoard));
    int idx = 0;
    int cnt = 1;
    int color = flatBoard[0];
    for(int i = 1; i < N*N; i++){
        if(color == flatBoard[i]){
            cnt++;
        }
        else{
            changeFlatBoard[idx] = cnt;
            changeFlatBoard[idx+1] = color;
            idx += 2;
            cnt = 1;
            color = flatBoard[i];
        }
    }
}

void putBall(){
    memset(board, 0, sizeof(board));
    int block = 0;
    int dir = -1; 
    int curY = shark_y, curX = shark_x;
    for(int i = 1; i < N; i++){
        for(int j = 0; j < 3; j++){
            if(i != N-1 && j == 2){
                break;
            }
            dir = (dir+1) % 4;
            for(int k = 0; k < i; k++){
                curY += moveY[dir];
                curX += moveX[dir];
                board[curY][curX] = changeFlatBoard[block];
                block++;
            }
        }
    }
}

int main(){
    userInput();
    for(int times = 0; times < M; times++){
        removeBall(command[times].first, command[times].second); // 마법 수행해서 구슬 없애기
        makeFlat(); // 1차원 배열에 순서대로 집어넣기
        moveBall(); // 빈 곳 땡기기
        bombBall(); // 구슬 폭발 (폭발, 땡기기 반복)
        changeBall(); // 구슬 갯수, 색깔번호 이 순서로 새로 배열에 만들기
        putBall(); // 순서대로 board에 다시 구슬 넣기
    }
    int ans = (1 * number1) + (2 * number2) + (3 * number3);
    cout << ans; 
    return 0;
}