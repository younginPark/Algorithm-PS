#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int dy[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int N, M;
int board[51][51] = { 0, };
bool cloud[51][51] = { false, };
struct COMMAND {
    int dir;
    int space;
};
vector<COMMAND> command;
vector<pair<int, int> > cloud_info;

void userInput(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> board[i][j];
        }
    }
    for(int i = 0; i < M; i++){
        COMMAND tmp_command;
        cin >> tmp_command.dir >> tmp_command.space;
        tmp_command.dir--;
        command.push_back(tmp_command);
    }
}

void moveCloud(int dir, int space){
    // 구름 이동과 구름 있는 곳에 물바구니++;
    vector<pair<int, int> > new_cloud_info;
    memset(cloud, false, sizeof(cloud));
    for(int i = 0; i < cloud_info.size(); i++){
        int curY = cloud_info[i].first;
        int curX = cloud_info[i].second;
        int nextY = (curY + (dy[dir] * space)) % N;
        int nextX = (curX + (dx[dir] * space)) % N;
        if(nextY < 0){
            nextY += N;
        }
        if(nextX < 0){
            nextX += N;
        }
        cloud[nextY][nextX] = true;
        new_cloud_info.push_back(make_pair(nextY, nextX));
        board[nextY][nextX] += 1;
    }
    cloud_info = new_cloud_info;
}

void copyWaterBug(){
    for(int i = 0; i < cloud_info.size(); i++){
        int curY = cloud_info[i].first;
        int curX = cloud_info[i].second;
        int cnt = 0;
        for(int dir = 1; dir < 8; dir += 2){
            int nextY = curY + dy[dir];
            int nextX = curX + dx[dir];
            if(nextY < 0 || nextY >= N || nextX < 0 || nextX >= N){
                continue;
            }
            if(board[nextY][nextX] > 0){
                cnt++;
            }
        }
        board[curY][curX] += cnt;
    }
}

void makeCloud(){
    int new_cloud[51][51];
    memset(new_cloud, false, sizeof(new_cloud));
    cloud_info.clear();
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(board[i][j] >= 2 && cloud[i][j] == false){
                cloud_info.push_back(make_pair(i, j));
                board[i][j] -= 2;
                new_cloud[i][j] = true;
            }
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cloud[i][j] = new_cloud[i][j];
        }
    }
}

int result(){
    int ans = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            ans += board[i][j];
        }
    }
    return ans;
}

int main() {
    cin >> N >> M;
    userInput();
    cloud[N-1][0] = true;
    cloud[N-1][1] = true;
    cloud[N-2][0] = true;
    cloud[N-2][1] = true;
    cloud_info.push_back(make_pair(N-1, 0));
    cloud_info.push_back(make_pair(N-1, 1));
    cloud_info.push_back(make_pair(N-2, 0));
    cloud_info.push_back(make_pair(N-2, 1));
    for(int times = 0; times < M; times++){
        moveCloud(command[times].dir, command[times].space);
        copyWaterBug();
        makeCloud();
    }
    int ans = result();
    cout << ans;
    return 0;
}