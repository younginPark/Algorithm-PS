#include <iostream>
using namespace std;

int N, M, H;
bool visit[31][11];
int result = 4;

bool check(){
    for(int i = 1; i <= N; i++){
        int start = i;
        for(int j = 1; j <= H; j++){
            if(visit[j][start] == 1){
                start++;
            }
            else if(visit[j][start-1] == 1){
                start--;
            }
        }
        if(start != i){
            return false;
        }
    }
    return true;
}

void dfs(int cnt, int y, int x){
    if(cnt >= result){
        return;
    }
    if(check()){
        result = cnt;
        return;
    }
    if(cnt == 3){
        return;
    }
    for(int i = y; i <= H; i++){
        for(int j = x; j < N; j++){
            if(visit[i][j-1] == 0 && visit[i][j] == 0 && visit[i][j+1] == 0){
                visit[i][j] = 1;
                dfs(cnt+1, i, j);
                visit[i][j] = 0;
            }
        }
        x = 1;
    }
}

int main(){
    scanf("%d %d %d", &N, &M, &H);
    for(int i = 0; i < M; i++){
        int tmp1, tmp2;
        scanf("%d %d", &tmp1, &tmp2);
        visit[tmp1][tmp2] = 1; //tmp1 높이에서 tmp2, tmp2+1을 이엇다는 뜻
    }
    dfs(0, 1, 1);
    if(result == 4){
        printf("-1\n");
    }
    else{
        printf("%d\n", result);
    }
    return 0;
}