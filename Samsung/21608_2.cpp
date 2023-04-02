#include <iostream>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;

int dy[4] = { -1, 0, +1, 0 };
int dx[4] = { 0, -1, 0, +1 };

int N;
int order[405];
int like[405][5];
int board[25][25];

int ans = 0;

queue<pair<int, int> > q;
queue<pair<int, int> > secondQueue;
queue<pair<int, int> > thirdQueue;

void userInput(){
    cin >> N;
    for(int i = 0; i < N*N; i++){
        cin >> order[i];
        order[i]--;
        cin >> like[order[i]][0] >> like[order[i]][1] >> like[order[i]][2] >> like[order[i]][3];
        like[order[i]][0]--; like[order[i]][1]--; like[order[i]][2]--; like[order[i]][3]--;
    }
}

void printBoard(){
    cout << "----------------\n";
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

void checkLike(int now){
    int likeStudent = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(board[i][j] != -1){
                continue;
            }
            int cnt = 0;
            for(int dir = 0; dir < 4; dir++){
                int ny = i + dy[dir];
                int nx = j + dx[dir];
                if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                    continue;
                }
                for(int person = 0; person < 4; person++){
                    if(board[ny][nx] == like[now][person]){
                        cnt++;
                        break;
                    }
                }
            }
            if(cnt > likeStudent){
                while(!q.empty()) q.pop();
                q.push(make_pair(i, j));
                likeStudent = cnt;
            }
            else if(cnt == likeStudent){
                q.push(make_pair(i, j));
            }
        }
    }
}

void checkEmpty(){
    int loopTime = q.size();
    int empty = 0;
    for(int i = 0; i < loopTime; i++){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        int cnt = 0;
        for(int dir = 0; dir < 4; dir++){
            int ny = y + dy[dir];
            int nx = x + dx[dir];
            if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                continue;
            }
            if(board[ny][nx] == -1){
                cnt++;
            }
        }
        if(cnt > empty){
            while(!secondQueue.empty()) secondQueue.pop();
            secondQueue.push(make_pair(y, x));
            empty = cnt;
        }
        else if(cnt == empty){
            secondQueue.push(make_pair(y, x));
        }
    }
}

// void checkRowCol(){
//     int loopTime = secondQueue.size();
//     int lastY = q.front().first;
//     int lastX = 
// }

void init(){
    while(!q.empty()) q.pop();
    while(!secondQueue.empty()) secondQueue.pop();
    while(!thirdQueue.empty()) thirdQueue.pop();
}

void addPoint(int num){
    if(num == 1){
        ans += 1;
    }
    else if(num == 2){
        ans += 10;
    }
    else if(num == 3){
        ans += 100;
    }
    else if(num == 4){
        ans += 1000;
    }
}

void getSatisfaction(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            int cnt = 0;
            int now = board[i][j];
            for(int dir = 0; dir < 4; dir++){
                int ny = i + dy[dir];
                int nx = j + dx[dir];
                if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                    continue;
                }
                for(int person = 0; person < 4; person++){
                    if(board[ny][nx] == like[now][person]){
                        cnt++;
                        break;
                    }
                }
            }
            addPoint(cnt);
        }
    }
}

void solution(){
    memset(board, -1, sizeof(board));
    for(int i = 0; i < N*N; i++){
        checkLike(order[i]);
        int lastY, lastX;
        if(q.size() >= 2){
            checkEmpty();
            lastY = secondQueue.front().first;
            lastX = secondQueue.front().second;
        }
        else{
            lastY = q.front().first;
            lastX = q.front().second;
        }
        board[lastY][lastX] = order[i];
        init();
    }
    getSatisfaction();
}

int main(){
    userInput();
    solution();
    cout << ans;
    return 0;
}