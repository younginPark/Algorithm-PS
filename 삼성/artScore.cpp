#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

int dy[4] = { -1, 0, +1, 0 };
int dx[4] = { 0, -1, 0, +1 };

int N;
int board[30][30];
int visited[30][30];
int visited2[30][30];

struct GROUP {
    int y, x;
    int color;
    int total_cnt;
    int touch[900];
};

vector<GROUP> group;

void userInput(){
    cin >> N;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> board[i][j];
        }
    }
}

void bfs(int y, int x, int idx){
    GROUP myGroup;
    myGroup.y = y; myGroup.x = x;
    myGroup.color = board[y][x];
    int color = board[y][x];
    queue<pair<int, int> > q;
    q.push(make_pair(y, x));
    visited[y][x] = idx;
    int total_cnt = 1;
    while(!q.empty()){
        int cy = q.front().first;
        int cx = q.front().second;
        q.pop();
        for(int dir = 0; dir < 4; dir++){
            int ny = cy + dy[dir];
            int nx = cx + dx[dir];
            if(ny < 0 || nx < 0 || ny >= N || nx >= N || visited[ny][nx] > -1){
                continue;
            }
            if(board[ny][nx] != color){
                continue;
            }
            if(board[ny][nx] == color){
                total_cnt++;
                q.push(make_pair(ny, nx));
                visited[ny][nx] = idx;
            }
        }
    }
    myGroup.total_cnt = total_cnt;
    group.push_back(myGroup);
}

void touchBfs(int y, int x, int idx){
    // memset(group[idx].touch, 0, sizeof(group[idx].touch));
    memset(visited2, -1, sizeof(visited2));
    for(int i = 0; i < 900; i++){
        group[idx].touch[i] = 0;
    }
    queue<pair<int, int> > q;
    q.push(make_pair(y, x));
    visited2[y][x] = idx;
    while(!q.empty()){
        int cy = q.front().first;
        int cx = q.front().second;
        q.pop();
        for(int dir = 0; dir < 4; dir++){
            int ny = cy + dy[dir];
            int nx = cx + dx[dir];
            if(ny < 0 || nx < 0 || ny >= N || nx >= N || visited2[ny][nx] > -1){
                continue;
            }
            if(board[ny][nx] != group[idx].color){
                group[idx].touch[visited[ny][nx]]++;
                continue;
            }
            if(board[ny][nx] == group[idx].color){
                q.push(make_pair(ny, nx));
                visited2[ny][nx] = idx;
            }
        }
    }
}

// 그룹 별로 자신의 칸의 수, 다른 숫자들과 맞닿는 변의 수 구하기
void findGroup(){
    memset(visited, -1, sizeof(visited));
    int idx = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(visited[i][j] == -1){
                bfs(i, j, idx);
                idx++;
            }
        }
    }
    for(int i = 0; i < group.size(); i++){
        touchBfs(group[i].y, group[i].x, i);
    }
}

// 각 그룹들을 한쌍씩 묶어서 초기 예술 점수 구함 
int getArtScore(){
    int total = 0;
    for(int i = 0; i < group.size()-1; i++){
        for(int j = i+1; j < group.size(); j++){
            if(group[i].touch[j] == 0) continue;
            int score = (group[i].total_cnt + group[j].total_cnt) * group[i].color * group[j].color * group[i].touch[j];
            total += score;
            // cout << group[i].total_cnt << " " << group[j].total_cnt << " " << group[i].color << " " << group[j].color << " " << group[i].touch[j] << "\n";
            // cout << i << ", " << j << ": " << score << "\n";
        }
    }
    return total;
}

// 십자로 나눠서 십자 부분은 반시계 방향 90도 회전, 그 이외의 부분은 시계 방향 90도 회전
void rotation(){
    int new_board[30][30];
    int copy_board[30][30];
    int copy_board2[30][30];
    memset(new_board, 0, sizeof(new_board));
    // 십자 부분
    new_board[N/2][N/2] = board[N/2][N/2];
    for(int i = 0; i < N/2; i++){
        new_board[N/2][i] = board[i][N/2];
    }
    for(int i = 0, j = N-1; i < N/2 && j >= (N/2)+1; i++, j--){
        new_board[j][N/2] = board[N/2][i];
    }
    for(int i = (N/2)+1; i < N; i++){
        new_board[N/2][i] = board[i][N/2];
    }
    for(int i = 0, j = N-1; i < N/2 && j >= (N/2)+1; i++, j--){
        new_board[i][N/2] = board[N/2][j];
    }

    // 십자 이외 부분
    // 왼쪽 위
    for(int i = 0, i2 = 0; i < N/2; i++, i2++){
        for(int j = 0, j2 = 0; j < N/2; j++, j2++){
            // new_board[N/2-1-j][i] = board[i][j];
            copy_board[i2][j2] = board[i][j];
        }
    }
    for(int i = 0; i < N/2; i++){
        for(int j = 0; j < N/2; j++){
            copy_board2[i][j] = copy_board[N/2-1-j][i];
        }
    }
    for(int i = 0, i2 = 0; i < N/2; i++, i2++){
        for(int j = 0, j2 = 0; j < N/2; j++, j2++){
            new_board[i][j] = copy_board2[i2][j2];
        }
    }
    // 오른쪽 위
    for(int i = 0, i2 = 0; i < N/2; i++, i2++){
        for(int j = N/2+1, j2 = 0; j < N; j++, j2++){
            copy_board[i2][j2] = board[i][j];
        }
    }
    for(int i = 0; i < N/2; i++){
        for(int j = 0; j < N/2; j++){
            copy_board2[i][j] = copy_board[N/2-1-j][i];
        }
    }
    for(int i = 0, i2 = 0; i < N/2; i++, i2++){
        for(int j = N/2+1, j2 = 0; j < N; j++, j2++){
            new_board[i][j] = copy_board2[i2][j2];
        }
    }
    // 왼쪽 아래
    for(int i = N/2+1, i2 = 0; i < N; i++, i2++){
        for(int j = 0, j2 = 0; j < N/2; j++, j2++){
            copy_board[i2][j2] = board[i][j];
        }
    }
    for(int i = 0; i < N/2; i++){
        for(int j = 0; j < N/2; j++){
            copy_board2[i][j] = copy_board[N/2-1-j][i];
        }
    }
    for(int i = N/2+1, i2 = 0; i < N; i++, i2++){
        for(int j = 0, j2 = 0; j < N/2; j++, j2++){
            new_board[i][j] = copy_board2[i2][j2];
        }
    }
    // 오른쪽 아래
    for(int i = N/2+1, i2 = 0; i < N; i++, i2++){
        for(int j = N/2+1, j2 = 0; j < N; j++, j2++){
            copy_board[i2][j2] = board[i][j];
        }
    }
    for(int i = 0; i < N/2; i++){
        for(int j = 0; j < N/2; j++){
            copy_board2[i][j] = copy_board[N/2-1-j][i];
        }
    }
    for(int i = N/2+1, i2 = 0; i < N; i++, i2++){
        for(int j = N/2+1, j2 = 0; j < N; j++, j2++){
            new_board[i][j] = copy_board2[i2][j2];
        }
    }

    // 최종 복사
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            board[i][j] = new_board[i][j];
        }
    }
}

void printBoard(){
    // 최종 복사
    cout << "----------------------\n";
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

void printVisited(){
    // 최종 복사
    cout << "visited----------------------\n";
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << visited[i][j] << " ";
        }
        cout << "\n";
    }
}


void solution(){
    int total = 0;
    for(int i = 0; i < 4; i++){
        group.clear();
        findGroup();
        total += getArtScore();
        if(i == 3) break;
        rotation();
    }
    cout << total;
}

int main(){
    userInput();
    solution();
    return 0;
}