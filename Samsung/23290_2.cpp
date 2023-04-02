#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

int dy[8] = { 0, -1, -1, -1, 0, +1, +1, +1 };
int dx[8] = { -1, -1, 0, +1, +1, +1, 0, -1 };

int sharkdy[4] = { -1, 0, +1, 0 };
int sharkdx[4] = { 0, -1, 0, +1 };

int M, S;
int sharkY, sharkX;
int bestCnt;
int bestRoute[4];
struct FISH {
    int y, x, d;
};
vector<FISH> board[5][5];
vector<FISH> new_board[5][5];
queue<int> smell[5][5];

void userInput(){
    cin >> M >> S;
    for(int i = 0; i < M; i++){
        FISH tmp;
        cin >> tmp.y >> tmp.x >> tmp.d;
        tmp.y--; tmp.x--; tmp.d--;
        board[tmp.y][tmp.x].push_back(tmp);
    }
    cin >> sharkY >> sharkX;
    sharkY--, sharkX--;
}

void copyFish(){
    // 1에서 사용한 복제 마법이 완료된다. 모든 복제된 물고기는 1에서의 위치와 방향을 그대로 갖게 된다.
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(new_board[i][j].size() > 0){
                for(int k = 0; k < new_board[i][j].size(); k++){
                    board[i][j].push_back(new_board[i][j][k]);
                }
            }
        }
    }
}

void moveFish(){
    // 모든 물고기가 한 칸 이동한다. 
    // 상어가 있는 칸, 물고기의 냄새가 있는 칸, 격자의 범위를 벗어나는 칸으로는 이동할 수 없다. 
    // 각 물고기는 자신이 가지고 있는 이동 방향이 이동할 수 있는 칸을 향할 때까지 방향을 45도 반시계 회전시킨다. 
    // 만약, 이동할 수 있는 칸이 없으면 이동을 하지 않는다. 그 외의 경우에는 그 칸으로 이동을 한다. 물고기의 냄새는 아래 3에서 설명한다.

    // 벡터 초기화
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            new_board[i][j].clear();
        }
    }

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(board[i][j].size() > 0){
                for(int k = 0; k < board[i][j].size(); k++){
                    int cy = board[i][j][k].y;
                    int cx = board[i][j][k].x;
                    int cd = board[i][j][k].d;
                    int moveFlag = -1;
                    for(int dir = 0; dir < 8; dir++){
                        int ny = cy + dy[cd];
                        int nx = cx + dx[cd];
                        if(ny < 0 || nx < 0 || ny >= 4 || nx >= 4){
                            cd = ((cd-1)+8) % 8;
                            continue;
                        }
                        if((ny == sharkY && nx == sharkX) || smell[ny][nx].size() > 0){
                            cd = ((cd-1)+8) % 8;
                            continue;
                        }
                        FISH tmp;
                        tmp.y = ny, tmp.x = nx, tmp.d = cd;
                        new_board[ny][nx].push_back(tmp);
                        moveFlag = 1;
                        break;
                    }
                    if(moveFlag == -1){
                        FISH tmp;
                        tmp.y = cy, tmp.x = cx, tmp.d = cd;
                        new_board[cy][cx].push_back(tmp);
                    }
                }
            }
        }
    }
}

void findRoute(int y, int x, int cnt, int fishTotal, int route[4]){
    if(cnt >= 3){
        // 비교해서 bestRoute update 혹은 route 초기화
        if(fishTotal > bestCnt){
            bestCnt = fishTotal;
            for(int i = 1; i <= 3; i++){
                bestRoute[i] = route[i];
            }
        }
        return;
    }
    for(int dir = 0; dir < 4; dir++){
        int ny = y + sharkdy[dir];
        int nx = x + sharkdx[dir];
        if(ny < 0 || nx < 0 || ny >= 4 || nx >= 4){
            continue;
        }
        route[cnt+1] = dir;

        int tmp_size = new_board[ny][nx].size();
        vector<FISH> tmp_fish;
        for(int t = 0; t < tmp_size; t++){
            tmp_fish.push_back(new_board[ny][nx][t]);
        }
        new_board[ny][nx].clear();

        findRoute(ny, nx, cnt+1, fishTotal+tmp_size, route);
        
        for(int t = 0; t < tmp_size; t++){
            new_board[ny][nx].push_back(tmp_fish[t]);
        }
    }
}

void moveShark(int order){
    // 상어가 연속해서 3칸 이동한다. 상어는 현재 칸에서 상하좌우로 인접한 칸으로 이동할 수 있다. 
    // 연속해서 이동하는 칸 중에 격자의 범위를 벗어나는 칸이 있으면, 그 방법은 불가능한 이동 방법이다. 
    // 연속해서 이동하는 중에 상어가 물고기가 있는 같은 칸으로 이동하게 된다면, 그 칸에 있는 모든 물고기는 격자에서 제외되며, 
    // 제외되는 모든 물고기는 물고기 냄새를 남긴다. 
    // 가능한 이동 방법 중에서 제외되는 물고기의 수가 가장 많은 방법으로 이동하며, 
    // 그러한 방법이 여러가지인 경우 사전 순으로 가장 앞서는 방법을 이용한다.
    bestCnt = -1;
    int route[4];
    memset(bestRoute, -1, sizeof(bestRoute));
    findRoute(sharkY, sharkX, 0, 0, route);

    // 상어 이동 루트 찾은걸로 진짜 수행
    for(int i = 1; i <= 3; i++){
        sharkY += sharkdy[bestRoute[i]];
        sharkX += sharkdx[bestRoute[i]];
        if(new_board[sharkY][sharkX].size() > 0){
            smell[sharkY][sharkX].push(order);
            new_board[sharkY][sharkX].clear();
        }
    }
}

void removeFishSmell(int order){
    // 두 번 전 연습에서 생긴 물고기의 냄새가 격자에서 사라진다.
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            int loopCnt = smell[i][j].size();
            for(int k = 0; k < loopCnt; k++){
                if(smell[i][j].front() <= order-2){
                    smell[i][j].pop();
                }
                else{
                    int tmp = smell[i][j].front();
                    smell[i][j].pop();
                    smell[i][j].push(tmp);
                }
            }
        }
    }
}

void getAns(){
    int total = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            total += board[i][j].size();
        }
    }
    cout << total;
}

void solution(){
    for(int i = 0; i < S; i++){
        moveFish();
        moveShark(i);
        removeFishSmell(i);
        copyFish();
    }
    getAns();
}

int main(){
    userInput();
    solution();
    return 0;
}