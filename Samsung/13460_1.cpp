#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int N, M;
char arr[11][11];
int ans = 11;

bool move(int dir){
    int bX, bY;
    int rX, rY;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(arr[i][j] == 'B'){
                bX = i;
                bY = j;
            }
            else if(arr[i][j] == 'R'){
                rX = i;
                rY = j;
            }
        }
    }

    if(dir == 0){ // 왼쪽
        while(1){
            // B 이동
            if(arr[bX][bY] == '0'){
                return false;
            }
            else if(arr[bX][bY] == '#'){
                break;
            }
            else{
                bY -= 1;
            }
        }
        while(1){
            // R 이동
            if(arr[rX][rY] == '#'){
                break;
            }
            else if(arr[rX][rY] == '0'){
                return true;
            }
            else {
                rY -= 1;
            }
        }
    }

    else if(dir == 1){ // 오른쪽
        printf("오른쪽 들어옴!!");
        while(1){
            // B 이동
            if(arr[bX][bY] == '0'){
                return false;
            }
            else if(arr[bX][bY] == '#'){
                break;
            }
            else{
                bY += 1;
            }
        }
        while(1){
            // R 이동
            if(arr[rX][rY] == '#'){
                break;
            }
            else if(arr[rX][rY] == '0'){
                printf("Here!!!!!!");
                return true;
            }
            else{
                rY += 1;
            }
        }
    }

    else if(dir == 2){ // 위
        while(1){
            // B 이동
            if(arr[bX][bY] == '0'){
                return false;
            }
            else if(arr[bX][bY] == '#'){
                break;
            }
            else{
                bX -= 1;
            }
        }
        while(1){
            // R 이동
            if(arr[rX][rY] == '#'){
                break;
            }
            else if(arr[rX][rY] == '0'){
                return true;
            }
            else{
                rX -= 1;
            }
        }

    }

    else if(dir == 3){ // 아래
        while(1){
            // B 이동
            if(arr[bX][bY] == '0' || arr[bX][bY] == '#'){
                break;
                return false;
            }
            else{
                bX += 1;
            }
        }
        while(1){
            // R 이동
            if(arr[rX][rY] == '#'){
                break;
            }
            else if(arr[rX][rY] == '0'){
                return true;
            }
            else{
                rX += 1;
            }
        }
    }

    return false;
}

int dfs(int cnt){
    char copied_arr[11][11];
    if(cnt >= ans){
        return 0;
    }
    else{
        for(int dir = 0; dir < 4; dir++){
            // 배열 복사해 놓기
            for(int i = 0; i < N; i++){
                for(int j = 0; j < M; j++){
                    copied_arr[i][j] = arr[i][j];
                }
            }
            // 좌우상하 이동 및 dfs 
            bool move_result = move(dir);
            // printf("%s", move_result?"true":"false");
            if(move_result){
                ans = min(cnt, ans);
            }
            else{
                dfs(cnt+1);
            }
            // dfs에서 돌아왔을 때 배열 원복
            for(int i = 0; i < N; i++){
                for(int j = 0; j < M; j++){
                    arr[i][j] = copied_arr[i][j];
                }
            }
        }
    }
    return 0;
}

int main(){
    scanf("%d %d", &N, &M);
    string str1;
    for(int i = 0; i < N; i++){
        cin >> str1;
        for(int j = 0; j < M; j++){
            arr[i][j] = str1[j];
        }   
    }

    dfs(0);

    if(ans > 10){
        printf("!! %d\n", ans);
        printf("%d", -1);
    }
    else{
        printf("%d", ans);
    }

    return 0;
}