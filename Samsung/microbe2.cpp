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
    int y, x, num, dir;
};
queue<MICROBE> microbe;
vector<MICROBE> board[101][101];

int dy[4] = { -1, +1, 0, 0 };
int dx[4] = { 0, 0, -1, +1 };

void init(){
    ans = 0;
    while(!microbe.empty()) microbe.pop();
}

void userInput(){
    cin >> N >> M >> K;
    for(int i = 0; i < K; i++){
        MICROBE tmp;
        cin >> tmp.y >> tmp.x >> tmp.num >> tmp.dir;
        tmp.dir--;
        microbe.push(tmp);
    }
}

void printBoard(){
    cout << "------------------------\n";
    int microbe_size = microbe.size();
    for(int i = 0; i < microbe_size; i++){
        MICROBE front = microbe.front();
        cout << front.y << ", " << front.x << " " << front.num << " " << front.dir << "\n";
        microbe.pop();
        microbe.push(front);
    }
}

// 1) 이동 및 약품 칠해진 곳에 미생물 반 죽이고 방향 반대로
// 2) 한 셀에 군집 여러개면 하나로 합쳐주기

void solution(){
    while(M--){
        int microbe_size = microbe.size();
        for(int i = 0; i < microbe_size; i++){
            MICROBE cur_micro = microbe.front();
            microbe.pop();
            int ny = cur_micro.y + dy[cur_micro.dir];
            int nx = cur_micro.x + dx[cur_micro.dir];
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
            cur_micro.y = ny;
            cur_micro.x = nx;
            microbe.push(cur_micro);
            board[ny][nx].push_back(cur_micro);
        }

        microbe_size = microbe.size();
        for(int i = 0; i < microbe_size; i++){
            MICROBE cur_micro = microbe.front();
            microbe.pop();
            if(board[cur_micro.y][cur_micro.x].size() >= 2){
                int total_cnt = 0;
                int max_cnt = 0, max_dir = 0;
                for(int j = 0; j < board[cur_micro.y][cur_micro.x].size(); j++){
                    total_cnt += board[cur_micro.y][cur_micro.x][j].num;
                    if(board[cur_micro.y][cur_micro.x][j].num > max_cnt){
                        max_cnt = board[cur_micro.y][cur_micro.x][j].num;
                        max_dir = board[cur_micro.y][cur_micro.x][j].dir;
                    }
                }
                board[cur_micro.y][cur_micro.x].clear();
                cur_micro.num = total_cnt;
                cur_micro.dir = max_dir;
                microbe.push(cur_micro);
            }
            else if(board[cur_micro.y][cur_micro.x].size() == 1){
                microbe.push(cur_micro);
                board[cur_micro.y][cur_micro.x].clear();
            }
            else{
                continue;
            }
        }
        //printBoard();
    }  
    while(!microbe.empty()){
        MICROBE front = microbe.front();
        microbe.pop();
        ans += front.num;
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