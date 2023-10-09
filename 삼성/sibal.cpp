#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

/*
1. 일차원 배열에 술래의 턴에 따른 위치와 방향(안밖,밖안) 미리 기록
2. 도망자 이동
3. 술래 이동
*/

int dy[4] = { -1, +1, 0, 0 };
int dx[4] = { 0, 0, -1, +1 };

int N, M, H, K;
int board[100][100];
int tree[100][100];
struct DOMANGZA {
    int y, x, d;
    bool live;
};
vector<DOMANGZA> domangza;
struct COORD {
    int y, x, forward_d, backward_d;
};
COORD coord[10000];
int person_idx = 0;
int person_dir = 0; // 0이면 안에서 밖, 1이면 밖에서 안
int ans = 0;

void userInput(){
    cin >> N >> M >> H >> K;
    for(int i = 0; i < M; i++){
        DOMANGZA tmp;
        cin >> tmp.y >> tmp.x >> tmp.d;
        tmp.y--, tmp.x--;
        if(tmp.d == 1){
            tmp.d = 3;
        }
        else if(tmp.d == 2){
            tmp.d = 1;
        }
        board[tmp.y][tmp.x] = 1;
        tmp.live = true;
        domangza.push_back(tmp);
    }
    for(int i = 0; i < H; i++){
        int tmp_y, tmp_x;
        cin >> tmp_y >> tmp_x;
        tmp_y--, tmp_x--;
        tree[tmp_y][tmp_x] = 1;
    }
}

void makeCoordForward(){
    int mydy[4] = { -1, 0, +1, 0 };
    int mydx[4] = { 0, +1, 0, -1 };

    int cur_dir = 0;
    int cy = N/2, cx = N/2;
    int cidx = 0;

    coord[cidx].y = cy, coord[cidx].x = cx, coord[cidx].forward_d = cur_dir;
    cidx++;

    for(int i = 1; i <= N-1; i++){
        for(int j = 0; j < 3; j++){
            if(i != N-1 && j == 2){
                continue;
            }
            for(int k = 0; k < i; k++){
                cy += mydy[cur_dir];
                cx += mydx[cur_dir];
                coord[cidx].y = cy, coord[cidx].x = cx, coord[cidx].forward_d = cur_dir;
                cidx++;
            }
            cur_dir = (cur_dir + 1) % 4;
            coord[cidx-1].forward_d = cur_dir;
        }
    }
    coord[cidx-1].forward_d = 2;
    // for(int i = 0; i < N*N; i++){
    //     cout << coord[i].y << ", " << coord[i].x << " " << coord[i].forward_d << "\n";
    // }
}

void makeCoordBackward(){
    int mydy[4] = { +1, 0, -1, 0 };
    int mydx[4] = { 0, +1, 0, -1 };

    int cur_dir = 0;
    int cy = 0, cx = 0;
    int cidx = (N*N)-1;

    coord[cidx].y = cy, coord[cidx].x = cx, coord[cidx].backward_d = cur_dir;
    cidx--;

    for(int i = N-1; i >= 0; i--){
        for(int j = 0; j < 3; j++){
            if(i != N-1 && j == 2){
                continue;
            }
            for(int k = 0; k < i; k++){
                //cout << cidx << " ";
                cy += mydy[cur_dir];
                cx += mydx[cur_dir];
                coord[cidx].y = cy, coord[cidx].x = cx, coord[cidx].backward_d = cur_dir;
                cidx--;
            }
            cur_dir = (cur_dir + 1) % 4;
            coord[cidx+1].backward_d = cur_dir;
        }
    }
    coord[cidx+1].backward_d = 2;
    // for(int i = 0; i < N*N; i++){
    //     cout << coord[i].y << ", " << coord[i].x << " " << coord[i].backward_d << "\n";
    // }
}

void moveDomangza(){
    int person_y = coord[person_idx].y;
    int person_x = coord[person_idx].x;
    for(int i = 0; i < domangza.size(); i++){
        if(domangza[i].live == false){
            continue;
        }
        int y = domangza[i].y;
        int x = domangza[i].x;
        int d = domangza[i].d;
        if((abs(person_y - y) + abs(person_x - x)) <= 3){
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
                domangza[i].d = d;
            }
            if(ny == person_y && nx == person_x){
                continue;
            }
            else{
                if(board[y][x] > 0){
                    board[y][x]--;
                }
                else{
                    board[y][x] = 0;
                }
                board[ny][nx]++;
                //cout << ny << ", " << nx << "\n";
                domangza[i].y = ny;
                domangza[i].x = nx;
            }
        }
    }
}

void moveCenterPerson(){
    if(coord[person_idx].y == 0 && coord[person_idx].x == 0){
        person_dir = 1;
    }
    else if(coord[person_idx].y == N/2 && coord[person_idx].x == N/2){
        person_dir = 0;
    }
    if(person_dir == 0){
        person_idx++;
    }
    else if(person_dir == 1){
        person_idx--;
    }
}

void catchDomangza(int round){
    // for(int i = 0; i < N; i++){
    //     for(int j = 0; j < N; j++){
    //         cout << board[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    int dy1[4] = { -1, 0, +1, 0 };
    int dx1[4] = { 0, +1, 0, -1 };

    int dy2[4] = { +1, 0, -1, 0 };
    int dx2[4] = { 0, +1, 0, -1 };

    int person_y = coord[person_idx].y;
    int person_x = coord[person_idx].x;
    int person_d;
    //cout << "------" << round << "-----\n";
    int catch_cnt = 0;
    if(person_dir == 0){
        person_d = coord[person_idx].forward_d;
        //cout << person_y << ", " << person_x << " " << person_d << "\n";
        for(int times = 0; times < 3; times++){
            int ny = person_y + (dy1[person_d] * times);
            int nx = person_x + (dx1[person_d] * times);
            //cout << "ny, nx: " << ny << ", " << nx << "\n";
            if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                break;
            }
            else if(tree[ny][nx] == 1){
                continue;
            }
            else if(board[ny][nx] >= 1){
                //cout << ny << ", " << nx << "\n";
                catch_cnt += board[ny][nx];
                for(int i = 0; i < domangza.size(); i++){
                    if(domangza[i].live == false){
                        continue;
                    }
                    else if(domangza[i].y == ny && domangza[i].x == nx){
                        domangza[i].live = false;
                        board[ny][nx] = 0;
                    }
                }
            }
        }
    }
    else if(person_dir == 1){
        person_d = coord[person_idx].backward_d;
        //cout << person_y << ", " << person_x << " " << person_d << "\n";
        for(int times = 0; times < 3; times++){
            int ny = person_y + (dy2[person_d] * times);
            int nx = person_x + (dx2[person_d] * times);
            if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                break;
            }
            else if(tree[ny][nx] == 1){
                continue;
            }
            else if(board[ny][nx] >= 1){
                //cout << ny << ", " << nx << "\n";
                catch_cnt += board[ny][nx];
                for(int i = 0; i < domangza.size(); i++){
                    if(domangza[i].live == false){
                        continue;
                    }
                    else if(domangza[i].y == ny && domangza[i].x == nx){
                        domangza[i].live = false;
                        board[ny][nx] = 0;
                    }
                }
            }
        }
    }
    ans += round * catch_cnt;
}

int main(){
    userInput();
    makeCoordForward();
    makeCoordBackward();
    for(int i = 0; i < K; i++){
        moveDomangza();
        moveCenterPerson();
        catchDomangza(i+1);
    }
    cout << ans;
    return 0;
}