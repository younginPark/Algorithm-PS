#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

/*
쌩구현 문제

핀볼은 상하좌우 한 방향으로 움직이고 블록, 웜홀, 블랙홀을 만나지 전까지 한 방향으로 움직임
블록의 경사면에 부딪히면 직각으로 방향 꺾이고 그 이외에는 방향만 반대로 돌아옴
벽을 만났을 때는 반대 방향으로 돌아옴
웜홀에 빠지면 같은 숫자 가진 다른 웜홀로 빠져나오고 진행방향은 그대로 유지
블랙홀 만나면 핀볼 사라지면서 게임 종료

출력정답: 벽에 부딪힌 횟수의 최대값
종료조건: 핀볼이 출발 위치로 돌아옴 or 블랙홀에 빠짐

고려사항
- 웜볼 저장은 struct 로 해서 한쌍의 웜볼을 숫자의 인덱스에 한번에 저장함 (6~10칸을 차지하니까 배열 크기 11로 함)
- 블록은 종류가 총 5개인데 번호별로 오는 방향에 따라 가는 방향을 반환하는 함수 만들기
- 시작은 블랙홀도, 웜홀도, 블록도 아닌 칸에서 4방향 다 해봐야 함
- 시작하자마자 부딪혀서 본인 위치로 오면 종료해야 함
- 블록이나 벽끼리 부딪히면서 무한반복 할 수도 있음 => 이런경우없음!!! 무조건 본인이 시작한 위치로라도 돌아오게 되어 있음

구현방식
1. 시작은 블랙홀도, 웜홀도, 블록도 아닌 칸에서 4방향을 for문 돌면서 진행
2. 블록,웜홀,벽,블랙홀,시작위치가 아니면 해당 방향으로 무한반복 진행
- 벽일 때
    방향을 바꿔서 진행한 만큼 한번에 반대로 바로 이동 (한칸씩 이동X)
    정답변수에 +1
- 블록일 때
    번호에 따라 다름
    1번의 경우 위에서 아래로 왔을 경우 오른쪽으로 방향 전환, 오른쪽에서 왼쪽으로 왔을 경우 위로 방향 전환, 나머지는 본인 방향의 반대로
    2번의 경우 아래에서 위로 왔을 경우 오른쪽으로 방향 전환, 오른쪽에서 왼쪽으로 왔을 경우 아래로 방향 전환, 나머지는 본인 방향의 반대로
    3번의 경우 아래에서 위로 왔을 경우 왼쪽으로 방향 전환, 왼쪽에서 오른쪽으로 왔을 경우 아래로 방향 전환, 나머지는 본인 방향의 반대로
    4번의 경우 위에서 아래로 왔을 경우 왼쪽으로 방향 전환, 왼쪽에서 오른쪽으로 왔을 경우 위로 방향 전환, 나머지는 본인 방향의 반대로
    5번의 경우 모두 본인의 방향 반대로
    ** 이때 본인의 방향과 반대일 경우에는 벽일 때와 마찬가지로 진행한 만큼 한번에 반대로 이동하면 됨
- 웜홀일 때
    해당 번호의 웜홀을 찾아서 현재 나의 위치가 아닌 웜홀의 위치로 현재 위치 이동 (방향은 변함X)
- 블랙홀이거나 시작위치일 때
    반복분 종료
- 위의 경우 모두 아니여서 진행 방향으로 가면 될 때
    몇번째로 진행 중인지 +1씩 해주면서 진행
*/

int dy[4] = { 0, 0, +1, -1 };
int dx[4] = { +1, -1, 0, 0 };

int N;
int ans = 0;
int startY, startX;
int y, x, d;
struct WORMHOLE{
    int num;
    int y1, x1;
    int y2, x2;
};
WORMHOLE wormhole[11];
int board[101][101];

void init(){   
    ans = 0;
    memset(board, 0, sizeof(board));
    memset(wormhole, -1, sizeof(wormhole));
}

void userInput(){
    cin >> N;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> board[i][j];
            if(6 <= board[i][j] && board[i][j] <= 10){
                if(wormhole[board[i][j]].num == -1){
                    wormhole[board[i][j]].num = board[i][j];
                    wormhole[board[i][j]].y1 = i;
                    wormhole[board[i][j]].x1 = j;
                }
                else{
                    wormhole[board[i][j]].y2 = i;
                    wormhole[board[i][j]].x2 = j;
                }
            }
        }
    }
}
void meetBlock(int blockNum){
    if(blockNum == 1){
        if(d == 0){
            d = 1;
        }
        else if(d == 1){
            d = 3;
        }
        else if(d == 2){
            d = 0;
        }
        else if(d == 3){
            d = 2;
        }
    }
    else if(blockNum == 2){
        if(d == 0){
            d = 1;
        }
        else if(d == 1){
            d = 2;
        }
        else if(d == 2){
            d = 3;
        }
        else if(d == 3){
            d = 0;
        }
    }
    else if(blockNum == 3){
        if(d == 0){
            d = 2;
        }
        else if(d == 1){
            d = 0;
        }
        else if(d == 2){
            d = 3;
        }
        else if(d == 3){
            d = 1;
        }
    }
    else if(blockNum == 4){
        if(d == 0){
            d = 3;
        }
        else if(d == 1){
            d = 0;
        }
        else if(d == 2){
            d = 1;
        }
        else if(d == 3){
            d = 2;
        }
    }
    else if(blockNum == 5){
        if(d == 0){
            d = 1;
        }
        else if(d == 1){
            d = 0;
        }   
        else if(d == 2){
            d = 3;
        }
        else if(d == 3){
            d = 2;
        }
    }
}

void checkState(){
    int tmp_ans = 0;
    int first = 1;
    while(1){
        if(board[y][x] == -1 || (first == 0 && y == startY && x == startX)){
            break;
        }
        else if(y < 0 || x < 0 || y >= N || x >= N){
            tmp_ans++;
            if(d == 0){
                d = 1;
            }
            else if(d == 1){
                d = 0;
            }
            else if(d == 2){
                d = 3;
            }
            else if(d == 3){
                d = 2;
            }
            y = y + dy[d];
            x = x + dx[d];
        }
        else if(1 <= board[y][x] && board[y][x] <= 5){
            tmp_ans++;
            meetBlock(board[y][x]);
            y = y + dy[d];
            x = x + dx[d];
        }
        else if(6 <= board[y][x] && board[y][x] <= 10){
            int num = board[y][x];
            if(y == wormhole[num].y1 && x == wormhole[num].x1){
                y = wormhole[num].y2;
                x = wormhole[num].x2;
            }
            else{
                y = wormhole[num].y1;
                x = wormhole[num].x1;
            }
            y = y + dy[d];
            x = x + dx[d];
        }
        else if(board[y][x] == 0){
            y = y + dy[d];
            x = x + dx[d];
            //cout<< "!: " << y << ", " << x << "\n";
        }
        first = 0;
    }
    //cout << tmp_ans << "\n";
    ans = max(ans, tmp_ans);
}

void solution(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(board[i][j] == 0){
                startY = i, startX = j;
                for(int dir = 0; dir < 4; dir++){
                    //cout << "start: " << i << ", " << j << "\n";
                    y = i, x = j, d = dir;
                    checkState();
                }
            }
        }
    }
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