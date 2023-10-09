#include <iostream>
using namespace std;

int dy[4] = { -1, 0, +1, 0 };
int dx[4] = { 0, +1, 0, -1 };

int N, M;
int board[55][55];
int visit[55][55];

int ans = 0;

struct ROBOT {
    int y, x, dir;
};
ROBOT robot;

void userInput(){
    cin >> N >> M;
    cin >> robot.y >> robot.x >> robot.dir;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> board[i][j];
        }
    }  
}

void simulation(){
    while(1){
        // 현재 위치 청소
        if(visit[robot.y][robot.x] == 0){
            ans++;
            visit[robot.y][robot.x] = 1;
        }
        // 현재 위치에서 왼쪽으로 방향 회전하며 청소
        int fail_cnt = 0;
        for(int dir = 1; dir <= 4; dir++){
            int ndir = (robot.dir-dir+4)%4;
            int ny = robot.y + dy[ndir];
            int nx = robot.x + dx[ndir];
            if(board[ny][nx] == 1 || visit[ny][nx] == 1){ // 벽이거나 이미 청소함
                fail_cnt++;
                if(fail_cnt == 4){
                    ny = robot.y - dy[ndir];
                    nx = robot.x - dx[ndir];
                    if(board[ny][nx] == 1){
                        return;
                    }
                    else{
                        robot.y = ny;
                        robot.x = nx;
                        robot.dir = ndir;
                        break;
                    }
                }
                continue;
            }
            // 로봇청소기 이동 그리고 현재 있는 for문 break
            robot.y = ny;
            robot.x = nx;
            robot.dir = ndir;
            break;
        }
    }
}

int main(){
    userInput();
    simulation();
    cout << ans;
    return 0;
}