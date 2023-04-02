#include <iostream>
#include <queue>
using namespace std;

int dy[] = { -1, -1, 0, +1, +1, +1, 0, -1 };
int dx[] = { 0, +1, +1, +1, 0, -1, -1, -1 };

int setDir1[] = { 0, 2, 4, 6 };
int setDir2[] = { 1, 3, 5, 7 };

struct FIREBALL
{
    int m, s, d;
};
int N, M, K;
queue<FIREBALL> board[51][51];

void solve() {
    // move
    queue<FIREBALL> new_board[51][51];
    for(int y = 0; y < N; y++){
        for(int x = 0; x < N; x++){
            if(!board[y][x].empty()){
                while(!board[y][x].empty()) {
                    FIREBALL front = board[y][x].front(); board[y][x].pop();
                    int next_y, next_x;
                    int speed = front.s % N;
                    next_y = (y + (speed * dy[front.d]));
                    next_x = (x + (speed * dx[front.d]));
                    if(next_y < 0) { next_y = next_y + N; };
                    if(next_x < 0) { next_x = next_x + N; };
                    if(next_y >= N) { next_y = next_y - N; };
                    if(next_x >= N) { next_x = next_x - N; };
                    new_board[next_y][next_x].push(front);
                }
            }
        }
    }

    // divide
    for(int y = 0; y < N; y++){
        for(int x = 0; x < N; x++){
            if(new_board[y][x].size() >= 2) {
                int m_total = 0, s_total = 0, d_total = 0;
                int ball_cnt = new_board[y][x].size();
                while(!new_board[y][x].empty()){
                    FIREBALL front = new_board[y][x].front(); new_board[y][x].pop();
                    m_total += front.m;
                    s_total += front.s;
                    if(front.d % 2 == 0){
                        d_total++;
                    }
                }
                m_total /= 5;
                s_total /= ball_cnt;
                if(m_total > 0){
                    if(d_total == 0 || d_total == ball_cnt) {
                        for(int i = 0; i < 4; i++){
                            FIREBALL tmp;
                            tmp.m = m_total;
                            tmp.s = s_total;
                            tmp.d = setDir1[i];
                            new_board[y][x].push(tmp);
                        }
                    }
                    else{
                        for(int i = 0; i < 4; i++){
                            FIREBALL tmp;
                            tmp.m = m_total;
                            tmp.s = s_total;
                            tmp.d = setDir2[i];
                            new_board[y][x].push(tmp);
                        }
                    }
                }
            }
        }
    }

    for(int y = 0; y < N; y++){
        for(int x = 0; x < N; x++){
            board[y][x] = new_board[y][x];
        }
    }
}

int main() {
    cin >> N >> M >> K;
    for(int i = 0; i < M; i++){
        int r, c, m, s, d;
        FIREBALL tmp;
        cin >> r >> c >> m >> s >> d;
        r--, c--;
        tmp.m = m, tmp.s = s, tmp.d = d;
        board[r][c].push(tmp);
    }
    for(int i = 0; i < K; i++){
        solve();
    }
    int ans = 0;
    for(int y = 0; y < N; y++){
        for(int x = 0; x < N; x++){
            if(!board[y][x].empty()){
                while(!board[y][x].empty()){
                    FIREBALL front = board[y][x].front(); board[y][x].pop();
                    ans += front.m;
                }
            }
        }
    }
    cout << ans;
    return 0;
}