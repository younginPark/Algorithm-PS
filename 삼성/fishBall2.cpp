#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int dy[4] = { 0, 1, 0, -1 };
int dx[4] = { 1, 0, -1, 0 };
int N, K;
vector<vector<int> > board;

bool if_end(){
    int max_fishes = *max_element(board[0].begin(), board[0].end());
    int min_fishes = *min_element(board[0].begin(), board[0].end());
    return ((max_fishes - min_fishes) <= K);
}

void userInput(){
    cin >> N >> K;
    board = vector<vector<int> >(N, vector<int>(N, -1));
    for(int i = 0; i < N; i++){
        cin >> board[0][i];
    }
}

void move_fishes(){
    vector<vector<int> > new_board = board;
    for(int y = 0; y < N; y++){
        for(int x = 0; x < N; x++){
            if(board[y][x] == -1) continue;
            for(int dir = 0; dir < 4; dir++){
                int ny = y + dy[dir];
                int nx = x + dx[dir];
                if(ny < 0 || nx < 0 || ny >= N || nx >= N || board[ny][nx] == -1){
                    continue;
                }
                // 음수면 알아서 빠지고 양수면 알아서 더해짐
                new_board[y][x] += (int) (board[ny][nx] - board[y][x]) / 5;
            }
        }
    }

    // board 바닥에 일자로 펴줌
    vector<int> flat_bowl;
    for(int x = 0; x < N; x++){
        for(int y = 0; y < N; y++){
            if(new_board[y][x] == -1) continue;
            else{
                flat_bowl.push_back(new_board[y][x]);
            }
        }
    }
    board = vector<vector<int> >(N, vector<int>(N, -1));
    board[0] = flat_bowl;
}

void move(){
    int ly = 1, lx = 1;
    int sx = 0;
    // 물고기 추가
    int min_fishes = *min_element(board[0].begin(), board[0].end());
    for(int i = 0; i < N; i++){
        if(board[0][i] == min_fishes){
            board[0][i]++;
        }
    }

    // 어항 말기
    while(sx + ly + lx <= N){ 
        // 현재 시작점 + ly => 다음 시작점, 거기에 + lx 해주면 다음 회전의 가로, <= 인건 시작점을 중복으로 더해서 -1 하고 < 해주거나 아니면 그냥 <= 해주거나
        for(int y = 0; y < ly; y++){
            for(int x = 0; x < lx; x++){
                int ny = lx - x; // lx - 1 - x + 1 , +1은 항상 바닥칸보다 한층 위에서 시작해주므로
                int nx = sx + lx + y;
                board[ny][nx] = board[y][sx+x]; // y는 어차피 바닥 어항에 붙어있는걸 위로 올리는거니까 y 그대로 하면 됨
                board[y][sx+x] = -1; 
            }
        }
        sx += lx;
        if(ly == lx){
            ly++;
        }
        else{
            lx++;
        }
    }

    move_fishes(); // 인접한거 확인해서 물고기 수 조절

    sx = 0;
    ly = 1;
    lx = N / 2;
    for(int i = 0; i < 2; i++){
        for(int y = 0; y < ly; y++){
            for(int x = 0; x < lx; x++){
                int ny = 2 * ly - y - 1; // 두칸 위로 올라가야하니까 기존 ly에 2 곱해주고, y를 ly만큼 반복하면서 내려오니까 y 빼주고, ly * 2 하면 배열 기준으로 크니까 -1 해줘야 함
                int nx = 2 * lx + sx - x - 1; // 마찬가지로 접히는거니까 2배 이후부터 시작하니까 2 곱해주고, 앞에 배열이 떙겨지는게 아니니까 sx 꼭 더해줘야 하고 x로 lx 만큼 조절해주고 배열이니까 -1 해줌
                // ny,nx는 끝에서부터 채우는거임
                board[ny][nx] = board[y][sx + x];
                board[y][sx + x] = -1;
            }
        }
        sx += lx;
        ly *= 2;
        lx /= 2;
    }
    move_fishes();
}

void solution(){
    int count = 0;
    while(!if_end()){
        count++;
        move();
    }
    cout << count;
}

int main(){
    userInput();
    solution();
    return 0;
}