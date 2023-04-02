#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int dy[4] = { 0, +1, 0, -1 };
int dx[4] = { +1, 0, -1, 0 };

int N, K;
vector<vector<int> > board;

void userInput(){
    cin >> N >> K;
    board = vector<vector<int > >(N, vector<int>(N, -1));
    for(int i = 0; i < N; i++){
        cin >> board[0][i];
    }
}

bool if_end(){
    int max_num = *max_element(board[0].begin(), board[0].end());
    int min_num = *min_element(board[0].begin(), board[0].end());
    if(max_num - min_num <= K){
        return true;
    }
    return false;
}

void move_fishes(){
    vector<vector<int> > copy_board = board;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(board[i][j] == -1) continue;
            // 비교해서 각각에 바로바로 적용하면 2바퀴만 돌려도 되지만 
            // 아래 방식은 돌면서 빼고, 돌면서 더하고 이런거여서 4바퀴 다 돌려야함
            // 그렇지 않으면 하나는 빼거나 더해지고 나머지 하나는 비교만 하고 끝남
            for(int dir = 0; dir < 4; dir++){
                int ny = i + dy[dir];
                int nx = j + dx[dir];
                if(ny < 0 || nx < 0 || ny >= N || nx >= N || board[ny][nx] == -1){
                    continue;
                }
                else{
                    copy_board[i][j] += (board[ny][nx] - board[i][j]) / 5;
                }
            }
        }
    }

    vector<int> flat_bowl;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(copy_board[j][i] == -1) continue;
            flat_bowl.push_back(copy_board[j][i]);
        }
    }

    board = vector<vector<int> >(N, vector<int>(N, -1));
    board[0] = flat_bowl;
}

void move(){
    // 제일 물고기 수 적은 칸에 물고기 넣어주기
    int min_num = *min_element(board[0].begin(), board[0].end());
    for(int i = 0; i < N; i++){
        if(board[0][i] == min_num){
            board[0][i] += 1;
        }
    }
    // 어항 말기
    int sx = 0;
    int ly = 1, lx = 1;
    while(sx + ly + lx <= N){
        for(int y = 0; y < ly; y++){
            for(int x = 0; x < lx; x++){
                int ny = lx - x; // y는 lx크기만큼 올라감 (이동했을 경우의 젤 위에서부터 채움)
                int nx = sx + lx + y; // sx는 이전꺼의 시작 위치 + lx는 sx + lx 해줘서 다음 sx 위치 찾음 + ly 만큼 이동
                board[ny][nx] = board[y][sx+x];
                board[y][sx+x] = -1; // 기존의 yx 위치는 단순하게 생각하면 됨 y는 결국 끝에 ly 만큼 돌아야 하고 x도 마찬가지인데 sx만큼 이동한 곳에서 그만큼 돌면 됨
            }
        }
        sx += lx;
        if(lx == ly){
            ly++;
        }
        else{
            lx++;
        }
    }
    // 물고기 인접 수 조정
    move_fishes();
    
    // 어항 접기
    sx = 0;
    lx = N/2, ly = 1;
    for(int i = 0; i < 2; i++){
        for(int y = 0; y < ly; y++){
            for(int x = 0; x < lx; x++){
                // y, x 둘다 거꾸로 넣음
                int ny = (2 * ly) - 1 - y;
                int nx = sx + (2 * lx ) - 1 - x;
                board[ny][nx] = board[y][sx+x];
                board[y][sx+x] = -1;
            }
        }
        sx += lx;
        lx /= 2;
        ly *= 2;
    }

    // 물고기 인접 수 조정
    move_fishes();
}

int main(){
    userInput();
    int cnt = 0;
    while(!if_end()){
        cnt++;
        move();
    }
    cout << cnt << "\n";
    return 0;
}