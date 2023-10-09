#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

/*
예제 따라가보기
초기상태 -> 1시간 째에 1인 세포들 활성화 -> 2시간 째에 활성화된 세포들 번식 그리고 활성화 시간 끝난 세포들 죽이기
-> 활성화 시켜야하는 세포들 활성화 & 이미 활성화 되어 있는 세포들 번식 & 활성화 시간 끝난 세포들 죽이기 .. 무한반복

- 고려할 점
1. 활성화/비활성화 상태의 시간을 어떻게 관리할 것인지?
   ㄴ 0: 빈칸, 1~10 활성비활성 시간을 나타내는 입력 칸
   ㄴ flag 1: 비활성, 2: 활성, 3: 죽음 으로 해서
     번식현황 격자와 초기생명력/상태를 나타내는 격자 2개로 구분
     번식현황에서 0이 되면 상태를 보고 다음 상태로 넘기면서 해당 생명령 숫자로 초기화 해주는 방식으로 진행 
2. 격자 크기에 제한이 없음
   ㄴ 세포 정보가 가장 크게 주어지면 50x50 이고 최대 300시간 동안 번식하니까 300+300+50 이 한변 총 650임
      넉넉하게 1000x1000으로 하면 충분할거고, 입력을 받고 500씩 더해줘서 격자의 중간 위치로 옮기기
3. 동시에 하나의 그리드 셀에 번식하려는 경우
   ㄴ visited 격자를 두어서 만약 visited가 1이면 현재 타이밍에 번식해주고 있다는 의미로 생명력을 비교해서 더 큰 생명력으로 덮어씀

- 1시간마다 구현해야 하는 내용
각 세포들의 상태를 확인
만약 비활성 상태인데 생명력이 0이 되면 활성상태로 켜줌 그리고 생명력은 초기생명력으로 초기화, 그게 아니라면 -1 해줌
만약 활성 상태인데 초기생명력 == 현재생명력 => 4방향 번식 후 현재생명력 -1 해줌   
만약 활성 상태인데 현재생명력 == 0 => 죽은 상태로 변경, 그게 아니라면 현재생명력 -1 만 해주고 끝
만약 죽은 상태라면 그냥 패스

상태랑 초기생명력 필요할 때는 초기생명력/상태 격자를 사용하고
실제 번식과 시간 지날 때 -1씩 해줄 때는 
번식 격자에 -1이나 초기생명력으로 초기화해주고
초기생명력/상태 격자에는 번식 시에 초기생명력과 flag를 넣어줌 

- 정답구하기
정답은 초기생명력/상태를 나타내는 격자에서 flag가 0, 1인 세포들의 개수만 세기
*/

int dy[4] = { -1, 0, +1 , 0 };
int dx[4] = { 0, -1, 0, +1 };

int Y, X;
int N, M, K;
int ans = 0;
int board[401][401];
pair<int, int> state_board[401][401];
int visited[401][401];

void init(){
    ans = 0;
    memset(board, 0, sizeof(board));
    memset(state_board, 0, sizeof(state_board));
    memset(visited, 0, sizeof(visited));
}

void userInput(){
    cin >> N >> M >> K;
    int addNum = 180;
    Y = 390;
    X = 390;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> board[i+addNum][j+addNum];
            if(1 <= board[i+addNum][j+addNum] && board[i+addNum][j+addNum] <= 10){
                state_board[i+addNum][j+addNum].first = board[i+addNum][j+addNum];
                state_board[i+addNum][j+addNum].second = 1;
            }
        }
    }
}

// - 1시간마다 구현해야 하는 내용
// 각 세포들의 상태를 확인
// 만약 비활성 상태인데 생명력이 0이 되면 활성상태로 켜줌 그리고 생명력은 초기생명력으로 초기화, 그게 아니라면 -1 해줌
// 만약 활성 상태인데 초기생명력 == 현재생명력 => 4방향 번식 후 현재생명력 -1 해줌   
// 만약 활성 상태인데 현재생명력 == 0 => 죽은 상태로 변경, 그게 아니라면 현재생명력 -1 만 해주고 끝
// 만약 죽은 상태라면 그냥 패스

// 상태랑 초기생명력 필요할 때는 초기생명력/상태 격자를 사용하고
// 실제 번식과 시간 지날 때 -1씩 해줄 때는 
// 번식 격자에 -1이나 초기생명력으로 초기화해주고
// 초기생명력/상태 격자에는 번식 시에 초기생명력과 flag를 넣어줌 

void printBoard(){
    cout << "-----------\n";
    for(int i = 495; i < 510; i++){
        for(int j = 495; j < 510; j++){
            cout << state_board[i][j].second << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    for(int i = 495; i < 510; i++){
        for(int j = 495; j < 510; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

void propagation(int y, int x){
    //cout << y-500 << ", " << x-500 << "\n";
    int lifetime = state_board[y][x].first;
    for(int dir = 0; dir < 4; dir++){
        int ny = y + dy[dir];
        int nx = x + dx[dir];
        if(visited[ny][nx] == 0 && state_board[ny][nx].first > 0){
            continue;
        }
        else if(visited[ny][nx] == 1){
            if(lifetime > state_board[ny][nx].first){
                state_board[ny][nx].first = lifetime;
                board[ny][nx] = lifetime;
            }
        }
        else{
            state_board[ny][nx].first = lifetime;
            state_board[ny][nx].second = 1;
            board[ny][nx] = lifetime;
            visited[ny][nx] = 1;
        }
    }
}

void checkState(){
    for(int i = 0; i < Y; i++){
        for(int j = 0; j < X; j++){
            if(visited[i][j] == 1) continue;
            if(state_board[i][j].second == 1){
                if(board[i][j] - 1 == 0){
                    state_board[i][j].second = 2;
                    board[i][j] = state_board[i][j].first;
                }
                else{
                    board[i][j]--;
                }
            }
            else if(state_board[i][j].second == 2){
                if(board[i][j] == state_board[i][j].first){
                    propagation(i, j);
                    board[i][j]--;
                }
                else if(board[i][j] == 0){
                    state_board[i][j].second = 3;
                }
                else{
                    board[i][j]--;
                }
                if(board[i][j] == 0){
                    state_board[i][j].second = 3;
                }
            }
            else if(state_board[i][j].second == 3){
                continue;
            }
        }
    }
}

void getAns(){
    for(int i = 0; i < Y; i++){
        for(int j = 0; j < X; j++){
            if(state_board[i][j].second == 1 || state_board[i][j].second == 2){
                ans++;
            }
        }
    }
}

void solution(){
    for(int i = 0; i < K; i++){
        memset(visited, 0, sizeof(visited));
        checkState();
        //printBoard();
    }
    getAns();
}

void solve(){
    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++){
        init();
        userInput();
        solution();
        cout << "#" << tc << " " << ans << "\n";
    }
}

int main(){
    solve();
    return 0;
}