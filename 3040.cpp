#include <iostream>
using namespace std;
#define NUM 9
bool ans;
int arr[10];
bool visit[10];

void dfs(int total) {
    if(ans) {
        return;
    }
    if(total == 100){
        int cnt = 0;
        for(int i = 0; i < NUM; i++){
            if(visit[i]){
                cnt++;
            }
        }
        if(cnt == 7){
            for(int i = 0; i < NUM; i++){
                if(visit[i]){
                    printf("%d\n", arr[i]);
                }
            }
            ans = true;
            return;
        }
    }
    for(int i = 0; i < NUM; i++){
        if(!visit[i]){
            total += arr[i];
            visit[i] = true;
            dfs(total);
            total -= arr[i];
            visit[i] = false;
        }
    }
    return;
}

int main() {
    for(int i = 0; i < NUM; i++){
        cin >> arr[i];
    }
    dfs(0);
    return 0;
}