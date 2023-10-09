#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
1. 격자에서 각각의 그룹을 찾음
2. 인접해 있는 그룹의 개수를 찾아둠
3. 인접해 있는 그룹의 개수를 찾아둔걸 통해 예술성 점수를 구해서 정답 변수에 더함
4. 십자가 부분 반시계 방향 회전
5. 십자 모양 제외한 4개의 정사각형을 각각 시계 방향으로 회전
*/

int dy[4] = { -1, 0, +1, 0 };
int dx[4] = { 0, -1, 0, +1 };

int visited[31][31];

int N;
int board[31][31];
int group_board[31][31];
int copy_board[31][31];
int ans = 0;

struct GROUP {
    int y, x;
    int num, cnt;
    int adjGroup[900];
};
vector<GROUP> group;

void init(){
    group.clear();
    memset(visited, 0, sizeof(visited));
    memset(group_board, 0, sizeof(group_board));
    memset(copy_board, 0, sizeof(copy_board));
}

void userInput(){
    cin >> N;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> board[i][j];
        }
    }
}

void findGroupBFS(int y, int x){
    int this_idx = group.size();
    int group_size = 1;
    queue<pair<int, int> > q;
    q.push(make_pair(y, x));
    visited[y][x] = 1;
    int standard_num = board[y][x];
    group_board[y][x] = this_idx;
    while(!q.empty()){
        int cy = q.front().first;
        int cx = q.front().second;
        q.pop();
        for(int dir = 0; dir < 4; dir++){
            int ny = cy + dy[dir];
            int nx = cx + dx[dir];
            if(ny < 0 || nx < 0 || ny >= N || nx >= N 
            || visited[ny][nx] == 1 || board[ny][nx] != standard_num){
                continue;
            }
            else{
                visited[ny][nx] = 1;
                group_board[ny][nx] = this_idx;
                group_size++;
                q.push(make_pair(ny, nx));
            }
        }
    }
    GROUP tmp;
    tmp.y = y, tmp.x = x, tmp.num = standard_num, tmp.cnt = group_size;
    memset(tmp.adjGroup, 0, sizeof(tmp.adjGroup));
    group.push_back(tmp);
}

void findGroup(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(visited[i][j] == 0){
                findGroupBFS(i, j);
            }
        }
    }
    // for(int i = 0; i < group.size(); i++){
    //     cout << group[i].cnt << " " << group[i].num << "\n";
    // }
}

void findAdjGroup(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            for(int dir = 0; dir < 4; dir++){
                int ny = i + dy[dir];
                int nx = j + dx[dir];
                if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                    continue;
                }
                else if(group_board[i][j] != group_board[ny][nx]){
                    group[group_board[i][j]].adjGroup[group_board[ny][nx]]++;
                }
            }
        }
    }
    int score = 0;
    for(int i = 0; i < group.size()-1; i++){
        for(int j = i+1; j < group.size(); j++){
            // cout << i << ", " << j << ": ";
            score += (group[i].cnt + group[j].cnt) * group[i].num * group[j].num * group[i].adjGroup[j];
            // cout << group[i].cnt << " " << group[j].cnt << " " << group[i].num << " " << group[j].num  << " " << group[i].adjGroup[j] << " => ";
            // cout << (group[i].cnt + group[j].cnt) * group[i].num * group[j].num * group[i].adjGroup[j] << "\n";
        }
    }
    ans += score;
    //cout << score << "\n";
}

void rollbackBoard(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            board[i][j] = copy_board[i][j];
        }
    }
}
/*
4등분으로 나누어서 하나씩 진행한다.
copy_board에 저장한다.
*/
void rotationCrossClockwise(){
    for(int i = 0; i < (N/2); i++){
        copy_board[N/2][i] = board[i][N/2];
    }
    for(int i = 0; i < (N/2); i++){
        copy_board[N-1-i][N/2] = board[N/2][i];
    }
    for(int i = 0; i < (N/2); i++){
        copy_board[N/2][N-1-i] = board[N-1-i][N/2];
    }
    for(int i = 0; i < (N/2); i++){
        copy_board[i][N/2] = board[N/2][N-1-i];
    }
    copy_board[N/2][N/2] = board[N/2][N/2];
    // for(int i = 0; i < N; i++){
    //     for(int j = 0; j < N; j++){
    //         cout << copy_board[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
}

void rotation(int y, int x){
    for(int i = 0; i < N/2; i++){
        for(int j = 0; j < N/2; j++){
            copy_board[y+j][x+(N/2)-1-i] = board[y+i][x+j];
        }
    }
}

void rotationBlockClock(){
    rotation(0, 0);
    rotation(0, N/2+1);
    rotation(N/2+1, 0);
    rotation(N/2+1, N/2+1);
    rollbackBoard();
}

int main(){
    userInput();
    for(int i = 0; i < 4; i++){
        findGroup();
        findAdjGroup();
        rotationCrossClockwise();
        rotationBlockClock();
        init();
    }
    cout << ans;
    return 0;
}