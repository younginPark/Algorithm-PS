#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

int dy[4] = { 0, -1, 0, +1 };
int dx[4] = { +1, 0, -1, 0 };

int N, M, K;
int board[25][25];
int visited[25][25];
int score = 0;
int changeY, changeX;

// 팀 당 머리, 꼬리 위치 저장
struct INFO{
    int headY, headX;
    int tailY, tailX;
};
vector<INFO> team;

// 입력 받을 때 방향을 어떻게 알것인가
void userInput(){
    cin >> N >> M >> K;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> board[i][j];
        }
    }
}

void printBoard(){
    cout << "----------------\n";
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

// 공을 획득했을 경우 머리와 꼬리 위치 바꾸기
void changeHeadTail(){
    for(int i = 0; i < M; i++){
        if(team[i].headY == changeY && team[i].headX == changeX){
            team[i].headY = team[i].tailY;
            team[i].headX = team[i].tailX;
            team[i].tailY = changeY;
            team[i].tailX = changeX;
            board[team[i].headY][team[i].headX] = 1;
            board[team[i].tailY][team[i].tailX] = 3;
            break;
        }
    }
}

// 머리 사람으로부터 몇번째 위치에 있는지 확인
// 여기서 구한 머리 값으로 머리꼬리 정보가 저장되어 있는 곳에서 어느 팀인지 찾고 머리꼬리 위치 바꿀 때 팀 번호 활용
int findOrder(int y, int x){
    // bfs 돌면서 공을 맞은 위치부터 방문 안한 곳으로 이동하면서 머리의 y, x 가 나올때까지 cnt 추가하면서 반복
    memset(visited, 0, sizeof(visited));
    queue<pair<pair<int, int>, int> > q;
    if(board[y][x] == 1){
        changeY = y, changeX = x;
        return 1;
    }
    q.push(make_pair(make_pair(y ,x), 1));
    while(!q.empty()){
        int cy = q.front().first.first;
        int cx = q.front().first.second;
        int cnt = q.front().second;
        q.pop();
        for(int dir = 0; dir < 4; dir++){
            int ny = cy + dy[dir];
            int nx = cx + dx[dir];
            if(ny < 0 || nx < 0 || ny >= N || nx >= N || visited[ny][nx] == 1){
                continue;
            }
            if(board[ny][nx] == 2 || board[ny][nx] == 3){
                q.push(make_pair(make_pair(ny, nx), cnt+1));
                visited[ny][nx] = 1;
            }
            if(board[ny][nx] == 1){
                changeY = ny, changeX = nx;
                return cnt+1;
            }
        }
    }
    return 0;
}

// 라운드 별로 공으로 때리기 및 점수 획득
void round(int order){
    // 현재 라운드/N 해서 roundDir 정해줌, %로 나머지 구해서 0+line 번째 줄 해줌
    int roundDir = (order / N) % 4;
    int line = order % N;
    // board에서 해당 좌표에 사람이 있다면 flag 바꾸고 몇번째 사람인지 찾기
    int cy, cx;
    if(roundDir == 0){
        cy = line, cx = 0;
    }
    else if(roundDir == 1){
        cy = N-1, cx = line;
    }
    else if(roundDir == 2){
        cy = N-1-line, cx = N-1;
    }
    else if(roundDir == 3){
        cy = 0, cx = N-1-line;
    }
    for(int i = 0; i < N; i++){
        int ny = cy + dy[roundDir] * i;
        int nx = cx + dx[roundDir] * i;
        cout << ny << ", " << nx << "\n";
        if(board[ny][nx] != 4 && board[ny][nx] != 0){
            int shotOrder = findOrder(ny, nx);
            score += shotOrder * shotOrder;
            changeHeadTail();
            break;
        }
    }
}


// 머리부터 이동하기
void moveHead(){
    // 방향은 반시계/시계 따지지 않고 4방향 돌면서 머리는 4가 있는 칸으로 이동
    // 방금 있던 자리를 변수에 임시로 저장해놓고 다음 몸통이나 꼬리를 해당 임시 값으로 바꿔주고, 기존 값을 다시 임시 값에 업데이트
    memset(visited, 0, sizeof(visited));
    for(int i = 0; i < M; i++){
        int move = 0;
        int cy = team[i].headY;
        int cx = team[i].headX;
        int tmpY, tmpX;
        for(int dir = 0; dir < 4; dir++){
            int ny = cy + dy[dir];
            int nx = cx + dx[dir];
            if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                continue;
            }
            if(board[ny][nx] == 4){
                move = 1;
                board[cy][cx] = board[ny][nx];
                board[ny][nx] = 1;
                visited[ny][nx] = 1;
                team[i].headY = ny;
                team[i].headX = nx;
                tmpY = cy, tmpX = cx;
                break;
            }
        }
        int tailY, tailX;
        while(move == 1){
            for(int dir = 0; dir < 4; dir++){
                int ny = tmpY + dy[dir];
                int nx = tmpX + dx[dir];
                if(ny < 0 || nx < 0 || ny >= N || nx >= N || visited[ny][nx] == 1){
                    continue;
                }
                if(board[ny][nx] == 2){
                    int tmpVal = board[tmpY][tmpX];
                    board[ny][nx] = tmpVal;
                    board[tmpY][tmpX] = 2;
                    visited[tmpY][tmpX] = 1;
                    tmpY = ny, tmpX = nx;
                }
                else if(board[ny][nx] == 3){
                    int tmpVal = board[tmpY][tmpX];
                    board[ny][nx] = tmpVal;
                    board[tmpY][tmpX] = 3;
                    visited[tmpY][tmpX] = 1;
                    tailY = tmpY, tailX = tmpX;
                    tmpY = ny, tmpX = nx;
                }
            }
            if((tmpY == team[i].tailY) && (tmpX == team[i].tailX)){
                break;
            }
        }
        if(move == 1){
            team[i].tailY = tailY;
            team[i].tailX = tailX;
        }
    }
}

void bfs(int y, int x){
    INFO tmp_info;
    queue<pair<int, int> > q;
    q.push(make_pair(y, x));
    visited[y][x] = 1;
    if(board[y][x] == 1){
        tmp_info.headY = y;
        tmp_info.headX = x;
    }
    else if(board[y][x] == 3){
        tmp_info.tailY = y;
        tmp_info.tailX = x;
    }
    while(!q.empty()){
        int cy = q.front().first;
        int cx = q.front().second;
        q.pop();
        for(int dir = 0; dir < 4; dir++){
            int ny = cy + dy[dir];
            int nx = cx + dx[dir];
            if(ny < 0 || nx < 0 || ny >= N || nx >= N || visited[ny][nx] == 1 || board[ny][nx] == 0){
                continue;
            }
            if(1 <= board[ny][nx] && board[ny][nx] <= 4){
                q.push(make_pair(ny, nx));
                visited[ny][nx] = 1;
                if(board[ny][nx] == 1){
                    tmp_info.headY = ny;
                    tmp_info.headX = nx;
                }
                else if(board[ny][nx] == 3){
                    tmp_info.tailY = ny;
                    tmp_info.tailX = nx;
                }
            }
        }
    }
    team.push_back(tmp_info);
}

// 입력만으로는 팀을 알 수 없으니까 bfs 돌면서 팀별로 머리와 꼬리 위치 구하기
void getTeam(){
    int idx = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(board[i][j] != 0 && visited[i][j] == 0){
                bfs(i, j);
            }
        }
    }
}

void solution(){
    getTeam();
    for(int i = 0; i < K; i++){
        cout << "----------------\n";
        cout << "round: " << i << "\n";
        moveHead();
        printBoard();
        round(i);
        cout << "score: " << score << "\n";
    }
    cout << score;
}

int main(){
    userInput();
    solution();
    return 0;
}