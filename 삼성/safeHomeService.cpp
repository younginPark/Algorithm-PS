#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

/*
K가 1일 때의 운영비용은 운영비용 식에서 구하고
방범 가능한 영역에 들어온 집들의 수는 K크기의 영역을 실제로 확인하면서 셈

입력 받을 때 총 집의 수를 구한 다음에 최대 지불 비용을 미리 계산해놓고
방범 영역의 크기가 커짐에 따라 운영비용이 최대 지불 비용보다 커지면 K는 그만 커지고 break
K는 최대 N까지 커질 수 있음

K의 영역을 어떻게 알 것인가?
K가 1이면 딱 한칸만 보고
K가 2이면 K는 1에서 4방향 확인
K가 3이면 K는 2인 것에서 4방향 확인
K가 4이면 K는 3인 것에서 4방향 확인

bfs로 하고 K를 따로 구분해주는게 아니라 K가 20이 넘거나 운영비용이 전체 집의 비용보다 커지면 break

visited를 둬서 이미 영역을 키운 칸은 확인하지 않음
K만큼 돌면서 4방향씩 키워나가면 됨
격자 벗어나면 무시

방범 영역을 두는 것은 (0, 0)부터 둠
단, 운영비용이 모든 집이 낼 수 있는 지불비용보다 크면 안되고 최대 N까지 커질 수 있음

그런데 이렇게 하면 문제인게
K의 크기에서 구해진 지불비용이 K의 운영비용보다 더 커지면 해당 K는 무효이고
그 값이 최대더라도 소용없는데

그냥 비효율적으로 한칸마다 1씩 키우면서 bfs돌림
*/

int dy[4] = { -1, 0, +1, 0 };
int dx[4] = { 0, -1, 0, +1 };

int N, M;
int board[21][21];
int visited[21][21];
int total_home_cost = 0;
int ans = 0;

void init(){
    total_home_cost = 0;
    ans = 0;
}  

void userInput(){
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> board[i][j];
            if(board[i][j] == 1){
                total_home_cost += M;
            }
        }
    }
}

void printVisitedAndHouseCnt(){
    cout << "------------\n";
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << visited[i][j] << " ";
        }
        cout << "\n";
    }
}

void checkArea(int y, int x){
    for(int k = 1; k <= N+1; k++){
        if((k*k + (k-1)*(k-1)) > total_home_cost){
            break;
        }
        memset(visited, 0, sizeof(visited));
        int tmp_cnt = 0;
        queue<pair<pair<int, int>, int> > q;
        q.push(make_pair(make_pair(y, x), 1));
        visited[y][x] = 1;
        if(board[y][x] == 1){
            tmp_cnt++;
        }
        while(!q.empty()){
            int cy = q.front().first.first;
            int cx = q.front().first.second;
            int ck = q.front().second;
            q.pop();
            if(ck == k){
                continue;
            }
            else{
                for(int dir = 0; dir < 4; dir++){
                    int ny = cy + dy[dir];
                    int nx = cx + dx[dir];
                    if(ny < 0 || nx < 0 || ny >= N || nx >= N || visited[ny][nx] == 1){
                        continue;
                    }
                    if(visited[ny][nx] == 0){
                        if(board[ny][nx] == 1){
                            tmp_cnt++;
                        }
                        visited[ny][nx] = 1;
                        q.push(make_pair(make_pair(ny, nx), ck+1));
                    }
                }
            }
        }
        int organaize_cost = (k * k) + ((k-1)*(k-1));
        //cout << k << ": " << organaize_cost << " " << tmp_cnt * M << "\n";
        if(organaize_cost <= (tmp_cnt * M)){
            ans = max(ans, tmp_cnt);
        }
    }
}

void solution(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            // cout << "--------------\n";
            // cout << i << ", " << j << ": \n";
            checkArea(i, j);
            //printVisitedAndHouseCnt();
        }
    }
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