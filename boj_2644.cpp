#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int n, m, want1, want2;
int answer = 987654321;
bool relation[101][101] = { false, };
bool visit[101] = { false, };
queue<pair<int, int> > q;

void bfs(){
    while(!q.empty()){
        int frontX = q.front().first;
        int cnt = q.front().second;
        visit[frontX] = true;
        q.pop();
        if(frontX == want2){
            answer = min(answer, cnt);
            break;
        }
        for(int i = 1; i <= 100; i++){
            if(relation[frontX][i] == true && visit[i] == false){
                q.push(make_pair(i, cnt+1));
            }
        }
    }
}

int main(){

    cin >> n;
    cin >> want1 >> want2;
    cin >> m;
    for(int i = 0; i < m; i++){
        int tmp1, tmp2;
        cin >> tmp1 >> tmp2;
        relation[tmp1][tmp2] = true;
        relation[tmp2][tmp1] = true;
    }
    q.push(make_pair(want1, 0));
    bfs();

    if(answer == 987654321){
        answer = -1;
    }
    printf("%d", answer);
    return 0;
}