#include <iostream>
using namespace std;

int N;
int board[500][500];

// 7, 2, 10, 5, 10, 7, 2, 1, 1, a
const int calc[9] = { 1, 1, 2, 7, 7, 2, 10, 10, 5 };
const int left_y[10] = { -1, 1, -2, -1, 1, 2, -1, 1, 0, 0 };
const int left_x[10] = { 1, 1, 0, 0, 0, 0, -1, -1, -2, -1 };
const int down_y[10] = { -1, -1, 0, 0, 0, 0, 1, 1, 2, 1 };
const int down_x[10] = { -1, 1, -2, -1, 1, 2, -1, 1, 0, 0 };
const int right_y[10] = { -1, 1, -2, -1, 1, 2, -1, 1, 0, 0 };
const int right_x[10] = { -1, -1, 0, 0, 0, 0, 1, 1, 2, 1 };
const int up_y[10] = { 1, 1, 0, 0, 0, 0, -1, -1, -2, -1 };
const int up_x[10] = { -1, 1, -2, -1, 1, 2, -1, 1, 0, 0 };

const int dy[4] = { 0, +1, 0, -1 };
const int dx[4] = { -1, 0, +1, 0 };

void solve() {
    int cur_y = N / 2;
    int cur_x = N / 2;
    int cur_dir = 0;
    for(int i = 1; i < N; i++) {
        if(i == N-1){ // 마지막꺼는 3번씩 반복
            for(int j = 0; j < 3; j++){
                for(int k = 1; k <= i; k++){ // 2번 반복에서 각 1번에 한칸씩 이동이 몇번 있는지 (1~N-1)
                    int next_y = cur_y + dy[cur_dir]; 
                    int next_x = cur_x + dx[cur_dir]; 
                    cur_y = next_y, cur_x = next_x;
                    int tmp_result[11] = { 0, };
                    int tmp_total = 0;
                    for(int h = 0; h < 9; h++){
                        tmp_result[h] = board[next_y][next_x] * calc[h] / 100; // 각 퍼센티지 계산해서 저장해둠
                        // cout << board[next_y][next_x] << " * " << calc[h] << " = " << board[next_y][next_x] * calc[h] / 100 << "  " << tmp_result[h] << "\n";
                        tmp_total += tmp_result[h];
                    }
                    tmp_result[9] = board[next_y][next_x] - tmp_total; // a 값 넣어줌
                    board[next_y][next_x] = 0; // y의 모든 모래는 날아감
                    // 모래가 흩날리는 위치가 격자 안에 있으면 기존 모래에 더해주고 아니면 버림
                    if(cur_dir == 0) { // 왼
                        for(int h = 0; h < 10; h++){
                            int y = next_y + left_y[h];
                            int x = next_x + left_x[h];
                            if(y < 0 || y >= N || x < 0 || x >= N){
                                continue;
                            }
                            board[y][x] += tmp_result[h];
                        }
                    }
                    if(cur_dir == 1) { // 아래
                        for(int h = 0; h < 10; h++){
                            int y = next_y + down_y[h];
                            int x = next_x + down_x[h];
                            if(y < 0 || y >= N || x < 0 || x >= N){
                                continue;
                            }
                            board[y][x] += tmp_result[h];
                        }
                    }
                    if(cur_dir == 2) { // 오른
                        for(int h = 0; h < 10; h++){
                            int y = next_y + right_y[h];
                            int x = next_x + right_x[h];
                            if(y < 0 || y >= N || x < 0 || x >= N){
                                continue;
                            }
                            board[y][x] += tmp_result[h];
                        }
                    }
                    if(cur_dir == 3) { // 위
                        for(int h = 0; h < 10; h++){
                            int y = next_y + up_y[h];
                            int x = next_x + up_x[h];
                            if(y < 0 || y >= N || x < 0 || x >= N){
                                continue;
                            }
                            board[y][x] += tmp_result[h];
                        }
                    }
                }
                cur_dir = (cur_dir + 1) % 4;
            }
        }
        else{
            for(int j = 0; j < 2; j++){ // 각 숫자마다 2번씩 반복
                // cout << cur_dir << "\n";
                for(int k = 1; k <= i; k++){ // 2번 반복에서 각 1번에 한칸씩 이동이 몇번 있는지 (1~N-1)
                    int next_y = cur_y + dy[cur_dir]; 
                    int next_x = cur_x + dx[cur_dir];
                    cur_y = next_y, cur_x = next_x; 
                    int tmp_result[11] = { 0, };
                    int tmp_total = 0;
                    for(int h = 0; h < 9; h++){
                        tmp_result[h] = board[next_y][next_x] * calc[h] / 100; // 각 퍼센티지 계산해서 저장해둠
                        tmp_total += tmp_result[h];
                    }
                    tmp_result[9] = board[next_y][next_x] - tmp_total;
                    board[next_y][next_x] = 0; // y의 모든 모래는 날아감
                    // 모래가 흩날리는 위치가 격자 안에 있으면 기존 모래에 더해주고 아니면 버림
                    if(cur_dir == 0) { // 왼
                        for(int h = 0; h < 10; h++){
                            int y = next_y + left_y[h];
                            int x = next_x + left_x[h];
                            if(y < 0 || y >= N || x < 0 || x >= N){
                                continue;
                            }
                            board[y][x] += tmp_result[h];
                        }
                    }
                    if(cur_dir == 1) { // 아래
                        for(int h = 0; h < 10; h++){
                            int y = next_y + down_y[h];
                            int x = next_x + down_x[h];
                            if(y < 0 || y >= N || x < 0 || x >= N){
                                continue;
                            }
                            board[y][x] += tmp_result[h];
                        }
                    }
                    if(cur_dir == 2) { // 오른
                        for(int h = 0; h < 10; h++){
                            int y = next_y + right_y[h];
                            int x = next_x + right_x[h];
                            if(y < 0 || y >= N || x < 0 || x >= N){
                                continue;
                            }
                            board[y][x] += tmp_result[h];
                        }
                    }
                    if(cur_dir == 3) { // 위
                        for(int h = 0; h < 10; h++){
                            int y = next_y + up_y[h];
                            int x = next_x + up_x[h];
                            if(y < 0 || y >= N || x < 0 || x >= N){
                                continue;
                            }
                            board[y][x] += tmp_result[h];
                        }
                    }
                }
                cur_dir = (cur_dir + 1) % 4;
            }
        }
    }
}

int main() {

    int start_total = 0;
    int last_total = 0;

    scanf("%d", &N);
    for(int y = 0; y < N; y++){
        for(int x = 0; x < N; x++){
            scanf("%d", &board[y][x]);
            start_total += board[y][x];
        }
    }
    solve();
    for(int y = 0; y < N; y++){
        for(int x = 0; x < N; x++){
            last_total += board[y][x];
        }
    }
    cout << start_total - last_total;
    return 0;
}