#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

int tc;
vector<int> arr[20002];
int visit[20001];
int result = 1;

void init(int nodeNum){
    for(int i = 0; i <= nodeNum; i++){
        arr[i].clear();
    }
    for(int i = 1; i <= 2000; i++){
        visit[i] = 0;
    }
    result = 1;
}

void bfs(int start){
    queue<pair<int, int> > q;
    q.push(make_pair(start, 2)); // 2 or 3
    while(!q.empty()){
        int front = q.front().first;
        int color = q.front().second;
        visit[front] = color;
        q.pop();
        for(int i = 0; i < arr[front].size(); i++){
            int now = arr[front][i];
            if(visit[now] == 0){
                if(color == 2){
                    q.push(make_pair(now, 3));
                }
                else{
                    q.push(make_pair(now, 2));
                }
            }
            else if(visit[now] != color){
                continue;
            }
            else{
                result = 0;
                return;
            }
        }   
    }
}

int main(){
    cin >> tc;
    for(int i = 0; i < tc; i++){
        int V, E;
        cin >> V >> E;
        for(int j = 0; j < E; j++){
            int u, v;
            cin >> u >> v;
            arr[u].push_back(v);
            arr[v].push_back(u);
        }
        for(int j = 1; j <= V; j++){
            bfs(j);
            if(result == 0){
                break;
            }
        }
        if(result == 0){
            printf("NO\n");
        }
        else{
            printf("YES\n");
        }
        init(V);
    }
    return 0;
}