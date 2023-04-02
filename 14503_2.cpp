#include <iostream>
#include <queue>
using namespace std;

int dy[4] = { -1, 0, 1, 0}; //북동남서
int dx[4] = { 0, 1, 0, -1};
int N, M;
int arr[51][51];
int answer;

struct ROBOT{
    int y, x, dir;
};

queue<ROBOT> q;

int main(){
    ROBOT robot;
    cin >> N >> M;
    cin >> robot.y >> robot.x >> robot.dir;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> arr[i][j];
        }
    }
    q.push(robot);
    while(!q.empty()){
        ROBOT cur = q.front();
        q.pop();
        if(arr[cur.y][cur.x] == 0){
            arr[cur.y][cur.x] = 2;
            answer++;
        }
        for(int i = 0; i < 4; i++){
            ROBOT next;
            //next라는 변수 만들어서 일단 왼쪽 방향으로 옮겨서 상황 판단 후 청소 할 수 있으면 q에 push
            next.dir = (cur.dir + 3 + i*3) % 4;
            next.y = cur.y + dy[next.dir];
            next.x = cur.x + dx[next.dir];

            if(next.y < 0 || next.y > N || next.x < 0 || next.x > M || arr[next.y][next.x] != 0){
                continue;
            }
            q.push(next);
            break;
        }
        if(q.empty()){
            ROBOT next;
            //일단 후진함
            next.dir = cur.dir;
            next.y = cur.y + dy[(cur.dir+2) % 4];
            next.x = cur.x + dx[(cur.dir+2) % 4];
            //후진했을 때 벽이면 스탑
            if(arr[next.y][next.x] == 1){
                break;
            }
            q.push(next);
        }
    }
    
    printf("%d\n", answer);
    return 0;
}