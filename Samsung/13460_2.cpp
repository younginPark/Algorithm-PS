#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int dy[4] = { -1, 0, +1, 0 };
int dx[4] = { 0, -1, 0, +1 };

int N, M;
char board[15][15];
int ans = 11;

struct BALL {
    int y;
    int x;
};

BALL red;
BALL blue;

void userInput(){
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        string str1;
        cin >> str1;
        for(int j = 0; j < M; j++){
            if(str1[j] == 'R'){
                red.y = i;
                red.x = j;
                board[i][j] = '.';
            }
            else if(str1[j] == 'B'){
                blue.y = i;
                blue.x = j;
                board[i][j] = '.';
            }
            else{
                board[i][j] = str1[j];
            }
        }
    }
}

void dfs(int cur_dir, int times){
    if(times >= ans){
        return;
    }
    // 빨간공 움직이기
    int ny = red.y + dy[cur_dir];
    int nx = red.x + dx[cur_dir];
    int blue_flag = 0;
    while(1){
        if(ny == blue.y && nx == blue.x){ // 이동하는데 앞에 파란공이 있다면 플래그 둠
            blue_flag = 1;
        }
        if(board[ny][nx] == '.'){ // . 이면 한번 더 이동
            ny += dy[cur_dir];
            nx += dx[cur_dir];
        }
        else if(board[ny][nx] == 'O'){ // 구멍이면 파란공 플래그와 상관없이 빠짐
            red.y = ny;
            red.x = nx;
            break;
        }
        else if(board[ny][nx] == '#'){ // #이면 파란공 플래그에 따라 한칸 혹은 두칸 전으로 이동
            if(blue_flag == 1){
                red.y = ny - (2 * dy[cur_dir]);
                red.x = nx - (2 * dx[cur_dir]);
            }
            else{
                red.y = ny - dy[cur_dir];
                red.x = nx - dx[cur_dir];
            }
            break;
        }
    }
    // 파란공 움직이기
    ny = blue.y + dy[cur_dir];
    nx = blue.x + dx[cur_dir];
    while(1){
        if(board[ny][nx] == 'O'){ // 구멍이면 빨간공 위치와 상관없이 빠짐
            blue.y = ny;
            blue.x = nx;
            break;
        }
        else if(board[ny][nx] == '#' || (ny == red.y && nx == red.x && blue_flag == 0)){ // 구멍이 아니면서 빨간공이나 # 이면 한칸 이전에 위치
            blue.y = ny - dy[cur_dir];
            blue.x = nx - dx[cur_dir];
            break;
        }
        else if(board[ny][nx] == '.'){ // . 이면 한번 더 이동
            ny += dy[cur_dir];
            nx += dx[cur_dir];
        }
    }

    // 디버깅용 출력
    // cout << "dir: " << cur_dir << "times: " << times << "\n";
    // cout << red.y << ", " << red.x << "\n";
    // cout << blue.y << ", " << blue.x << "\n";
    // char tmp_red = board[red.y][red.x];
    // char tmp_blue = board[blue.y][blue.x];
    // board[red.y][red.x] = 'R';
    // board[blue.y][blue.x] = 'B';
    // for(int i = 0; i < N; i++){
    //     for(int j = 0; j < M; j++){
    //         cout << board[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    // cout << "\n";
    // board[red.y][red.x] = tmp_red;
    // board[blue.y][blue.x] = tmp_blue;
    // 공 빠졌는지 확인 
    // 파란공 빠졌으면 빨간공 빠진 것과 상관없이 실패
    if(board[blue.y][blue.x] == 'O'){
        return;
    }
    // 빨간공만 빠졌으면 정답 업데이트
    else if(board[red.y][red.x] == 'O'){
        ans = min(ans, times);
        return;
    }
    // 둘다 안빠졌으면 다시 기울이기
    else if(board[blue.y][blue.x] != 'O' && board[red.y][red.x] != 'O'){
        BALL copy_red, copy_blue;
        for(int dir = 0; dir < 4; dir++){
            copy_red.y = red.y; copy_red.x = red.x;
            copy_blue.y = blue.y; copy_blue.x = blue.x;
            dfs(dir, times+1);
            red.y = copy_red.y; red.x = copy_red.x;
            blue.y = copy_blue.y; blue.x = copy_blue.x;
        }
    }
}

int main(){
    userInput();
    BALL copy_red, copy_blue;
    for(int dir = 0; dir < 4; dir++){
        copy_red.y = red.y; copy_red.x = red.x;
        copy_blue.y = blue.y; copy_blue.x = blue.x;
        dfs(dir, 1);
        red.y = copy_red.y; red.x = copy_red.x;
        blue.y = copy_blue.y; blue.x = copy_blue.x;
    }
    if(ans >= 11){
        cout << -1;
    }
    else{
        cout << ans;
    }
    return 0;
}