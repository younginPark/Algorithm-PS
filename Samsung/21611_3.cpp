#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int dy[4] = { -1, +1, 0, 0 };
int dx[4] = { 0, 0, -1, +1 };

int dy2[4] = { 0, +1, 0, -1 };
int dx2[4] = { -1, 0, +1, 0 };

int N, M;
int sharkY, sharkX;
int color_arr[4] = { 0, 0, 0, 0 };
int board[50][50];
int flat[2500];
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
        board[ny][nx] = 0;
    }
}

void flatBall(){
    memset(flat, 0, sizeof(flat));
    int cy = sharkY, cx = sharkX;
    int dir = 0;
    int idx = 0;
    for(int i = 1; i < N; i++){
        for(int j = 0; j < 3; j++){
            if(i < N-1 && j == 2){
                continue;
            }
            for(int k = 1; k <= i; k++){
                cy = cy + dy2[dir];
                cx = cx + dx2[dir];
                flat[idx++] = board[cy][cx];
            }
            dir = (dir+1) % 4;
        }
    }
}

void pullBall(){
    int copy_flat[2500];
    int idx = 0;
    memset(copy_flat, 0, sizeof(copy_flat));
    for(int i = 0; i < N*N; i++){
        if(flat[i] == 0){
            continue;
        }
        else{
            copy_flat[idx++] = flat[i];
        }
    }
    for (int i = 0; i < N * N; i++) {
		flat[i] = copy_flat[i];
	}
}

bool bombGroupBall(){
    int bombFlag = -1;
    int color = flat[0];
    int cnt = 1;
    int idx = 0;
    for(int i = 1; i < N*N; i++){
        if(flat[i] == color){
            cnt++;
        }
        else if(flat[i] != color && flat[i] != 0){
            if(cnt >= 4){
                bombFlag = 1;
                color_arr[color] += cnt;
                for(int j = idx; j < i; j++){
                    flat[j] = 0;
                }
            }
            color = flat[i];
            cnt = 1;
            idx = i;
        }
        if(flat[i] == 0){
            break;
        }
    }
    if(cnt >= 4){
        bombFlag = 1;
        color_arr[color] += cnt;
        for(int j = idx; j <= idx+cnt; j++){
            flat[j] = 0;
        }
    }
    if(bombFlag == 1){
        return true;
    }
    else{
        return false;
    }
}

void addBall(){
    int new_flat[2500];
    int idx = 0;
    int color = flat[0];
    int cnt = 1;
    memset(new_flat, 0, sizeof(new_flat));
    for(int i = 1; i < N*N; i++){
        if(flat[i] == color){
            cnt++;
        }
        else if(flat[i] != color){
            new_flat[idx] = cnt;
            new_flat[idx+1] = color;
            idx += 2;
            color = flat[i];
            cnt = 1;
        }
        if(flat[i] == 0 || idx >= N*N){
            break;
        }
    }

    for(int i = 0; i < N*N; i++){
        flat[i] = new_flat[i];
    }
}

void rollBack(){
    memset(board, 0, sizeof(board));
    int cy = sharkY, cx = sharkX;
    int dir = 0;
    int idx = 0;
    for(int i = 1; i < N; i++){
        for(int j = 0; j < 3; j++){
            if(i < N-1 && j == 2){
                continue;
            }
            for(int k = 1; k <= i; k++){
                cy = cy + dy2[dir];
                cx = cx + dx2[dir];
                board[cy][cx] = flat[idx++];
            }
            dir = (dir+1) % 4;
        }
    }
}

void getAns(){
    // 1×(폭발한 1번 구슬의 개수) + 2×(폭발한 2번 구슬의 개수) + 3×(폭발한 3번 구슬의 개수)
    int total = color_arr[1] * 1 + color_arr[2] * 2 + color_arr[3] * 3;
    cout << total; 
}

void printFlat(){
    for(int i = 0; i < N*N; i++){
        cout << flat[i] << " ";
    }
    cout << "\n";
}

void solution(){
    for(int i = 0; i < M; i++){
        bombBall(i);
        flatBall();
        pullBall();
        while(bombGroupBall() == 1){
            pullBall();
        }
        addBall();
        rollBack();
    }   
}

int main(){
    userInput();
    solution();
    getAns();
    return 0;
}