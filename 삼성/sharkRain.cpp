#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

/*
1. 구름의 이동 (격자 벗어나도 연결되어 있음)
2. 구름이 있는 칸에 물의 양 1 증가
3. 구름은 사라짐
4. 2에서 물의 양이 증가한 칸에 물복사마법 하는데,
해당 칸에서 대각선 방향으로 거리가 1인 칸에 물이 있는 바구니의 수 만큼 양이 증가함 (격자 넘어가는 칸은 확인X)
5. 구름이 방금 사라진 곳이 아니면서 물의 양이 2이상인 모든 칸에 구름이 생기고 물의 양이 2 줄어듬
반복
*/

int dy[8] = { 0, -1, -1, -1, 0, +1, +1, +1 };
int dx[8] = { -1, -1, 0, +1, +1, +1, 0, -1 };

int N, M;
int board[51][51];
int cloud[51][51];
int copy_cloud[51][51];
struct COMM {
    int d, s;
};
vector<COMM> command;

void userInput(){
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> board[i][j];
        }
    }
    for(int i = 0; i < M; i++){
        COMM tmp;
        cin >> tmp.d >> tmp.s;
        tmp.d--;
        command.push_back(tmp);
    }

    cloud[N-1][0] = 1;
    cloud[N-1][1] = 1;
    cloud[N-2][0] = 1;
    cloud[N-2][1] = 1;
}

void moveCloud(int round){
    memset(copy_cloud, 0, sizeof(copy_cloud));
    int cd = command[round].d;
    int cs = command[round].s;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(cloud[i][j] == 1){
                int ny = ((i + dy[cd] * cs) + (N*51)) % N;
                int nx = ((j + dx[cd] * cs) + (N*51)) % N;
                copy_cloud[ny][nx] = 1;
            }
        }
    }
}

void addWaterUnderCloud(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(copy_cloud[i][j] == 1){
                board[i][j] += 1;
            }
        }
    }
}

void waterCopyMagic(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(copy_cloud[i][j] == 1){
                int cnt = 0;
                for(int dir = 1; dir < 8; dir += 2){
                    int ny = i + dy[dir];
                    int nx = j + dx[dir];
                    if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                        continue;
                    }
                    else if(board[ny][nx] >= 1){
                        cnt++;
                    }
                }
                board[i][j] += cnt;
            }
        }
    }
}

void makeCloud(){
    memset(cloud, 0, sizeof(cloud));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(board[i][j] >= 2 && copy_cloud[i][j] != 1){
                cloud[i][j] = 1;
                board[i][j] -= 2;
            }
        }
    }
}

void getAns(){
    int ans = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            ans += board[i][j];
        }
    }

    cout << ans;
}

int main(){
    userInput();
    for(int i = 0; i < M; i++){
        moveCloud(i);
        addWaterUnderCloud();
        waterCopyMagic();
        makeCloud();
    }
    getAns();
    return 0;
}