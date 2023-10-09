#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

int dy[4] = { 0, -1, 0, +1 };
int dx[4] = { +1, 0, -1, 0 };

int N, M, K;
int board[21][21];
int copy_board[21][21];
int shootHeadY, shootHeadX;
struct LINEINFO {
    int headY, headX;
    int tailY, tailX;
    bool adj;
};
vector<LINEINFO> info; 
int ans = 0;

void userInput(){
    cin >> N >> M >> K;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> board[i][j];
            if(board[i][j] == 1){
                LINEINFO tmp;
                tmp.headY = i; tmp.headX = j;
                tmp.tailY = -1; tmp.tailX = -1;
                tmp.adj = true;
                info.push_back(tmp);
            }
        }
    }
}

void printBoard(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

void copyBoard(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            copy_board[i][j] = board[i][j];
        }
    }
}

void rollbackBoard(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            board[i][j] = copy_board[i][j];
        }
    }
}

/*
팀 정보를 팀의 머리, 꼬리 좌표를 넣는 구조체를 만들어서 방문 여부 확인하면서 bfs 돌려서 쭉 넣고 시작
이때 4있는지 확인해서 머리꼬리가 붙어있는지 아닌지 확인
*/
void findTeamBFS(int y, int x, int idx){
    int loc_visited[21][21];
    memset(loc_visited, 0, sizeof(loc_visited));
    queue<pair<int, int> > q;
    q.push(make_pair(y, x));
    loc_visited[y][x] = 1;
    while(!q.empty()){
        int cy = q.front().first;
        int cx = q.front().second;
        q.pop();
        for(int dir = 0; dir < 4; dir++){
            int ny = cy + dy[dir];
            int nx = cx + dx[dir];
            if(ny < 0 || nx < 0 || ny >= N || nx >= N || loc_visited[ny][nx] == 1 || board[ny][nx] == 0){
                continue;
            }
            else if(board[ny][nx] == 3){
                info[idx].tailY = ny;
                info[idx].tailX = nx;
                loc_visited[ny][nx] = 1;
                q.push(make_pair(ny, nx));
            }
            else if(board[ny][nx] == 4){
                info[idx].adj = false;
                loc_visited[ny][nx] = 1;
                q.push(make_pair(ny, nx));
            }
            else if(board[ny][nx] == 2){
                loc_visited[ny][nx] = 1;
                q.push(make_pair(ny, nx));
            }
        }
    }
}

void findTeam(){
    for(int i = 0; i < info.size(); i++){
        findTeamBFS(info[i].headY, info[i].headX, i);
    }
}

/*
1. 모든 팀은 머리사람 따라서 한칸 이동
이동할 때 머리와꼬리가 붙어있을 수도 있고 중간에 빈칸이 있을 수도 있음
- 머리와 꼬리가 붙어있다면
1이 3의자리로 가고 3옆의 2의자리에 3이 가고 2가 1자리로 감
각각의 이동할 좌표들을 미리 갖고 있다가 한번에 딱딱딱 넣어주기
- 중간에 빈칸이 있다면
1은 4가 있는 곳으로 이동하고 2는 기존 1로 가고 3은 기존 2로 감
이것도 각각 좌표 미리 구해놓고 한번에 넣어주기
*/

void moveTeam(){
    copyBoard();
    for(int i = 0; i < info.size(); i++){
        if(info[i].adj == true){
            // 1 바로 옆의 2의 위치를 찾아야 함
            int secondY, secondX;
            for(int dir = 0; dir < 4; dir++){
                int ny = info[i].tailY + dy[dir];
                int nx = info[i].tailX + dx[dir];
                if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                    continue;
                }
                else if(board[ny][nx] == 2){
                    secondY = ny;
                    secondX = nx;
                    break;
                }
            }
            copy_board[info[i].tailY][info[i].tailX] = 1;
            copy_board[info[i].headY][info[i].headX] = 2;
            copy_board[secondY][secondX] = 3;

            info[i].headY = info[i].tailY;
            info[i].headX = info[i].tailX;
            info[i].tailY = secondY;
            info[i].tailX = secondX;
        }
        else if(info[i].adj == false){
            // 1은 4가 있는 곳으로 이동하고 2는 기존 1로 가고 3은 기존 2로 감
            int fourY, fourX; 
            int secondY, secondX;
            for(int dir = 0; dir < 4; dir++){
                int ny = info[i].headY + dy[dir];
                int nx = info[i].headX + dx[dir];
                if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                    continue;
                }
                else if(board[ny][nx] == 4){
                    fourY = ny;
                    fourX = nx;
                    break;
                }
            }
            for(int dir = 0; dir < 4; dir++){
                int ny = info[i].tailY + dy[dir];
                int nx = info[i].tailX + dx[dir];
                if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                    continue;
                }
                else if(board[ny][nx] == 2){
                    secondY = ny;
                    secondX = nx;
                    break;
                }
            }

            copy_board[fourY][fourX] = 1;
            copy_board[info[i].headY][info[i].headX] = 2;
            copy_board[secondY][secondX] = 3;
            copy_board[info[i].tailY][info[i].tailX] = 4;

            info[i].headY = fourY;
            info[i].headX = fourX;
            info[i].tailY = secondY;
            info[i].tailX = secondX;
        }
    }
    rollbackBoard();
}

/*
2. 각 라운드마다 정해진 선을 따라 공을 던짐
방향을 4가지로 놓고 오른쪽 위로 왼쪽 아래로 둠
2-1. 이때 공을 맞은 팀이 있으면 첫번째로 맞은 사람의 머리에서부터의 위치의 제곱을 정답변수에 더함
공을 맞은 사람으로부터 bfs를 돌면서 머리 찾음, 이때 bfs 돌 때 몇번째로부터 찾게된건지 큐에 변수 추가로 해줘야 함
2-2. 없으면 패스
*/

int findHeadBFS(int y, int x){
    int loc_visited[21][21];
    memset(loc_visited, 0, sizeof(loc_visited));
    queue<pair<pair<int, int>, int> > q;
    q.push(make_pair(make_pair(y, x), 1));
    loc_visited[y][x] = 1;
    while(!q.empty()){
        int cy = q.front().first.first;
        int cx = q.front().first.second;
        int ccnt = q.front().second;
        q.pop();
        for(int dir = 0; dir < 4; dir++){
            int ny = cy + dy[dir];
            int nx = cx + dx[dir];
            if(ny < 0 || nx < 0 || ny >= N || nx >= N || loc_visited[ny][nx] == 1 
            || board[ny][nx] == 0 || board[ny][nx] == 3){
                continue;
            }
            else if(board[ny][nx] == 1){
                if(board[y][x] == 3 && ccnt == 1){
                    continue;
                }
                shootHeadY = ny, shootHeadX = nx;
                return ccnt+1;
            }
            else if(board[ny][nx] == 2){
                loc_visited[ny][nx] = 1;
                q.push(make_pair(make_pair(ny, nx), ccnt+1));
            }
        }
    }
    return 0;
}

void getScore(int y, int x){
    if(board[y][x] == 1){
        shootHeadY = y, shootHeadX = x;
        ans += 1;
    }
    else{
        int score = findHeadBFS(y, x);
        ans += score * score;
    }
}

bool shootBall(int round){
    bool shootFlag = false; 
    int dir = (round / N) % 4;
    int order = round % N;
    int shootY = -1, shootX = -1;
    if(dir == 0){
        int y = order;
        int x = 0;
        for(int i = 0; i < N; i++){
            int cy = y + (dy[dir] * i);
            int cx = x + (dx[dir] * i);
            if(board[cy][cx] == 1 || board[cy][cx] == 2 || board[cy][cx] == 3){
                shootFlag = true;
                shootY = cy; shootX = cx;
                break;
            }
        }
    }
    else if(dir == 1){
        int y = N - 1;
        int x = order;
        for(int i = 0; i < N; i++){
            int cy = y + (dy[dir] * i);
            int cx = x + (dx[dir] * i);
            if(board[cy][cx] == 1 || board[cy][cx] == 2 || board[cy][cx] == 3){
                shootFlag = true;
                shootY = cy; shootX = cx;
                break;
            }
        }
    }
    else if(dir == 2){
        int y = N - order - 1;
        int x = N - 1;
        for(int i = 0; i < N; i++){
            int cy = y + (dy[dir] * i);
            int cx = x + (dx[dir] * i);
            if(board[cy][cx] == 1 || board[cy][cx] == 2 || board[cy][cx] == 3){
                shootFlag = true;
                shootY = cy; shootX = cx;
                break;
            }
        }
    }
    else if(dir == 3){
        int y = 0;
        int x = N - order - 1;
        for(int i = 0; i < N; i++){
            int cy = y + (dy[dir] * i);
            int cx = x + (dx[dir] * i);
            if(board[cy][cx] == 1 || board[cy][cx] == 2 || board[cy][cx] == 3){
                shootFlag = true;
                shootY = cy; shootX = cx;
                break;
            }
        }
    }
    if(shootFlag == true){
        // cout << shootY << ", " << shootX << "\n";
        getScore(shootY, shootX);
    }
    return shootFlag;
}

/*
3. 공을 맞은 팀이 있으면 그 팀만 머리,꼬리 사람 바꿈 없으면 그냥 패스
*/

void changeHeadTail(){
    // cout << "들어옴: " << shootHeadY << ", " << shootHeadX << "\n";
    for(int i = 0; i < info.size(); i++){
        if(info[i].headY == shootHeadY && info[i].headX == shootHeadX){
            // cout << "찾음\n";
            board[info[i].headY][info[i].headX] = 3;
            board[info[i].tailY][info[i].tailX] = 1;
            info[i].headY = info[i].tailY;
            info[i].headX = info[i].tailX;
            info[i].tailY = shootHeadY;
            info[i].tailX = shootHeadX;
            break;
        }
    }
}

void printTeam(){
    for(int i = 0; i < info.size(); i++){
        cout << info[i].headY << " " << info[i].headX << " " << info[i].tailY << " " << info[i].tailX << " " << info[i].adj << "\n";
    }
}

void solution(){
    findTeam();
    for(int i = 0; i < K; i++){
        moveTeam();
        // cout << "afterMove--------------\n";
        // printBoard();
        bool shoot = shootBall(i);
        // cout << "shoot: " << shoot << "\n";
        if(shoot == true){
            changeHeadTail();
        }
        // cout << "--------\n";
        // printBoard();
    }
    cout << ans;
}

int main(){
    userInput();
    solution();
    return 0;
}