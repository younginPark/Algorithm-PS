#include <iostream>
#include <queue>
using namespace std;

int dy[8] = { -1, -1, 0, +1, +1, +1, 0, -1 };
int dx[8] = { 0, +1, +1, +1, 0, -1, -1, -1 };

int N, M, K;
struct FIREBALL {
    int m, d, s;
};
queue<FIREBALL> board[55][55];

void userInput(){
    cin >> N >> M >> K;
    for(int i = 0; i < M; i++){
        int y, x;
        FIREBALL tmp;
        cin >> y >> x >> tmp.m >> tmp.s >> tmp.d;
        y--; x--;
        board[y][x].push(tmp);
    }
}

int solution(){
    while(K > 0){
        K--;
        queue<FIREBALL> new_board[55][55];
        // 모든 파이어볼은 자신의 방향 d로 속력 s만큼 이동한다.
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(board[i][j].size() > 0){
                    int q_size = board[i][j].size();
                    for(int k = 0; k < q_size; k++){
                        FIREBALL cur = board[i][j].front();
                        board[i][j].pop();
                        int ny = (i + (dy[cur.d] * cur.s) + 2000*N) % N;
                        int nx = (j + (dx[cur.d] * cur.s) + 2000*N) % N;
                        new_board[ny][nx].push(cur);
                    }
                }
            }
        }
        // 파이어볼이 있는 칸 처리
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(new_board[i][j].size() >= 2){
                    int q_size = new_board[i][j].size();
                    int total_dir = 0;
                    int total_m = 0;
                    int total_s = 0;
                    for(int k = 0; k < q_size; k++){
                        FIREBALL cur = new_board[i][j].front();
                        new_board[i][j].pop();
                        total_m += cur.m;
                        total_s += cur.s;
                        if(k == 0){
                            if(cur.d % 2 == 0){
                                total_dir = 1;
                            }
                            else if(cur.d % 2 != 0){
                                total_dir = 0;
                            }
                        }
                        else{
                            if(cur.d % 2 == 0 && total_dir == 1){
                                total_dir = 1;
                            }
                            else if(cur.d % 2 != 0 && total_dir == 0){
                                total_dir = 0;
                            }
                            else{
                                total_dir = 2;
                            }
                        }
                    }
                    total_m /= 5;
                    total_s /= q_size;
                    if(total_m > 0){
                        if(total_dir == 0 || total_dir == 1){
                            for(int dir = 0; dir < 8; dir += 2){
                                FIREBALL tmp;
                                tmp.d = dir; tmp.m = total_m; tmp.s = total_s;
                                board[i][j].push(tmp);
                            }
                        }
                        else{
                            for(int dir = 1; dir < 8; dir +=2){
                                FIREBALL tmp;
                                tmp.d = dir; tmp.m = total_m; tmp.s = total_s;
                                board[i][j].push(tmp);
                            }
                        }
                    }
                }
                else{
                    board[i][j] = new_board[i][j];
                }
            }
        }
    }
    int ans = 0;
    // K번 이후 질량의 합 구하기
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(board[i][j].size() > 0){
                int q_size = board[i][j].size();
                for(int k = 0; k < q_size; k++){
                    FIREBALL cur = board[i][j].front();
                    board[i][j].pop();
                    ans += cur.m;
                }
            }
        }
    }
    return ans;
}

int main(){
    userInput();
    int ans = solution();
    cout << ans;
    return 0;
}