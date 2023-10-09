#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

struct GROUP {
    int y, x;
    int total_cnt;
    int rainbow_cnt;
};

int N, M;
int board[21][21];
int score = 0;
GROUP standard;

bool visit[21][21];


GROUP bfs(int y, int x){
    queue<pair<int, int> > q;
    GROUP standard_block;
    bool visit_bfs[21][21];
    memset(visit_bfs, false, sizeof(visit_bfs));

    standard_block.y = y, standard_block.x = x, standard_block.total_cnt = 1, standard_block.rainbow_cnt = 0;
    q.push(make_pair(y, x));
    visit[y][x] = true;
    int front_color = board[y][x];

    while(!q.empty()){
        int front_y = q.front().first;
        int front_x = q.front().second;
        q.pop();

        for(int dir = 0; dir < 4; dir++){
            int next_y = front_y + dy[dir];
            int next_x = front_x + dx[dir];
            int next_color = board[next_y][next_x];
            if(next_y < 0 || next_y >= N || next_x < 0 || next_x >= N){
                continue;
            }
            if(((front_color == next_color) || next_color == 0) && !visit_bfs[next_y][next_x]){ // 처음 블록 색과 같거나 무지개 색일 때만 가능
                if(board[next_y][next_x] == 0){
                    standard_block.rainbow_cnt++;
                }
                else{
                    visit[next_y][next_x] = true;
                    if(standard_block.y > next_y || (standard_block.y == next_y && standard_block.x > next_x)){
                        standard_block.y = next_y;
                        standard_block.x = next_x;
                    }
                }
                visit_bfs[next_y][next_x] = true;
                standard_block.total_cnt++;
                q.push(make_pair(next_y, next_x));
            }
        }

    }
    return standard_block;

}

void removeBFS(int y, int x){
    queue<pair<int, int> > q;
    int front_color = board[y][x];
    board[y][x] = -9;
    cout << "지울 색깔: " << front_color << "\n";
    q.push(make_pair(y, x));
    int count = 1;
    while(!q.empty()){
        int front_y = q.front().first;
        int front_x = q.front().second;
        q.pop();

        for(int dir = 0; dir < 4; dir++){
            int next_y = front_y + dy[dir];
            int next_x = front_x + dx[dir];
            if(next_y < 0 || next_y >= N || next_x < 0 || next_x >= N){
                continue;
            }
            if(board[next_y][next_x] == -1){
                continue;
            }
            if(front_color == board[next_y][next_x] || board[next_y][next_x] == 0){
                q.push(make_pair(next_y, next_x));
                board[next_y][next_x] = -9;
                count++;
            }
        }
    }
    score += count*count;
    cout << "----------remove-----------\n";
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

void gravity(){
    for(int y = N-1; y >= 0; y--){
        for(int x = 0; x < N; x++){
            int cur_y = y;
            int cur_block = board[y][x];
            if(cur_block == -1){
                continue;
            }
            while(cur_y+1 < N && board[cur_y+1][x] == -9){
                board[cur_y+1][x] = cur_block;
                board[cur_y][x] = -9;
                cur_y++;
                
            }
        }
    }
    cout << "------gravity------\n";
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

void reverseRotation(){
    int copy_board[21][21];
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            copy_board[i][j] = board[j][N-1-i];
        }
    } 
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            board[i][j] = copy_board[i][j];
        }
    }
    cout << "------reverseRotation------\n";
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            scanf("%d", &board[i][j]);
        }
    }

    // N = 4, M = 3;
    // board[0][0] = 1; board[0][1] = 1; board[0][2] = 1; board[0][3] = 3;
    // board[1][0] = 3; board[1][1] = 2; board[1][2] = 3; board[1][3] = 3;
    // board[2][0] = 1; board[2][1] = 2; board[2][2] = -1; board[2][3] = 3;
    // board[3][0] = -1; board[3][1] = -1; board[3][2] = 1; board[3][3] = 1;

    while(1) { // autoplay 블록 그룹 있는 동안 반복
        standard.rainbow_cnt = 0, standard.total_cnt = 0, standard.y = 21, standard.x = 21;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                visit[i][j] = false;
            }
        }
        // 블록 별 기준 블록 찾아서 저장, 하나씩 함수에 넣고 방문 체크해주기, 해당 블록 기준으로 bfs탐색해서 하나의 그룹으로 묶기
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(board[i][j] != -1 && board[i][j] != 0 && board[i][j] != -9 && !visit[i][j]){ // 검은색도 무지개도 아닌 일반 블록 일 때
                    GROUP bfs_result = bfs(i, j);
                    if(standard.total_cnt < bfs_result.total_cnt){
                        standard = bfs_result;
                    }
                    else if(standard.total_cnt == bfs_result.total_cnt){
                        if(standard.rainbow_cnt < bfs_result.rainbow_cnt){
                            standard = bfs_result;
                        }
                        else if(standard.rainbow_cnt == bfs_result.rainbow_cnt){
                            if(standard.y < bfs_result.y || (standard.y == bfs_result.y && standard.x < bfs_result.x)){
                                standard = bfs_result;
                            }
                        }
                    }
                }
            }
        } 
        // 블록의 갯수가 1개이면 블록그룹이 아니므로 autoplay 중단
        if(standard.total_cnt == 1 || standard.y == 21){
            break;
        }
        cout << "standard: " << standard.y << ", " << standard.x << "\n";
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                cout << board[i][j] << " ";
            }
            cout << "\n";
        }
        removeBFS(standard.y, standard.x);
        gravity();
        reverseRotation();
        gravity();
        cout << "----------\n";
        cout << "current score: " << score << "\n"; 
    }
    printf("%d\n", score);
    return 0;

}