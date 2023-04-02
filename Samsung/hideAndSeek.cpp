#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

int dy[4] = { 0, 0, +1, -1 };
int dx[4] = { +1, -1, 0, 0 };

int N, M, H, K;
struct RUN {
    int y, x, d;
};
struct COORD {
    int y, x, d1, d2;
};
COORD order[10000];
vector<RUN> runner;
vector<int> board[100][100];
int tree[100][100];
int score = 0;
int master = 0; // 술래의 현재 위치
int master_flag = 0; // 술래가 안쪽/바깥쪽을 도는 방향에 대한 플래그

/*
술래는 정중앙에서 시작
도망자는 좌우로 움직이는 사람은 항상 오른쪽을 보고 시작하며, 상하로 움직이는 사람은 항상 아래쪽을 보고 시작
1. M명의 도망자 동시 이동 -> 술래 이동이 한턴
    1-1) 도망자 움직이는 조건: 
        술래와의 거리가  |x1 - x2| + |y1 - y2|로 3 이하일 때 현재 바라보고 있는 방향으로 1칸 움직임
        만약 1칸 이동 시 격자를 벗어나지 않는다면 이동하려는 칸에 술래 있다면 이동X, 없으면 나무와 상관없이 이동 
        벗어난다면 방향으로 반대로 돌리고 1칸 이동 시 술래가 없다면 이동
2. 술래는 턴마다 한칸씩 윗 방향부터 시작하는 달팽이모양으로 움직임, (0, 0)에 도착하면 다시 거꾸로 들어옴
   달팽이모양을 한턴에서 다 도는게 아니라 매 턴 한칸씩 돌기 때문에 달팽이가 안에서 바깥인지의 여부와 위치를 전역으로 저장필요
    2-1) 달팽이 모양으로 한칸씩 이동 후 위치가 이동방향이 틀어져야하면 바로 틀어줌 (0,0)과 정중앙에 왔을 때도
    2-2) 술래의 시야 방향 기준으로 술래가 있는 칸 포함하여 3칸에 도망자가 있는지 체크 필요, 나무가 있으면 해당 칸은 건너 뛰고 아니라면 도망자 지움
    2-3) 점수 얻기 += 현재턴번호 * 현재 턴에서 잡힌 도망자 수
*/

/*
- 나무 존재 여부는 새로운 보드에 기록해서 확인이 필요할 때마다 해당 보드를 체크
- 도망자의 방향은 1, 2 끼리 3, 4끼리 바꿀 수 있게 dy, dx 순서 정해서 선언
- 격자 안에 도망자가 겹쳐져서 입력을 받을 수도, 이동 시에 겹쳐질 수도 있다는 점 유의
- 술래가 돌 때는 도는 위치를 1, 2, 3 .. N*N 까지 숫자와 좌표를 매핑하는걸 미리 세팅해놓고 순서대로 쓰기 (토네이도 얍문코드 참고)
*/

void userInput(){
    cin >> N >> M >> H >> K;
    for(int i = 0; i < M; i++){
        RUN tmp;
        cin >> tmp.y >> tmp.x >> tmp.d;
        if(tmp.d == 1){
            tmp.d = 0;
        }
        else if(tmp.d == 2){
            tmp.d = 2;
        }
        tmp.y--, tmp.x--;
        runner.push_back(tmp);
    }
    for(int i = 0; i < H; i++){
        int y, x;
        cin >> y >> x;
        tree[y-1][x-1] = 1;
    }
}

void masterCatchRunner(int turn){
    int dy2[4] = { -1, 0, +1, 0 };
    int dx2[4] = { 0, +1, 0, -1 };
    int dy3[4] = { +1, 0, -1, 0 };
    int dx3[4] = { 0, +1, 0, -1 };
    if(order[master].y == 0 && order[master].x == 0){
        master_flag = 1;
    }
    else if(order[master].y == N/2 && order[master].x == N/2){
        master_flag = 0;
    }
    int cd;
    if(master_flag == 0){
        master++;
        cd = order[master].d1;
    }
    else{
        master--;
        cd = order[master].d2;
    }
    int cy = order[master].y;
    int cx = order[master].x;
    //cout << cy << ", " << cx << "  " << cd << "\n";
    for(int i = 0; i < 3; i++){
        int ny, nx;
        if(master_flag == 0){
            ny = cy + (dy2[cd] * i);
            nx = cx + (dx2[cd] * i);
        }
        else{
            ny = cy + (dy3[cd] * i);
            nx = cx + (dx3[cd] * i);
        }
        if(ny < 0 || nx < 0 || ny >= N || nx >= N){
            break;
        }
        if(tree[ny][nx] != 1 && board[ny][nx].size() > 0){
            score += board[ny][nx].size() * turn;
            for(int num = 0; num < board[ny][nx].size(); num++){
                int runner_idx = board[ny][nx][num];
                runner[runner_idx].y = -1;
                runner[runner_idx].x = -1;
                runner[runner_idx].d = -1;
            }
            board[ny][nx].clear();
        }
    }
}

void moveRunner(){
    int masterY = order[master].y;
    int masterX = order[master].x;
    vector<int> new_board[100][100];
    for(int i = 0; i < M; i++){
        int y = runner[i].y;
        int x = runner[i].x;
        int d = runner[i].d;
        if(y == -1 || x == -1){ // 잡힌 도망자 체크
            continue;
        }
        if(abs(masterY - y) + abs(masterX - x) <= 3){
            int ny = y + dy[d];
            int nx = x + dx[d];
            if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                if(d == 0){
                    d = 1;
                }
                else if(d == 1){
                    d = 0;
                }
                else if(d == 2){
                    d = 3;
                }
                else if(d == 3){
                    d = 2;
                }
                ny = y + dy[d];
                nx = x + dx[d];
                if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                    runner[i].d = d;
                    new_board[y][x].push_back(i);
                    continue;
                }
            }
            if(ny == masterY && nx == masterX){
                runner[i].d = d;
                new_board[y][x].push_back(i);
                continue;
            }
            if(ny != masterY || nx != masterX){
                runner[i].y = ny;
                runner[i].x = nx;
                runner[i].d = d;
                new_board[ny][nx].push_back(i);
                continue;
            }
        }  
        else{
            new_board[y][x].push_back(i);
        }
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            board[i][j] = new_board[i][j];
        }
    }

    // for(int i = 0; i < N; i++){
    //     for(int j = 0; j < N; j++){
    //         cout << board[i][j].size() << " ";
    //     }
    //     cout << "\n";
    // }
}

void makeOrder(){
    int dy2[4] = { -1, 0, +1, 0 };
    int dx2[4] = { 0, +1, 0, -1 };
    int dy3[4] = { +1, 0, -1, 0 };
    int dx3[4] = { 0, +1, 0, -1 };
    int cy = N/2, cx = N/2;
    int dir = 0;
    int idx = 0;
    order[idx].y = cy;
    order[idx].x = cx;
    order[idx].d1 = dir;
    idx++;
    for(int i = 1; i < N; i++){
        for(int j = 0; j < 3; j++){
            if(j == 2 && i < N-1){
                continue;
            }
            for(int k = 0; k < i; k++){
                int ny = cy + dy2[dir];
                int nx = cx + dx2[dir];
                cy = ny, cx = nx;
                order[idx].y = ny;
                order[idx].x = nx;
                order[idx].d1 = dir;
                idx++;
            }
            dir = (dir+1) % 4;
            order[idx-1].d1 = dir;
        }
    }
    cy = 0, cx = 0;
    dir = 0;
    idx = N*N-1;
    order[idx].y = cy;
    order[idx].x = cx;
    order[idx].d2 = dir;
    idx--;
    for(int i = N-1; i >= 1; i--){
        for(int j = 0; j < 3; j++){
            if(j == 2 && i < N-1){
                continue;
            }
            for(int k = i-1; k >= 0; k--){
                int ny = cy + dy3[dir];
                int nx = cx + dx3[dir];
                cy = ny, cx = nx;
                order[idx].y = ny;
                order[idx].x = nx;
                order[idx].d2 = dir;
                //cout << cy << ", " << cx << " " << dir << "\n";
                idx--;
            }
            dir = (dir+1) % 4;
            order[idx+1].d2 = dir;
        }
    }
    order[0].d2 = 2;
    order[N*N-1].d1 = 2;
    // for(int i = 0; i < N*N; i++){
    //     cout << order[i].y << ", " << order[i].x << " " << order[i].d1 << " " << order[i].d2 << "\n";
    // }
}

void solution(){
    makeOrder();
    for(int i = 1; i <= K; i++){
        moveRunner();
        masterCatchRunner(i);
        //cout << "score: " << score << "\n";
    }
    cout << score;
}

int main(){
    userInput();
    solution();
    return 0;
}