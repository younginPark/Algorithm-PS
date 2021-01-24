#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

int N, L, R;
int arr[51][51];
bool visit[51][51];
int dx[4] = { 0, -1, 1, 0};
int dy[4] = { -1, 0, 0, 1};
int cnt;
queue<pair<int, int> > q;
bool chk = false;

void bfs(){
    int total = 0;
    int cnt_country = 0;
    queue<pair<int, int> > uni;
    while(!q.empty()){
        int frontY = q.front().first;
        int frontX = q.front().second;
        total += arr[frontY][frontX];
        uni.push(make_pair(frontY, frontX));
        cnt_country++;
        q.pop();
        for(int i = 0; i < 4; i++){
            int newY = frontY + dy[i];
            int newX = frontX + dx[i];
            if(visit[newY][newX] == false && 0 <= newY && newY < N && 0 <= newX && newX < N){
                int interval = abs(arr[newY][newX] - arr[frontY][frontX]);
                if(L <= interval && interval <= R){
                    q.push(make_pair(newY, newX));
                    visit[newY][newX] = true;
                }
            }
        }
    }
    if(cnt_country > 1){
        chk = true;
        int num = total / cnt_country;
        while(!uni.empty()){
            // printf("%d, %d\n", uni.front().first, uni.front().second);
            arr[uni.front().first][uni.front().second] = num;
            uni.pop();
        }
    }
    else{
        uni.pop();
    }
}

int main(){
    cin >> N >> L >> R;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> arr[i][j];
        }
    }
    while(cnt <= 2000){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(visit[i][j] == false){
                    q.push(make_pair(i, j));
                    visit[i][j] = true;
                    bfs();
                }
            }
        }
        // for(int i = 0; i < N; i++){
        //     for(int j = 0; j < N; j++){
        //         printf("%d ", arr[i][j]);
        //     }
        //     printf("\n");
        // }
        if(chk == true){
            chk = false;
            cnt++;
        }
        else{
            break;
        }
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                visit[i][j] = false;
            }
        }
    }
    printf("%d\n", cnt);
    return 0;
}