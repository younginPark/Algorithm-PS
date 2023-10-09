#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

int dy[4] = { -1, +1, 0, 0 };
int dx[4] = { 0, 0, -1, +1 };

int dy2[4] = { 0, -1, 0, +1 };
int dx2[4] = { +1, 0, -1, 0 };

int N, M;
int sharkY, sharkX;
int cnt1 = 0, cnt2 = 0, cnt3 = 0;
int board[50][50];
vector<pair<int, int> > command;

void userInput(){
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> board[i][j];
        }
    }
    for(int i = 0; i < M; i++){
        int d, s;
        cin >> d >> s;
        d--;
        command.push_back(make_pair(d, s));
    }
    sharkY = N/2, sharkX = N/2;
}

void bombBall(int order){
    // 한번에 s만큼 이동하는 것이 아니라 for문을 s번 돌면서 한칸씩 구슬 파괴함
    // 파괴하면서 파괴된 구슬이 몇번이고 몇개였는지 추가하기
    int d = command[order].first;
    int s = command[order].second;
    for(int i = 1; i <= s; i++){
        int ny = sharkY + dy[d] * i;
        int nx = sharkX + dx[d] * i;
        if(board[ny][nx] == 1){
            cnt1++;
        }
        else if(board[ny][nx] == 2){
            cnt2++;
        }
        else if(board[ny][nx] == 3){
            cnt3++;
        }
        board[ny][nx] = 0;
    }
    
}

void pullBall(){
    // 1 2 2 3 3 .. N-1 N-1 N-1 
    // 1은 상어 왼쪽이니까 그냥 시작하자마자 빈값인지 체크해서 넣어줌
    // 3중 for문 (2 ~ N-1), (2, 3 번씩 도는거), (맨처음 i만큼 돌리는거)
    // 빈칸을 큐에 넣으면서 돌다가 빈 칸이 아닌 칸을 만나면 큐에서 pop해서 값 넣고 값 넣은 칸을 다시 큐에 넣음
    // 방향 시작은 오른쪽이고 3번째 for문 끝날 때마다 방향 바뀜
    queue<pair<int, int> > q;
    int cy = sharkY, cx = sharkX-1;
    int cd = 0;
    if(board[cy][cx] == 0){
        q.push(make_pair(cy, cx));
    }
    for(int i = 2; i < N; i++){
        for(int j = 0; j < 3; j++){
            if(i < N-1 && j == 2){
                continue;
            }
            for(int k = 1; k <= i; k++){
                cy = cy + dy[cd];
                cx = cx + dx[cd];
                if(board[cy][cx] == 0){
                    q.push(make_pair(cy, cx));
                }
                else if(board[cy][cx] != 0 && q.size() > 0){
                    int frontY = q.front().first;
                    int frontX = q.front().second;
                    q.pop();
                    board[frontY][frontX] = board[cy][cx];
                    board[cy][cx] = 0;
                    q.push(make_pair(cy, cx));
                }
            }
            cd = (cd + 1) % 4;
        }
    }
}

bool bombGroupBall(){
    // 4개 이상있어서 폭발하는지 체크하는 flag 필요
    int bombFlag = -1;
    queue<pair<int, int> > q;
    int cy = sharkY, cx = sharkX-1;
    int cd = 0;
    int color = board[cy][cx];
    q.push(make_pair(cy, cx));
    // 상어 왼쪽부터 돌면서 queue에 넣으면서 똑같은 번호 몇개 있는지 확인
    // 만약 이전까지의 색깔과 지금의 색깔이 다르면 queue 사이즈 4 이상인지 확인하고 아래처럼 한 후 색깔 지금꺼로 업데이트
    // 4 이상이면 해당 색깔에 따라 갯수 추가해주고, 큐 팝 하면서 board에 구슬들 다 폭발시킴,
    // 4 이상 아니라면 큐만 비워줌
    for(int i = 2; i < N; i++){
        for(int j = 0; j < 3; j++){
            if(i < N-1 && j == 2){
                continue;
            }
            for(int k = 1; k <= i; k++){
                cy = cy + dy[cd];
                cx = cx + dx[cd];
                if(board[cy][cx] == 0){
                    break;
                }
                if(board[cy][cx] == color){
                    q.push(make_pair(cy, cx));
                }
                else if(board[cy][cx] != color){
                    // 4개 이상인지 확인해서 4개 이상이면 다 pop 해주고 지금 색깔과 개수로 update해주기
                    if(q.size() >= 4){
                        bombFlag = 1;
                        if(color == 1){
                            cnt1 += q.size();
                        }
                        else if(color == 2){
                            cnt2 += q.size();
                        }
                        else if(color == 3){
                            cnt3 += q.size();
                        }
                        while(!q.empty()){
                            int frontY = q.front().first;
                            int frontX = q.front().second;
                            board[frontY][frontX] = 0;
                            q.pop();
                        }
                    }
                    else{
                        while(!q.empty()){
                            q.pop();
                        }
                    }
                    color = board[cy][cx];
                    q.push(make_pair(cy, cx));
                }
            }
            cd = (cd + 1) % 4;
        }
    }
    // 반복 다 해서 for문 끝났을 때 큐 확인해서 큐에 사이즈가 4이상이면 다 pop해서 board 구슬 폭발시켜주기
    if(q.size() >= 4){
        bombFlag = 1;
        if(color == 1){
            cnt1 += q.size();
        }
        else if(color == 2){
            cnt2 += q.size();
        }
        else if(color == 3){
            cnt3 += q.size();
        }
        while(!q.empty()){
            int frontY = q.front().first;
            int frontX = q.front().second;
            board[frontY][frontX] = 0;
            q.pop();
        }
    }

    // flag에 따라 return true, false 해줌
    if(bombFlag == 1){
        return true;
    }
    return false;
}

void changeGroupBall(){
    // (구슬의 개수, 구슬의 색)
    // 새로운 격자 하나 만들어서 거기에다가 새로 넣어줌
    int new_board[50][50];
    memset(new_board, 0, sizeof(new_board));
    // 상어 왼쪽부터 돌면서 똑같은 번호가 몇개 있는지 확인 후 각 값에 따라 새로운 격자에 A, B 넣어줌
    queue<pair<int, int> > q;
    int cy = sharkY, cx = sharkX-1;
    int cd = 0;
    int color = board[cy][cx];
    q.push(make_pair(cy, cx));
    for(int i = 2; i < N; i++){
        for(int j = 0; j < 3; j++){
            if(i < N-1 && j == 2){
                continue;
            }
            for(int k = 1; k <= i; k++){
                cy = cy + dy[cd];
                cx = cx + dx[cd];
                if(board[cy][cx] == 0){
                    break;
                }
                if(board[cy][cx] == color){
                    q.push(make_pair(cy, cx));
                }
                else if(board[cy][cx] != color){
                    
                    color = board[cy][cx];
                    q.push(make_pair(cy, cx));
                }
            }
            cd = (cd + 1) % 4;
        }
    }
    // for문이 다 끝나고 나면 가지고 있던 수와 색깔을 다시 한번 넣어줌

    // 기존 격자에 새로운 격자 복사해서 넣어줌
}

void getAns(){
    // 1×(폭발한 1번 구슬의 개수) + 2×(폭발한 2번 구슬의 개수) + 3×(폭발한 3번 구슬의 개수)
}

void solution(){
    for(int i = 0; i < M; i++){
        bombBall(i);
        pullBall();
        while(bombGroupBall()){
            pullBall();
        }
        changeGroupBall();
    }   
}

int main(){
    userInput();
    solution();
    return 0;
}