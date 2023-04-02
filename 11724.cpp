#include <iostream>
using namespace std;

int N, M;
int arr[1001][1001];
int visit[1001];
int answer;
void dfs(int now){
    for(int i = 1; i <= N; i++){
        if(arr[now][i] == 1 && visit[i] == 0){
            visit[i] = 1;
            dfs(i);
        }
    }
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 0; i < M; i++){
        int tmp1, tmp2;
        scanf("%d %d", &tmp1, &tmp2);
        arr[tmp1][tmp2] = 1;
        arr[tmp2][tmp1] = 1;
    }
    for(int i = 1; i <= N; i++){
        if(visit[i] == 0){
            dfs(i);
            answer++;
        }
    }
    printf("%d\n", answer);
    return 0;
}