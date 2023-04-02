#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

int dy[4] = { -1, 0, +1, 0 };
int dx[4] = { 0, -1, 0, +1 }; 

int ans = -1;
int N, M;
int board[55][55];
int visited[55][55];
int check[15];
struct VIRUS{
    int y, x;
};
vector<VIRUS> info;

int virusCheck(){
    int result = 1;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(visited[i][j] == 0 && board[i][j] == 0){
                result = 0;
                return result;
            }
        }
    }
    return result;
}

void userInput(){
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> board[i][j];
            if(board[i][j] == 2){
                VIRUS tmp;
                tmp.y = i; tmp.x = j;
                info.push_back(tmp);
            }
        }
    }
}

void dfs(int idx, int cnt){
    if(cnt == M){
        // check 인 것만 bfs 실행
        queue<pair<pair<int, int>, int> > active;
        memset(visited, 0, sizeof(visited));
        for(int i = 0; i < info.size(); i++){
            if(check[i] == 1){
                active.push(make_pair(make_pair(info[i].y, info[i].x), 0));
                visited[info[i].y][info[i].x] = true;
            }
        }
        int tmp = 0;
        while(!active.empty()){
            int y = active.front().first.first;
            int x = active.front().first.second;
            int times = active.front().second;
            if(board[y][x] == 0){
                tmp = times;
            }
            active.pop();
            for(int dir = 0; dir < 4; dir++){
                int ny = y + dy[dir];
                int nx = x + dx[dir];
                if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                    continue;
                }
                if(!visited[ny][nx] && board[ny][nx] != 1){
                    visited[ny][nx] = 1;
                    active.push(make_pair(make_pair(ny, nx), times+1));
                }
            }
        }
        if(virusCheck()){
            if(ans == -1 || (ans != -1 && tmp < ans)){
                ans = tmp;
            }
        }

    }
    else{
        for(int i = idx; i < info.size(); i++){
            if(check[i] == 0){
                check[i] = 1;
                dfs(i+1, cnt+1);
                check[i] = 0;
            }
        }
    }
}

void simulation(){
    dfs(0, 0);
}

int main(){
    userInput();
    simulation();
    cout << ans;
    return 0;
}