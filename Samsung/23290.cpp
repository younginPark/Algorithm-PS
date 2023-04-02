#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int dy[8] = { 0, -1, -1, -1, 0, +1, +1, +1 };
int dx[8] = { -1, -1, 0, +1, +1, +1, 0, -1 };
int dicty[4] = { -1, 0, +1, 0 };
int dictx[4] = { 0, -1, 0, +1 };

int M, S;
struct FISH {
	int y, x, dir;
};
struct SHARK {
    int y, x;
};
SHARK shark;
vector<FISH> board[5][5];
int smell[5][5];
int dict[65][4];

void makeDict(){
    int idx = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                dict[idx][0] = i;
                dict[idx][1] = j;
                dict[idx][2] = k;
                idx++;
            }
        }
    }
}

void userInput(){
    cin >> M >> S;
    for(int i = 0; i < M; i++){
        FISH tmp;
        cin >> tmp.y >> tmp.x >> tmp.dir;
        tmp.y--; tmp.x--; tmp.dir--;
        board[tmp.y][tmp.x].push_back(tmp);
    }
    cin >> shark.y >> shark.x;
    shark.y--; shark.x--;
}

void moveFish(){
    vector<FISH> after_move[5][5];
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(board[i][j].size() > 0){
                for(int k = 0; k < board[i][j].size(); k++){
                    int flag = 0;
                    for(int idx = 0; idx < 8; idx++){
                        int dir = (board[i][j][k].dir-idx+8) % 8;
                        int ny = board[i][j][k].y + dy[dir];
                        int nx = board[i][j][k].x + dx[dir];
                        if(ny < 0 || nx < 0 || ny >= 4 || nx >= 4 || (shark.y == ny && shark.x == nx)
                        || smell[ny][nx] > 0){
                            continue;
                        }
                        else{
                            flag = 1;
                            FISH newFish;
                            newFish.dir = dir;
                            newFish.y = ny; newFish.x = nx;
                            after_move[ny][nx].push_back(newFish);
                            break;
                        }
                    }
                    // 이동안하면 그자리 그대로인것도 물고기 넣어줘야 함, 그냥 넘어가면 안돼..
                    if(flag == 0){
                        after_move[i][j].push_back(board[i][j][k]);
                    }
                }
            }
        }
    }
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            board[i][j] = after_move[i][j];
        }
    }
}

void moveShark(int s){
    int best_dir = 0;
    int total_cnt = -1;
    for(int i = 0; i < 64; i++){
        int cnt = 0;
        int ny = shark.y;
        int nx = shark.x; 
        int fail = 0;
        int visit[5][5];
        memset(visit, 0, sizeof(visit));
        for(int j = 0; j < 3; j++){
            ny += dicty[dict[i][j]];
            nx += dictx[dict[i][j]];
            if(ny < 0 || nx < 0 || ny >= 4 || nx >= 4){
                fail = 1;
                break;
            }
            if(visit[ny][nx] == 0){
                cnt += board[ny][nx].size();
                visit[ny][nx] = 1;
            }
        }
        if(cnt > total_cnt && fail == 0){
            total_cnt = cnt;
            best_dir = i;
        }
    } 
    for(int i = 0; i < 3; i++){
        shark.y += dicty[dict[best_dir][i]];
        shark.x += dictx[dict[best_dir][i]];
        if(board[shark.y][shark.x].size() > 0){
            board[shark.y][shark.x].clear();
            smell[shark.y][shark.x] = s;
        }
    }
}

void removeFishSmell(int s){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(smell[i][j] == s-2){
                smell[i][j] = 0;
            }
        }
    }
}

void solution(){
    for(int idx = 0; idx < S; idx++){
        vector<FISH> copy_board[5][5];
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                copy_board[i][j] = board[i][j];
            }
        }
        moveFish();
        moveShark(idx+1);
        removeFishSmell(idx+1);
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                for(int k = 0; k < copy_board[i][j].size(); k++){
                    board[i][j].push_back(copy_board[i][j][k]);
                }
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            ans += board[i][j].size();
        }
    }
    cout << ans;
}

int main() {
    makeDict();
    userInput();
    solution();
	return 0;
}
