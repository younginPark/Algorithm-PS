#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstdlib>

using namespace std;

int arr[101][101];

int bfs(int n, int startNode){
    queue<int> q;
    bool visit[101] = {};
    int cnt = 1;
    
    visit[startNode] = true;
    q.push(startNode);
    
    while(!q.empty()){
        int front = q.front();
        q.pop();
        for(int i = 1; i <= n; i++){
            if(arr[front][i] > 0 && !visit[i]){
                visit[i] = true;
                q.push(i);
                cnt++;
            }
        }
    }

    int tmp = 0;
    for(int i = 1; i <= n; i++){
        if(visit[i]){
            tmp++;
        }
    }
    return cnt;
}

int solution(int n, vector<vector<int> > wires) {
    // 입력 받은 송전탑의 연결 여부를 기록 
    for(int i = 0; i < wires.size(); i++){
        arr[wires[i][0]][wires[i][1]] = 1;
        arr[wires[i][1]][wires[i][0]] = 1;
    }
    int answer = n;
    // arr 배열을 송전탑의 개수만큼 확인 
    // 만약 i, j 가 연결되었다면 해당 연결을 0으로 끊고 bfs를 각각 돌려줌
    // 각각의 bfs 값의 차를 구하고 최소값을 answer에 대입
    // 한번 끊었던 전선은 다시 연결할 때 2로 연결하여 한번 끊었던 전선인 것을 표시함 
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(arr[i][j] == 1 || arr[j][i] == 1){
                arr[i][j] = 0;
                arr[j][i] = 0;
                int first = bfs(n, i);
                int second = bfs(n, j);
                if(abs(first-second) < answer){
                    answer = abs(first-second);
                }
                arr[i][j] = 2;
                arr[j][i] = 2;
            }
        }
    }   
    
    return answer;
}