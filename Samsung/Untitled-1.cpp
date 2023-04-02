#include <iostream>
#include <queue>
using namespace std;

int dy[4] = { -1, 0, +1, 0 };
int dx[4] = { 0, -1, 0, +1 };

int visited[20][20];

bool checkVisited(){
    cout << "------------\n";
    int total = 0;
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            cout << visited[i][j] << " ";
            if(visited[i][j] == 1){
                total++;
            }
        }
        cout << "\n";
    }
    if(total == 400){
        return true;
    }
    return false;
}

void bfs(int y, int x){
    queue<pair<pair<int, int>, int> > q;
    q.push(make_pair(make_pair(y, x), 1));
    visited[y][x] = 1;
    while(!q.empty()){
        int cy = q.front().first.first;
        int cx = q.front().first.second;
        int ck = q.front().second;
        q.pop();
        for(int dir = 0; dir < 4; dir++){
            int ny = cy + dy[dir];
            int nx = cx + dx[dir];
            if(ny < 0 || nx < 0 || ny >= 20 || nx >= 20 || visited[ny][nx] == 1){
                continue;
            }
            else{
                visited[ny][nx] = 1;
                q.push(make_pair(make_pair(ny, nx), ck+1));
            }
        }
        if(checkVisited() == true){
            cout << ck+1;
            return;
        }
    }
}

int main(){
    bfs(9, 9);
    return 0;
}