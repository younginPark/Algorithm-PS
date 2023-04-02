#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int R, C, K, W;
int board[25][25];
int wallMap[25][25][4];

vector<pair<int, int> > searchPos;
vector<pair<pair<int, int>, int> > heater;
vector<pair<pair<int, int>, int> > wall;

int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

int wdx[4][3] = { { -1, 0, 1 }, { -1, 0, 1 }, { 1, 1, 1 }, { -1, -1, -1 } };
int wdy[4][3] = { { 1, 1, 1 }, { -1, -1, -1 }, { -1, 0, 1 }, { -1, 0, 1 } };

void userInput(){
    cin >> R >> C >> K;
    for(int i = 1; i <= R; i++){
        for(int j = 1; j <= C; j++){
            cin >> board[i][j];
            if(board[i][j] != 0 && board[i][j] != 5){
                heater.push_back(make_pair(make_pair(i, j), board[i][j]));
            }
            else if(board[i][j] == 5){
                searchPos.push_back(make_pair(i, j));
            }
            board[i][j] = 0;
        }
    }
    cin >> W;
    for(int i = 0; i < W; i++){
        int X, Y, T; 
        cin >> X >> Y >> T;
        wall.push_back(make_pair(make_pair(X, Y), T));
    }
} 

void settingWall(){
    for(int i = 0; i < W; i++){
        int x = wall[i].first.first;
        int y = wall[i].first.second;
        int t = wall[i].second;

        if(t == 0){
            wallMap[x][y][3] = true;
            wallMap[x-1][y][2] = true;
        }
        else if(t == 1){
            wallMap[x][y][0] = true;
            wallMap[x][y+1][1] = true;
        }
    }
}

bool checkWall(int x, int y, int nx, int ny, int d, int dir){
    if(dir == 1){
        if(wallMap[x][y][d] == false) return true;
    }
    else if(dir == 0){
        if(d == 0){
            int upx = x-1;
            int upy = y;
            if(wallMap[x][y][3] == false && wallMap[upx][upy][0] == false) return true;
        }
        else if(d == 1){
            int upx = x-1;
            int upy = y;
            if(wallMap[x][y][3] == false && wallMap[upx][upy][1] == false) return true;
        }
        else if(d == 2){
            int dnx = x;
            int dny = y-1;
            if(wallMap[x][y][1] == false && wallMap[dnx][dny][2] == false) return true;
        }
        else if(d == 3){
            int dnx = x;
            int dny = y-1;
            if(wallMap[x][y][1] == false && wallMap[dnx][dny][3] == false) return true;
        }
    }
    else if(dir == 2){
        if(d == 0){
            int upx = x+1;
            int upy = y;
            if(wallMap[x][y][2] == false && wallMap[upx][upy][0] == false) return true;
        }
        else if(d == 1){
            int upx = x+1;
            int upy = y;
            if(wallMap[x][y][2] == false && wallMap[upx][upy][1] == false) return true;
        }
        else if(d == 2){
            int dnx = x;
            int dny = y+1;
            if(wallMap[x][y][0] == false && wallMap[dnx][dny][2] == false) return true;
        }
        else if(d == 3){
            int dnx = x;
            int dny = y+1;
            if(wallMap[x][y][0] == false && wallMap[dnx][dny][3] == false) return true;
        }
    }
    return false;
}

void spread(int x, int y, int d){
    bool update[25][25] = { false, };
    switch (d) {
    case 1:
        d= 0;
        break;
    case 2:
        d = 1;
        break;
    case 3:
        d = 3;
        break;
    case 4:
        d = 2;
        break;
    }
    x += dx[d];
    y += dy[d];
    if(x < 1 || y < 1 || x > R || y > C) return;

    queue<pair<pair<int, int>, int> > q;
    q.push(make_pair(make_pair(x, y), 5));

    while(!q.empty()){
        int x = q.front().first.first;
        int y = q.front().first.second;
        int wind = q.front().second;
        q.pop();

        board[x][y] += wind;
        if(wind == 1) continue;
        
        for(int i = 0; i < 3; i++){
            int nx = x + wdx[d][i];
            int ny = y + wdy[d][i];
            if(nx < 1 || ny < 1 || nx > R || ny > C){
                continue;
            }
            if(update[nx][ny] == false && checkWall(x, y, nx, ny, d, i) == true){
                update[nx][ny] = true;
                q.push(make_pair(make_pair(nx, ny), wind-1));
            }
        }
    }
}

void spreadWind(){
    for(int i = 0; i < heater.size(); i++){
        int x = heater[i].first.first;
        int y = heater[i].first.second;
        int d = heater[i].second;
        spread(x, y, d);
    }
}

void controlTemperature(){
    int tempMap[25][25] = { 0, };
    for(int x = 1; x <= R; x++){
        for(int y = 1; y <= C; y++){
            for(int i = 0; i < 2; i++){
                int dir = i == 0 ? 0 : 2;
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                if(nx >= 1 && ny >= 1 && nx <= R && ny <= C){
                    if(wallMap[x][y][dir] == false){
                        pair<int, int> maxCoord, minCoord;
                        if(board[x][y] > board[nx][ny]){
                            maxCoord = make_pair(x, y);
                            minCoord = make_pair(nx, ny);
                        }
                        else{
                            minCoord = make_pair(x, y);
                            maxCoord = make_pair(nx, ny);
                        }
                        int diff = abs(board[x][y] -board[nx][ny]);
                        diff /= 4;
                        tempMap[maxCoord.first][maxCoord.second] -= diff;
                        tempMap[minCoord.first][minCoord.second] += diff;
                    }
                }
            }
        }
    }
    for(int i = 1; i <= R; i++){
        for(int j = 1; j <= C; j++){
            board[i][j] += tempMap[i][j];
        }
    }
}

void decreaseTemperature(){
    for(int i = 1; i <= C; i++){
        if(board[1][i] > 0) board[1][i]--;
        if(board[R][i] > 0) board[R][i]--;
    }
    for(int i = 2; i < R; i++){
        if(board[i][1] > 0) board[i][1]--;
        if(board[i][C] > 0) board[i][C]--;
    }
}

bool check(){
    for(int i = 0; i < searchPos.size(); i++){
        int x = searchPos[i].first;
        int y = searchPos[i].second;
        if(board[x][y] < K){
            return false;
        }
    }
    return true;
}

void solve(){
    settingWall();
    int chocolate = 0;
    while(1){
        if(chocolate > 100){
            break;
        }
        spreadWind();
        controlTemperature();
        decreaseTemperature();
        chocolate++;
        if(check() == true){
            break;
        }
    }
    cout << chocolate << endl;
}

int main(){

    userInput();
    solve();

    return 0;
}

/* bfs응용! 4방향이 아니라 온풍기가 바라보는 방향에 따라 정해진 방향으로
   bfs에서 체크하고 온도 낮춘거 넣어주면 끝 
   벽 확인하는건 3차원 배열 이용하여 해당 위치의 동서남북에 벽이 세워있는걸
   미리 배열에 세팅해주고 나중에 확인만 해주면 됨*/