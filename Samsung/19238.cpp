#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

int dy[4] = { -1, +1, 0, 0 };
int dx[4] = { 0, 0, -1, +1 };

int N, M, F;
int board[25][25];
int getCustomer = 0;
struct CURCUSTOMER {
    int y, x, dst, no;
};
struct CUSTOMER {
    int srcY, srcX, dstY, dstX;
};
CUSTOMER info[405];
struct TAXI {
    int y, x;
};
TAXI taxi;

void userInput(){
    cin >> N >> M >> F;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> board[i][j];
        }
    }
    cin >> taxi.y >> taxi.x;
    taxi.y--;
    taxi.x--;
    for(int i = 0; i < M; i++){
        cin >> info[i].srcY >> info[i].srcX >> info[i].dstY >> info[i].dstX;
        info[i].srcY--;
        info[i].srcX--;
        info[i].dstY--;
        info[i].dstX--;
        board[info[i].srcY][info[i].srcX] = i + 2;
    }
}

int moveTaxi(int customer_no){
    getCustomer++;
    int visit[25][25];
    memset(visit, -1, sizeof(visit));
    queue<pair<pair<int, int>, int> > q;
    q.push(make_pair(make_pair(info[customer_no].srcY, info[customer_no].srcX), 1));
    visit[info[customer_no].srcY][info[customer_no].srcX] = 1;
    while(!q.empty()){
        int cy = q.front().first.first;
        int cx = q.front().first.second;
        int cdst = q.front().second;
        q.pop();
        for(int dir = 0; dir < 4; dir++){
            int ny = cy + dy[dir];
            int nx = cx + dx[dir];
            if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                continue;
            }
            if(board[ny][nx] == 1 || visit[ny][nx] == 1){
                continue;
            }
            visit[ny][nx] = 1;
            if(ny == info[customer_no].dstY && nx == info[customer_no].dstX){
                // 택시 목적지로 이동시켜줌
                taxi.y = ny;
                taxi.x = nx;
                return cdst;
            }
            q.push(make_pair(make_pair(ny, nx), cdst+1));
        }
    }
    return -1;
}

void solution(){
    int customer_no = M;
    while(customer_no > 0){
        customer_no--;
        int visit[25][25];
        memset(visit, -1, sizeof(visit));
        queue<pair<pair<int, int>, int> > q;
        q.push(make_pair(make_pair(taxi.y, taxi.x), 1));
        visit[taxi.y][taxi.x] = 1;
        CURCUSTOMER cur_customer;
        cur_customer.dst = 401;
        // 택시의 출발지에 바로 승객이 있는지 확인
        if(board[taxi.y][taxi.x] >= 2){
            cur_customer.dst = 0;
            cur_customer.y = taxi.y;
            cur_customer.x = taxi.x;
            cur_customer.no = board[taxi.y][taxi.x] - 2;
            q.pop(); // q empty 만들기
        }
        while(!q.empty()){
            int cy = q.front().first.first;
            int cx = q.front().first.second;
            int cdst = q.front().second;
            q.pop();
            // 출발지에 바로 승객이 없다면 bfs로 이동하면서 승객 찾기
            for(int dir = 0; dir < 4; dir++){
                int ny = cy + dy[dir];
                int nx = cx + dx[dir];
                if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                    continue;
                }
                if(board[ny][nx] == 1 || visit[ny][nx] == 1){
                    continue;
                }
                visit[ny][nx] = 1;
                if(board[ny][nx] >= 2){
                    if(cur_customer.dst == cdst){
                        if(ny < cur_customer.y){
                            cur_customer.y = ny;
                            cur_customer.x = nx;
                            cur_customer.no = board[ny][nx] - 2;
                        }
                        else if(ny == cur_customer.y && nx < cur_customer.x){
                            cur_customer.y = ny;
                            cur_customer.x = nx;
                            cur_customer.no = board[ny][nx] - 2;
                        }
                    }
                    else if(cur_customer.dst > cdst){
                        cur_customer.dst = cdst;
                        cur_customer.y = ny;
                        cur_customer.x = nx;
                        cur_customer.no = board[ny][nx] - 2;
                    }
                }
                if(cdst <= cur_customer.dst){
                    q.push(make_pair(make_pair(ny, nx), cdst+1));
                }
            }
        }
        if(cur_customer.dst < 401){
            board[cur_customer.y][cur_customer.x] = 0;
            int moveDst = moveTaxi(cur_customer.no);
            if(moveDst == -1){
                F = -10;
                return;
            }
            F = F - cur_customer.dst - moveDst;
            // cout << cur_customer.dst << ", " << moveDst << "\n";
            // cout << cur_customer.no << " F: " << F <<"\n";
            if(F >= 0){
                F += (moveDst * 2);
            }
            else{
                return;
            }
        }
    }
}

int main(){
    userInput();
    solution();
    if(getCustomer == M && F >= 0){
        cout << F;
    }
    else{
        cout << -1;
    }
    return 0;
}