#include <iostream>
#include <queue>
using namespace std;
int yy[4] = {-1,0,1,0}; //북동남서
int xx[4] = {0,1,0,-1};

struct ROBOT{
    int x;
    int y;
    int dir;
};

int main(){

    int arr[51][51] = { 0, };
    ROBOT robot;
    int r = 0, c = 0;
    int cnt = 0;

    cin >> r >> c;
    cin  >> robot.y >> robot.x >> robot.dir;

    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            cin >> arr[i][j];
        }
    }

    queue<ROBOT> q;
    q.push(robot);

    while(!q.empty()){
        ROBOT cur = q.front();
        q.pop();
        if(arr[cur.y][cur.x] == 0){
            arr[cur.y][cur.x] = 2; //청소는 2로 표시
            cnt++;
        }

        for(int dir = 0; dir < 4; dir++){
            ROBOT next;
            next.dir = (cur.dir + 3 + (dir * 3)) % 4; //왼쪽 방향 계산
            next.y = cur.y+ yy[next.dir]; //계산한 방향으로 y 이동
            next.x = cur.x + xx[next.dir]; //계산한 방향으로 x 이동

			//범위를 벗어나거나 청소할 곳이 없다면 for문 continue
            if(next.y < 0 || next.y >= r || next.x < 0 || next.x >= c || arr[next.y][next.x] != 0){
                continue;
            }
			//그렇지 않다면 q에 넣어주기 (큐에는 청소기 한대 밖에 안들어감!!)
            q.push(next);
            break;
        }

		//위에서 계속 continue로 for문 다 돌아서 push 된 것이 없는 경우
        if(q.empty()){
            ROBOT next;
            next.dir = cur.dir;
            next.y = cur.y+ yy[(next.dir+2) % 4]; //후진
            next.x = cur.x + xx[(next.dir+2) % 4]; //후진

            if(arr[next.y][next.x] == 1){ //후진 했을 때 벽이면 while문 종료
                break;
            }
			//벽이 아니라면 다시 q에 넣고 왼쪽 보고 청소하는거 시작하러 
            q.push(next);
        }
    }

    cout << cnt;

    return 0;
}
