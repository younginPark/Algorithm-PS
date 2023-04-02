#include <iostream>
using namespace std;

bool visit[9] = {false, };
int n;
int arr[9] = { 0, };

void dfs(int idx, int cnt){
    if(cnt == n){
        for(int i = 1; i <= n; i++){
            printf("%d ", arr[i]);
        }
        printf("\n");
        return;
    }

    for(int i = 1; i <= n; i++){
        if(visit[i] == false){
            visit[i] = true;
            arr[cnt+1] = i;
            dfs(i, cnt+1);
            visit[i] = false;
        }
    }

}

int main(){
    cin >> n;
    dfs(0, 0);
    return 0;
}