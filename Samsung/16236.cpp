#include <iostream>
#include <queue>
using namespace std;

int dy[4] = { 0, 0, -1, +1 };
int dx[4] = { -1, +1, 0, 0 };

int N;
int board[21][21];

struct SHARK {
    int y, x, time;
};

int shark_size = 2, shark_eat = 0;

int main(){
    cin >> N;
    SHARK shark;
    for(int y = 0; y < N; y++){
        for(int x = 0 ; x < N; x++){
            cin >> board[y][x];
            if(board[y][x] == 9){
                shark.y = y, shark.x = x, shark.time = 0;
                board[y][x] = 0;
            }
        }
    }

    bool is_update = true;
    while(is_update){
        is_update = false;
        queue <SHARK> q;
        bool visited[21][21] = { false, };
        q.push(shark);
        visited[shark.y][shark.x] = true;
        
        SHARK candi;
        candi.y = 21, candi.time = -1;
        while(!q.empty()){
            SHARK cur = q.front(); q.pop();
            if(candi.time < cur.time && candi.time != -1){
                break;
            }
            if(board[cur.y][cur.x] < shark_size && board[cur.y][cur.x] != 0){
                is_update = true;
                if(candi.y > cur.y || (candi.y == cur.y && candi.x > cur.x)){
                    candi = cur;
                }
            }
            for(int dir = 0; dir < 4; dir++){
                SHARK next;
                next.y = cur.y + dy[dir];
                next.x = cur.x + dx[dir];
                next.time = cur.time + 1;
                if(next.y < 0 || next.y >= N || next.x < 0 || next.x >= N){
                    continue;
                }
                if(board[next.y][next.x] <= shark_size && visited[next.y][next.x] == false){
                    visited[next.y][next.x] = true;
                    q.push(next);
                }
            }
        }
        if(is_update){
            shark = candi;
            shark_eat++;
            if(shark_eat == shark_size){
                shark_size++;
                shark_eat = 0; // 까먹지마
            }
            board[shark.y][shark.x] = 0;
        }
    }
    printf("%d", shark.time);
    return 0;
}