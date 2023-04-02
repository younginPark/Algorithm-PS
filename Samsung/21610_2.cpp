#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int dy[8] = { 0, -1, -1, -1, 0, +1, +1, +1 };
int dx[8] = { -1, -1, 0, +1, +1, +1, 0, -1 };

int N, M;
int rain[105][105];
int cloud[105][105];
vector<pair<int, int> > command;

void userInput(){
    memset(rain, 0, sizeof(rain));
    memset(cloud, 0, sizeof(cloud));
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> rain[i][j];
        }
    }
    for(int i = 0; i < M; i++){
        int d, s;
        cin >> d >> s;
        d--;
        command.push_back(make_pair(d, s));
    }
    cloud[N-1][0] = 1;
    cloud[N-1][1] = 1;
    cloud[N-2][0] = 1;
    cloud[N-2][1] = 1;
}

void printBoard(){
    cout << "----------------\n";
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << rain[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << cloud[i][j] << " ";
        }
        cout << "\n";
    }
}

void moveCloud(int order){
    int d = command[order].first;
    int s = command[order].second;
    int new_cloud[105][105];
    memset(new_cloud, 0, sizeof(new_cloud));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(cloud[i][j] == 1){
                int ny = (i + (dy[d] * s) + 55 * N) % N;
                int nx = (j + (dx[d] * s) + 55 * N) % N;
                new_cloud[ny][nx] = 1;
            }
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cloud[i][j] = new_cloud[i][j];
        }
    }
}

void addRain(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(cloud[i][j] == 1){
                rain[i][j] += 1;
            }
        }
    }
}

void copyRain(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(cloud[i][j] == 1){
                int cnt = 0;
                for(int dir = 1; dir < 8; dir += 2){
                    int ny = i + dy[dir];
                    int nx = j + dx[dir];
                    if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                        continue;
                    }
                    if(rain[ny][nx] > 0){
                        cnt++;
                    }
                }
                rain[i][j] += cnt;
            }
        }
    }
}

void makeCloudAndDecreaseRain(){
    int new_cloud[105][105];
    memset(new_cloud, 0, sizeof(new_cloud));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(cloud[i][j] != 1 && rain[i][j] >= 2){
                new_cloud[i][j] = 1;
                rain[i][j] -= 2;
            }
        }
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cloud[i][j] = new_cloud[i][j];
        }
    }
}

void getTotalRain(){
    int total = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            total += rain[i][j];
        }
    }
    cout << total;
}

void solution(){
    for(int loop = 0; loop < M; loop++){
        moveCloud(loop);
        addRain();
        copyRain();
        makeCloudAndDecreaseRain();
    }
    getTotalRain();
}

int main(){
    userInput();
    solution();
    return 0;
}