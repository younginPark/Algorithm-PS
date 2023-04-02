#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int N, M, C;
int board[11][11];
int visited[11][11];
int visited_calc[11];
int ans = 0;
int max_a = 0, max_b = 0;
vector<int> v1;
vector<int> v2;

void init(){
    v1.clear();
    v2.clear();
    memset(visited, 0, sizeof(visited));
    ans = 0;
    max_a = 0, max_b = 0;
}

void userInput(){
    cin >> N >> M >> C;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> board[i][j];
        }
    }
}

void dfs(int idx){
    int tmp_total = 0;
    for(int i = 0; i < v1.size(); i++){
        if(visited_calc[i] == 1){
            tmp_total += v1[i];
        }
    }
    if(tmp_total <= C){
        tmp_total = 0;
        //cout << "v1: ";
        for(int i = 0; i < v1.size(); i++){
            if(visited_calc[i] == 1){
                //cout << v1[i] << " ";
                tmp_total += v1[i] * v1[i];
            }
        }
        //cout << "\n";
        max_a = max(max_a, tmp_total);
    }
    for(int i = idx; i < v1.size(); i++){
        if(visited_calc[i] == 0){
            visited_calc[i] = 1;
            dfs(i+1);
            visited_calc[i] = 0;
        }
    }
}

void dfs2(int idx){
    int tmp_total = 0;
    for(int i = 0; i < v2.size(); i++){
        if(visited_calc[i] == 1){
            tmp_total += v2[i];
        }
    }
    if(tmp_total <= C){
        tmp_total = 0;
        //cout << "v2: ";
        for(int i = 0; i < v2.size(); i++){
            if(visited_calc[i] == 1){
                //cout << v2[i] << " ";
                tmp_total += v2[i] * v2[i];
            }
        }
        //cout << "\n";
        max_b = max(max_b, tmp_total);
    }
    for(int i = idx; i < v2.size(); i++){
        if(visited_calc[i] == 0){
            visited_calc[i] = 1;
            dfs2(i+1);
            visited_calc[i] = 0;
        }
    }
}

void calcHoney(){
    memset(visited_calc, 0, sizeof(visited_calc));
    for(int i = 0; i < v1.size(); i++){
        if(visited_calc[i] == 0){
            visited_calc[i] = 1;
            dfs(i+1);
            visited_calc[i] = 0;
        }
    }
    memset(visited_calc, 0, sizeof(visited_calc));
    for(int i = 0; i < v2.size(); i++){
        if(visited_calc[i] == 0){
            visited_calc[i] = 1;
            dfs2(i+1);
            visited_calc[i] = 0;
        }
    }
    //cout << "total: " << max_a + max_b << "\n";
    ans = max(ans, max_a + max_b);
    max_a = 0, max_b = 0;
}

void getHoneyB(int y, int x){
    for(int i = 0; i < M; i++){
        int nx = x + i;
        if(visited[y][nx] == 1){
            return;
        }
        v2.push_back(board[y][nx]);
    }
    calcHoney();
}

void visitB(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(j + M - 1 >= N || visited[i][j] == 1){
                continue;
            }
            else{
                getHoneyB(i, j);
                v2.clear();
            }
        }
    }
}

void printVisited(){
    cout << "---------\n";
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << visited[i][j] << " ";
        }
        cout << "\n";
    }
}

void getHoneyA(int y, int x){
    for(int i = 0; i < M; i++){
        int nx = x + i;
        visited[y][nx] = 1;
        v1.push_back(board[y][nx]);
    }
    //printVisited();
    visitB();
    for(int i = 0; i < M; i++){
        int nx = x + i;
        visited[y][nx] = 0;
    }
}

void visitA(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            //memset(visited, 0, sizeof(visited));
            if(j + M - 1 >= N){
                continue;
            }
            else{
                getHoneyA(i, j);
                v1.clear();
            }
        }
    }
}

void solution(){
    visitA();
}

int main(){
    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++){
        init();
        userInput();
        solution();
        cout << "#" << tc << " " << ans << "\n";
    }
    return 0;
}