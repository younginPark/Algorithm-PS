#include <iostream>
#include <cstring>
using namespace std;

/*
가로와 세로 방향을 나누어서 생각해야 함
활주로 놓을 조건: 높이 차이가 1이고 지형의 높이가 경사로의 가로 길이랑 동일해야 함
*/

int N, X;
int ans = 0;
int board[21][21];
int visited[21][21];

void init(){
    memset(board, 0, sizeof(board));
    memset(visited, 0, sizeof(visited));
}

void userInput(){
    cin >> N >> X;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> board[i][j];
        }
    }
    ans = N * 2;
}
/*
현재 높이가 기존과 달라질 때
작아지는거면 현재위치+X-1 이 모두 같은 높이인지 확인해서 만약 아니면 해당 행 혹은 열 실패
커지는거면 현재위치-X+1 이 모두 같은 높이인지 확인해서 만약 아니면 해당 행 혹은 열 실패
*/
void solution(){
    for(int cy = 0; cy < N; cy++){
        int cx = 1;
        int h = board[cy][0];
        int cnt = 1;
        int flag = 0;
        while(cx < N){
            if(h != board[cy][cx]){
                if(h+1 == board[cy][cx]){
                    for(int i = X; i > 0; i--){
                        int nx = cx - i;
                        if(nx >= 0 && board[cy][nx] == h && visited[cy][nx] == 0){
                            visited[cy][nx] = 1;
                        }
                        else{
                            flag = 1;
                            break;
                        }
                    }
                    h = board[cy][cx];
                }
                else if(h-1 == board[cy][cx]){
                    for(int i = 0; i < X; i++){
                        int nx = cx + i; 
                        if(nx < N && board[cy][nx] == board[cy][cx] && visited[cy][nx] == 0){
                            visited[cy][nx] = 1;
                        }
                        else{
                            flag = 1;
                            break;
                        }
                    }
                    h = board[cy][cx];
                }
                else{
                    flag = 1;
                }
            }
            if(flag == 1){
                ans--;
                break;
            }
            cx++;
        }
        //cout << "가로: " << flag << "\n";
    }
    memset(visited, 0, sizeof(visited));
    for(int cx = 0; cx < N; cx++){
        int cy = 1;
        int h = board[0][cx];
        int cnt = 1;
        int flag = 0;
        while(cy < N){
            if(h != board[cy][cx]){
                if(h+1 == board[cy][cx]){
                    for(int i = X; i > 0; i--){
                        int ny = cy - i;
                        if(ny >= 0 && board[ny][cx] == h && visited[ny][cx] == 0){
                            visited[ny][cx] = 1;
                        }
                        else{
                            flag = 1;
                            break;
                        }
                    }
                    h = board[cy][cx];
                }
                else if(h-1 == board[cy][cx]){
                    for(int i = 0; i < X; i++){
                        int ny = cy + i;
                        if(ny < N && board[ny][cx] == board[cy][cx] && visited[ny][cx] == 0){
                            visited[ny][cx] = 1;
                        }
                        else{
                            flag = 1;
                            break;
                        }
                    }
                    h = board[cy][cx];
                }
                else{
                    flag = 1;
                }
            }
            if(flag == 1){
                ans--;
                break;
            }
            cy++;
        }
        //cout << "세로: " << flag << "\n";
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