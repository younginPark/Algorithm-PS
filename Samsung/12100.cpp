#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int dy[4] = { 0, -1, 0, +1 };
int dx[4] = { -1, 0, +1, 0 };

int N;
int board[25][25];
int ans = -1;

void userInput(){
    cin >> N;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> board[i][j];
        }
    }
}

void getAns(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            ans = max(ans, board[i][j]);
        }
    }
}

void dfs(int times, int cDir){
    if(times > 5){
        getAns();
        return;
    }
    // cDir에 따라 일단 이동
    int moveCheck[25][25];
    memset(moveCheck, 0, sizeof(moveCheck));
    if(cDir == 0){ // 왼쪽
        for(int i = 0; i < N; i++){
            for(int j = 1; j < N; j++){
                if(board[i][j] == 0){
                    continue;
                }
                int cx = j;
                while(cx > 0){
                    // 앞에 칸이 비어있으면 이동
                    if(board[i][cx-1] == 0){
                        board[i][cx-1] = board[i][cx];
                        board[i][cx] = 0;
                        cx--;
                    }
                    // 비어있지 않고 값이 같으면서 아직 안합쳐진 칸이면 합치기
                    else if((board[i][cx-1] == board[i][cx]) && moveCheck[i][cx-1] == 0){
                        board[i][cx-1] += board[i][cx];
                        board[i][cx] = 0;
                        moveCheck[i][cx-1] = 1;
                        break;
                    }
                    // 비어있지 않고 값이 다르면 그대로 || 비어있지 않고 값이 같지만 이미 합쳐진 칸이면 그대로
                    else{
                        break;
                    }
                }
            }
        }
    }
    else if(cDir == 1){ // 위쪽
        for(int i = 0; i < N; i++){
            for(int j = 1; j < N; j++){
                if(board[j][i] == 0){
                    continue;
                }
                int cy = j;
                while(cy > 0){
                    // 앞에 칸이 비어있으면 이동
                    if(board[cy-1][i] == 0){
                        board[cy-1][i] = board[cy][i];
                        board[cy][i] = 0;
                        cy--;
                    }
                    // 비어있지 않고 값이 같으면서 아직 안합쳐진 칸이면 합치기
                    else if((board[cy-1][i] == board[cy][i]) && moveCheck[cy-1][i] == 0){
                        board[cy-1][i] += board[cy][i];
                        board[cy][i] = 0;
                        moveCheck[cy-1][i] = 1;
                        break;
                    }
                    // 비어있지 않고 값이 다르면 그대로 || 비어있지 않고 값이 같지만 이미 합쳐진 칸이면 그대로
                    else{
                        break;
                    }
                }
            }
        }
    }
    else if(cDir == 2){ // 오른쪽
        for(int i = 0; i < N; i++){
            for(int j = N-2; j >= 0; j--){
                if(board[i][j] == 0){
                    continue;
                }
                int cx = j;
                while(cx < N-1){
                    // 앞에 칸이 비어있으면 이동
                    if(board[i][cx+1] == 0){
                        board[i][cx+1] = board[i][cx];
                        board[i][cx] = 0;
                        cx++;
                    }
                    // 비어있지 않고 값이 같으면서 아직 안합쳐진 칸이면 합치기
                    else if((board[i][cx+1] == board[i][cx]) && moveCheck[i][cx+1] == 0){
                        board[i][cx+1] += board[i][cx];
                        board[i][cx] = 0;
                        moveCheck[i][cx+1] = 1;
                        break;
                    }
                    // 비어있지 않고 값이 다르면 그대로 || 비어있지 않고 값이 같지만 이미 합쳐진 칸이면 그대로
                    else{
                        break;
                    }
                }
            }
        }
    }
    else if(cDir == 3){ // 아래쪽
        for(int i = 0; i < N; i++){
            for(int j = N-2; j >= 0; j--){
                if(board[j][i] == 0){
                    continue;
                }
                int cy = j;
                while(cy < N-1){
                    // 앞에 칸이 비어있으면 이동
                    if(board[cy+1][i] == 0){
                        board[cy+1][i] = board[cy][i];
                        board[cy][i] = 0;
                        cy++;
                    }
                    // 비어있지 않고 값이 같으면서 아직 안합쳐진 칸이면 합치기
                    else if((board[cy+1][i] == board[cy][i]) && moveCheck[cy+1][i] == 0){
                        board[cy+1][i] += board[cy][i];
                        board[cy][i] = 0;
                        moveCheck[cy+1][i] = 1;
                        break;
                    }
                    // 비어있지 않고 값이 다르면 그대로 || 비어있지 않고 값이 같지만 이미 합쳐진 칸이면 그대로
                    else{
                        break;
                    }
                }
            }
        }
    }

    // dfs 넣어주기
    int copy_board[25][25] = { 0, };
    for(int dir = 0; dir < 4; dir++){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                copy_board[i][j] = board[i][j];
            }
        }
        dfs(times+1, dir);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                board[i][j] = copy_board[i][j];
            }
        }
    } 
}

int main(){
    userInput();
    int copy_board[25][25] = { 0, };
    for(int dir = 0; dir < 4; dir++){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                copy_board[i][j] = board[i][j];
            }
        }
        dfs(1, dir);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                board[i][j] = copy_board[i][j];
            }
        }
    }

    cout << ans;
    return 0;
}