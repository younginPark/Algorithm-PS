#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
int dy[4] = { -1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};
int N, M;
int arr[9][9];
int arr_copy[9][9];
int answer;

void copy(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            arr_copy[i][j] = arr[i][j];
        }
    }
}

void check(){ //바이러스 다 퍼트리고 안전 공간 세기
    copy();
    //printf("In Check Func\n");
    queue<pair<int, int> > q;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(arr_copy[i][j] == 2){
                q.push(make_pair(i, j));
            }
        }
    }
    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for(int i = 0; i < 4; i++){
            int newY = y + dy[i];
            int newX = x + dx[i];
            if(0 <= newY && newY < N && 0 <= newX && newX < M){
                if(arr_copy[newY][newX] == 0){
                    arr_copy[newY][newX] = 2;
                    q.push(make_pair(newY, newX));
                }
            }
        }
    }
    int cnt = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(arr_copy[i][j] == 0){
                cnt++;
            }
        }
    }
    answer = max(answer, cnt);
}

void wall(int cnt){ //빈칸에 벽 세우기
    if(cnt == 3){
        check();
        return;
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(arr[i][j] == 0){
                arr[i][j] = 1;
                wall(cnt+1);
                arr[i][j] = 0; 
            }
        }
    }
}

int main(){
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> arr[i][j];
        }
    }
    wall(0);
    printf("%d\n", answer);
    return 0;
}