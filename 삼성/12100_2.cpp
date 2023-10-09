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

void printBoard(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
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
    if(cDir == 0){ // 왼쪽
        for(int i = 0; i < N; i++){
            int stack_index = 0;
            bool is_stacked = false;
            for(int j = 0; j < N; j++){
                if(board[i][j] == 0){
                    continue;
                }
                if(is_stacked){
                    if(board[i][stack_index] == board[i][j]){
                        board[i][stack_index] += board[i][j];
                        stack_index++;
                        is_stacked = false;
                        board[i][j] = 0;
                    }
                    else{
                        stack_index++;
                        board[i][stack_index] = board[i][j];
                        if(j != stack_index){
                            board[i][j] = 0;
                        }
                        is_stacked = true;
                    }
                }
                else{
                    board[i][stack_index] = board[i][j];
                    is_stacked = true;
                    if(j != stack_index){
                        board[i][j] = 0;
                    }
                }
            }
        }
    }
    else if(cDir == 1){ // 위쪽
        for(int i = 0; i < N; i++){
            int stack_index = 0;
            bool is_stacked = false;
            for(int j = 0; j < N; j++){
                if(board[j][i] == 0){
                    continue;
                }
                if(is_stacked){
                    if(board[stack_index][i] == board[j][i]){
                        board[stack_index][i] += board[j][i];
                        stack_index++;
                        board[j][i] = 0;
                        is_stacked = false;
                    }
                    else{
                        stack_index++;
                        board[stack_index][i] = board[j][i];
                        if(j != stack_index){
                            board[j][i] = 0;
                        }
                        is_stacked = true;
                    }
                }
                else{
                    board[stack_index][i] = board[j][i];
                    is_stacked = true;
                    if(j != stack_index){
                        board[j][i] = 0;
                    }
                }
            }
        }
    }
    else if(cDir == 2){ // 오른쪽
        for(int i = 0; i < N; i++){
            int stack_index = N-1;
            bool is_stacked = false;
            for(int j = N-1; j >= 0; j--){
                if(board[i][j] == 0){
                    continue;
                }
                if(is_stacked){
                    if(board[i][stack_index] == board[i][j]){
                        board[i][stack_index] += board[i][j];
                        stack_index--;
                        is_stacked = false;
                        board[i][j] = 0;
                    }
                    else{
                        stack_index--;
                        board[i][stack_index] = board[i][j];
                        if(j != stack_index){
                            board[i][j] = 0;
                        }
                        is_stacked = true;
                    }
                }
                else{
                    board[i][stack_index] = board[i][j];
                    is_stacked = true;
                    if(j != stack_index){
                        board[i][j] = 0;
                    }
                }
            }
        }
    }
    else if(cDir == 3){ // 아래쪽
        for(int i = 0; i < N; i++){
            int stack_index = N-1;
            bool is_stacked = false;
            for(int j = N-1; j >= 0; j--){
                if(board[j][i] == 0){
                    continue;
                }
                if(is_stacked){
                    if(board[stack_index][i] == board[j][i]){
                        board[stack_index][i] += board[j][i];
                        stack_index--;
                        is_stacked = false;
                        board[j][i] = 0;
                    }
                    else{
                        stack_index--;
                        board[stack_index][i] = board[j][i];
                        is_stacked = true;
                        if(j != stack_index){
                            board[j][i] = 0;
                        }
                    }
                }
                else{
                    board[stack_index][i] = board[j][i];
                    is_stacked = true;
                    if(j != stack_index){
                        board[j][i] = 0;
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