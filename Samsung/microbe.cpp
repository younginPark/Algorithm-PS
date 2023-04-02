#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

/*
따로따로 미생물을 배열에 관리하는 것이 아닌 미생물 구조체를 가진 2차원 배열에 넣어서 관리
이동할 때 새로운 배열에 추가해주고 그 배열에서 합치는 것을 해주거나 방향을 바꿔주고 기존 배열에 복사해줌
약품 칠해진 곳에 오면 미생물 절반 죽고 방향 바뀌고 그 이후에 두개 이상의 군집을 합쳐줌
약품이 있는 곳에서 (기존 미생물 수/2) 해서 미생물 수가 0이 되면 해당 군집은 그냥 없애줌

약품이 칠해진 곳인지는 y가 0 혹은 N-1 아니면 x가 0 혹은 N-1 이면 약품이 칠해진 곳

미생물 구조체를 가진 100x100 크기의 벡터 배열
*/

int N, M, K;
int ans = 0;
struct MICROBE {
    int num, dir;
};
MICROBE board[101][101];
queue<MICROBE> copy_board[101][101];

int dy[4] = { -1, +1, 0, 0 };
int dx[4] = { 0, 0, -1, +1 };

void init(){
    memset(board, 0 ,sizeof(board));
    ans = 0;
}

void userInput(){
    cin >> N >> M >> K;
    for(int i = 0; i < K; i++){
        int tmpY, tmpX;
        MICROBE tmp;
        cin >> tmpY >> tmpX >> tmp.num >> tmp.dir;
        tmp.dir--;
        board[tmpY][tmpX] = tmp;
    }
}

void printBoard(){
    cout << "------------------------\n";
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << board[i][j].num << " ";
        }
        cout << "\n";
    }
}

// 1) 이동 및 약품 칠해진 곳에 미생물 반 죽이고 방향 반대로
// 2) 한 셀에 군집 여러개면 하나로 합쳐주기

void solution(){
    while(M--){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(board[i][j].num > 0){
                    MICROBE cur_micro = board[i][j];
                    int ny = i + dy[cur_micro.dir];
                    int nx = j + dx[cur_micro.dir];
                    if(ny == 0 || nx == 0 || ny == N-1 || nx == N-1){
                        cur_micro.num /= 2;
                        if(cur_micro.num == 0){
                            continue;
                        }
                        else{
                            if(cur_micro.dir == 0){
                                cur_micro.dir = 1;
                            }
                            else if(cur_micro.dir == 1){
                                cur_micro.dir = 0;
                            }
                            else if(cur_micro.dir == 2){
                                cur_micro.dir = 3;
                            }
                            else if(cur_micro.dir == 3){
                                cur_micro.dir = 2;
                            }
                        }
                    }
                    copy_board[ny][nx].push(cur_micro);
                }
            }
        }

        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(copy_board[i][j].size() >= 2){
                    int loop_size = copy_board[i][j].size();
                    int total_cnt = 0;
                    int max_cnt = 0, max_dir;
                    while(true){
                        MICROBE front = copy_board[i][j].front();
                        copy_board[i][j].pop();
                        total_cnt += front.num;
                        if(front.num > max_cnt){
                            max_cnt = front.num;
                            max_dir = front.dir;
                        }
                        if(copy_board[i][j].empty()){
                            front.dir = max_dir;
                            front.num = total_cnt;
                            copy_board[i][j].push(front);
                            break;
                        }
                    }
                    // MICROBE new_micro;
                    // new_micro.num = total_cnt;
                    // new_micro.dir = max_dir;
                    // copy_board[i][j].push({total_cnt, max_dir});
                }
            }
        }
        
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(copy_board[i][j].size() > 0){
                    board[i][j] = copy_board[i][j].front();
                    copy_board[i][j].pop();
                }
                else{
                    board[i][j].num = 0;
                    board[i][j].dir = 0;
                }
            }
        }
        //printBoard();
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            ans += board[i][j].num;
        }
    }
}

int main(){
    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++){
        init();
        userInput();
        solution();
        cout << "#" << tc << " " << ans << "\n";
    }
    return 0;
}