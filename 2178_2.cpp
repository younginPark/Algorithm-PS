#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

int dy[4] = { -1, 1, 0, 0};
int dx[4] = { 0, 0, -1, 1};
int N, M;
int arr[101][101];
int visit[101][101];
int result;
queue<pair<pair<int, int>, int> > q;
void bfs(){
    while(!q.empty()){
        int y = q.front().first.first;
        int x = q.front().first.second;
        int cnt = q.front().second;
        q.pop();
        if(y == N-1 && x == M-1){
            result = cnt;
            return;
        }
        for(int i = 0; i < 4; i++){
            int newY = y + dy[i];
            int newX = x + dx[i];
            if(newY >= 0 && newY < N && newX >= 0 && newX < M){
                if(arr[newY][newX] == 1 && visit[newY][newX] == 0){
                    visit[newY][newX] = 1;
                    q.push(make_pair(make_pair(newY, newX), cnt+1));
                }
            }
        }
    }
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 0; i < N; i++){
        string str1;
        cin >> str1;
        for(int j = 0; j < M; j++){
            arr[i][j] = str1[j] - 48;
        }
    }
    visit[0][0] = 1;
    q.push(make_pair(make_pair(0, 0), 1));
    bfs();
    printf("%d\n", result);
    return 0;
}