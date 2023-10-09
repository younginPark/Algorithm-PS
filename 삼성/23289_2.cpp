#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <cmath>
using namespace std;

int dy[4] = { 0, 0, -1, +1 };
int dx[4] = { +1, -1, 0, 0 };

// 오른쪽 왼쪽 위 아래
int heaterDirY[4][3] = { { -1, 0, +1 }, { -1, 0, +1 }, { -1, -1, -1 }, { +1, +1, +1 } };
int heaterDirX[4][3] = { { +1, +1, +1 }, { -1, -1, -1 }, { -1, 0, +1 }, { -1, 0, +1 } };

struct HEATER{
    int y, x, d;
};

int R, C, K, W;
int board[25][25];
int new_board[25][25];
int wall[25][25][4]; // 위 오른쪽 아래 왼쪽
int choco = 0;
vector<pair<int, int> > check;
vector<HEATER> heater;

void userInput(){
    cin >> R >> C >> K;
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            cin >> board[i][j];
            if(1 <= board[i][j] && board[i][j] <= 4){
                HEATER tmp;
                tmp.y = i, tmp.x = j, tmp.d = board[i][j]-1;
                heater.push_back(tmp);
                board[i][j] = 0;
            }
            else if(board[i][j] == 5){
                check.push_back(make_pair(i, j));
                board[i][j] = 0;
            }
        }
    }
    cin >> W;
    for(int i = 0; i < W; i++){
        int y, x, t;
        cin >> y >> x >> t;
        y--; x--;
        if(t == 0){
            wall[y][x][0] = 1;
            wall[y-1][x][2] = 1;
        }
        else{
            wall[y][x][1] = 1;
            wall[y][x+1][3] = 1;
        }
    }
}

void makeHeating(int y, int x, int d){
    int visited[25][25];
    memset(visited, 0, sizeof(visited));
    queue<pair<pair<int, int>, int> > q;
    int ny = y + dy[d];
    int nx = x + dx[d];
    q.push(make_pair(make_pair(ny, nx), 5));
    while(!q.empty()){
        int cy = q.front().first.first;
        int cx = q.front().first.second;
        int cnt = q.front().second;
        new_board[cy][cx] += cnt;
        q.pop();
        if(cnt <= 1){
            continue;
        }
        for(int times = 0; times < 3; times++){
            int ny = cy + heaterDirY[d][times];
            int nx = cx + heaterDirX[d][times];
            if(ny < 0 || nx < 0 || ny >= R || nx >= C){
                continue;
            }
            if(times == 0){
                // 오른쪽 왼쪽 위 아래
                // 벽 있는지 확인, 방문한 곳인지 확인 후 그렇다면 visited표시 후 큐에 넣기
                if(d == 0){
                    if((wall[cy-1][cx][2] != 1 && wall[cy-1][cx][1] != 1) && visited[ny][nx] == 0){
                        visited[ny][nx] = 1;
                        q.push(make_pair(make_pair(ny, nx), cnt-1));
                    }
                }
                else if(d == 1){
                    if((wall[cy-1][cx][3] != 1 && wall[cy-1][cx][2] != 1) && visited[ny][nx] == 0){
                        visited[ny][nx] = 1;
                        q.push(make_pair(make_pair(ny, nx), cnt-1));
                    }
                }
                else if(d == 2){
                    if((wall[cy][cx-1][0] != 1 && wall[cy][cx-1][1] != 1) && visited[ny][nx] == 0){
                        visited[ny][nx] = 1;
                        q.push(make_pair(make_pair(ny, nx), cnt-1));
                    }
                }
                else if(d == 3){
                    if((wall[cy][cx-1][2] != 1 && wall[cy][cx-1][1] != 1) && visited[ny][nx] == 0){
                        visited[ny][nx] = 1;
                        q.push(make_pair(make_pair(ny, nx), cnt-1));
                    }
                }
            }
            else if(times == 1){
                if(d == 0){
                    if(wall[cy][cx][1] != 1 && visited[ny][nx] == 0){
                        visited[ny][nx] = 1;
                        q.push(make_pair(make_pair(ny, nx), cnt-1));
                    }
                }
                else if(d == 1){
                    if(wall[cy][cx][3] != 1 && visited[ny][nx] == 0){
                        visited[ny][nx] = 1;
                        q.push(make_pair(make_pair(ny, nx), cnt-1));
                    }
                }
                else if(d == 2){
                    if(wall[cy][cx][0] != 1 && visited[ny][nx] == 0){
                        visited[ny][nx] = 1;
                        q.push(make_pair(make_pair(ny, nx), cnt-1));
                    }
                }
                else if(d == 3){
                    if(wall[cy][cx][2] != 1 && visited[ny][nx] == 0){
                        visited[ny][nx] = 1;
                        q.push(make_pair(make_pair(ny, nx), cnt-1));
                    }
                }
            }
            else if(times == 2){
                if(d == 0){
                    if((wall[cy+1][cx][0] != 1 && wall[cy+1][cx][1] != 1) && visited[ny][nx] == 0){
                        visited[ny][nx] = 1;
                        q.push(make_pair(make_pair(ny, nx), cnt-1));
                    }
                }
                else if(d == 1){
                    if((wall[cy+1][cx][3] != 1 && wall[cy+1][cx][0] != 1) && visited[ny][nx] == 0){
                        visited[ny][nx] = 1;
                        q.push(make_pair(make_pair(ny, nx), cnt-1));
                    }
                }
                else if(d == 2){
                    if((wall[cy][cx+1][3] != 1 && wall[cy][cx+1][0] != 1) && visited[ny][nx] == 0){
                        visited[ny][nx] = 1;
                        q.push(make_pair(make_pair(ny, nx), cnt-1));
                    }
                }
                else if(d == 3){
                    if((wall[cy][cx+1][3] != 1 && wall[cy][cx+1][2] != 1) && visited[ny][nx] == 0){
                        visited[ny][nx] = 1;
                        q.push(make_pair(make_pair(ny, nx), cnt-1));
                    }
                }
            }
        }
    }
    // cout << "*****\n";
    // for(int i = 0; i < R; i++){
    //     for(int j = 0; j < C; j++){
    //         cout << new_board[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
}

void heaterOn(){
    memset(new_board, 0, sizeof(new_board));
    for(int i = 0; i < heater.size(); i++){
        int y = heater[i].y;
        int x = heater[i].x;
        int d = heater[i].d;
        makeHeating(y, x, d); // new_board에 더할 온도들 저장해둠
    }
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            board[i][j] += new_board[i][j];
        }
    }
}

void controlTemp(){
    memset(new_board, 0, sizeof(new_board));
    // 모든 인접한 칸에 대해서, 온도가 높은 칸에서 낮은 칸으로 ⌊(두 칸의 온도의 차이)/4⌋만큼 온도가 조절된다. 
    // 온도가 높은 칸은 이 값만큼 온도가 감소하고, 낮은 칸은 온도가 상승한다. 
    // 인접한 두 칸 사이에 벽이 있는 경우에는 온도가 조절되지 않는다. 이 과정은 모든 칸에 대해서 동시에 발생한다.
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            for(int dir = 0; dir < 4; dir+= 3){
                int ny = i + dy[dir];
                int nx = j + dx[dir];
                if(ny < 0 || nx < 0 || ny >= R || nx >= C){
                    continue;
                }
                // 벽 체크
                if((dir == 0 && wall[i][j][1] == 1) || (dir == 3 && wall[i][j][2] == 1)){
                    continue;
                }
                int value = abs(board[i][j] - board[ny][nx]) / 4;
                if(board[i][j] > board[ny][nx]){
                    new_board[i][j] -= value;
                    new_board[ny][nx] += value;
                }
                else if(board[i][j] < board[ny][nx]){
                    new_board[i][j] += value;
                    new_board[ny][nx] -= value;
                }
            }
        }
    }
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            board[i][j] += new_board[i][j];
        }
    }
}

void minusTemp(){
    for(int i = 0; i < R; i++){
        if(board[i][0] > 0){
            board[i][0]--;
        }
        if(board[i][C-1] > 0){
            board[i][C-1]--;
        }
    }
    for(int i = 1; i < C-1; i++){
        if(board[0][i] > 0){
            board[0][i]--;
        }
        if(board[R-1][i] > 0){
            board[R-1][i]--;
        }
    }
}

bool checkTemp(){
    for(int i = 0; i < check.size(); i++){
        if(board[check[i].first][check[i].second] < K){
            return false;
        }
    }
    return true;
}

void printBoard(){
    cout << "------------------\n";
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

void solution(){
    while(1){
        heaterOn();
        controlTemp();
        minusTemp();
        choco++;
        if(choco >= 101){
            break;
        }
        if(checkTemp()){
            break;
        }
    }
}

int main(){
    userInput();
    solution();
    cout << choco;
    return 0;
}