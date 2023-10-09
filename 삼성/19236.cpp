#include <iostream>
using namespace std;

int dy[8] = { -1, -1, 0, +1, +1, +1, 0, -1 };
int dx[8] = { 0, -1, -1, -1, 0, +1, +1, +1 };

struct FISH {
    int x, y;
    int dir;
};

int ret = 0;

void solve(FISH fish[], int board[][4], int shark_y, int shark_x, int sum){
    // copy
    FISH candi_fish[16];
    int candi_board[4][4];
    for(int i = 0; i < 16; i++){
        candi_fish[i] = fish[i];
    }
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            candi_board[i][j] = board[i][j];
        }
    }
    // eat
    int fish_number = candi_board[shark_y][shark_x];
    int shark_dir = candi_fish[fish_number].dir;

    candi_fish[fish_number].y = -1;
    candi_fish[fish_number].x = -1;
    candi_fish[fish_number].dir = -1;
    candi_board[shark_y][shark_x] = -1;

    sum += (fish_number + 1);
    if(ret < sum) ret = sum;

    // fish move
    for(int i = 0; i < 16; i++){
        if(candi_fish[i].dir == -1){
            continue;
        }
        int cy = candi_fish[i].y;
        int cx = candi_fish[i].x;
        int cd = candi_fish[i].dir;

        int ny = cy + dy[cd];
        int nx = cx + dx[cd];
        int nd = cd;

        while(ny < 0 || ny >= 4 || nx < 0 || nx >= 4 || (ny == shark_y && nx == shark_x)){
            nd = (nd + 1) % 8; 
            ny = cy + dy[nd];
            nx = cx + dx[nd];
        }
        
        if(candi_board[ny][nx] != -1){
            int target = candi_board[ny][nx];
            candi_fish[target].y = cy;
            candi_fish[target].x = cx;
            candi_fish[i].y = ny;
            candi_fish[i].x = nx;
            candi_fish[i].dir = nd;

            candi_board[ny][nx] = i;
            candi_board[cy][cx] = target;
        }
        else{
            candi_fish[i].y = ny;
            candi_fish[i].x = nx;
            candi_fish[i].dir = nd;

            candi_board[cy][cx] = -1;
            candi_board[ny][nx] = i;
        }
    }

    // shark move
    for(int i = 1; i < 4; i++){
        int ny = shark_y + dy[shark_dir] * i;
        int nx = shark_x + dx[shark_dir] * i;
        if(ny < 0 || ny >= 4 || nx < 0 || nx >= 4){
            break;
        }
        if(candi_board[ny][nx] != -1){
            solve(candi_fish, candi_board, ny, nx, sum);
        }
    }
}

int main() {

    FISH fish[16];
    int board[4][4];

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            int a, b;
            scanf("%d %d", &a, &b);
            a--, b--;
            fish[a].y = i;
            fish[a].x = j;
            fish[a].dir = b;
            board[i][j] = a;
        }
    }

    solve(fish, board, 0, 0, 0);
    printf("%d", ret);
    return 0;
}