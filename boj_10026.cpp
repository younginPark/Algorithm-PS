#include <iostream>
#include <string>
#include <queue>
using namespace std;

int N, ans1, ans2;
int arr[101][101];
int arr2[101][101];
int dx[4] = { 0, -1, 1, 0};
int dy[4] = { -1, 0, 0, 1};

void bfs(int x, int y, char color, int yes) {
    queue <pair<int, int> > q;
    q.push(make_pair(x, y));

    while(!q.empty()){
        int frontx = q.front().first;
        int fronty = q.front().second;
        q.pop();

        for(int i = 0; i < 4; i++){
            if(0 <= frontx+dx[i] && frontx+dx[i] < N && 0 <= fronty+dy[i] && fronty+dy[i] < N) {
                if(yes == 1){
                    if(color == 'R' || color == 'G'){
                        if(arr[frontx+dx[i]][fronty+dy[i]] == 'R' || arr[frontx+dx[i]][fronty+dy[i]] == 'G'){
                            arr[frontx+dx[i]][fronty+dy[i]] = 0;
                            q.push(make_pair(frontx+dx[i], fronty+dy[i]));
                        }
                    }
                    else {
                        if(arr[frontx+dx[i]][fronty+dy[i]] == 'B'){
                            arr[frontx+dx[i]][fronty+dy[i]] = 0;
                            q.push(make_pair(frontx+dx[i], fronty+dy[i]));
                        }
                    }
                }
                else if(yes == 0){
                    if(color == 'R' && arr2[frontx+dx[i]][fronty+dy[i]] == 'R'){
                        arr2[frontx+dx[i]][fronty+dy[i]] = 0;
                        q.push(make_pair(frontx+dx[i], fronty+dy[i]));
                    }
                    else if(color == 'G' && arr2[frontx+dx[i]][fronty+dy[i]] == 'G'){
                        arr2[frontx+dx[i]][fronty+dy[i]] = 0;
                        q.push(make_pair(frontx+dx[i], fronty+dy[i]));
                    }
                    else if(color == 'B' && arr2[frontx+dx[i]][fronty+dy[i]] == 'B'){
                        arr2[frontx+dx[i]][fronty+dy[i]] = 0;
                        q.push(make_pair(frontx+dx[i], fronty+dy[i]));
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        string tmp1;
        cin >> tmp1;
        for(int j = 0; j < N; j++){
            arr[i][j] = tmp1[j];
            arr2[i][j] = tmp1[j];
        }
    }
    // 적록색약 일 때
    for(int i = 0; i < N; i ++){
        for(int j = 0; j < N; j++){
            if (arr[i][j] != 0) {
                bfs(i, j, arr[i][j], 1);
                ans1++;
            }
        }
    }

    // 적록색약 아닐 때
    for(int i = 0; i < N; i ++){
        for(int j = 0; j < N; j++){
            if (arr2[i][j] != 0) {
                bfs(i, j, arr2[i][j], 0);
                ans2++;
            }
        }
    }
    printf("%d %d\n", ans2, ans1);
    return 0;
}