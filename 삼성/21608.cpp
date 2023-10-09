#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
using namespace std;

int dy[4] = { +1, -1, 0, 0 };
int dx[4] = { 0, 0, +1, -1 };

int N;
int student_num;
vector<pair<int ,int> > student_pos(400, make_pair(-5, -5));
vector<int> favorite[400];
vector<int> sit_order;
int board[21][21];
int ans = 0;

void sitdown(){
    for(int order = 0; order < student_num; order++){
        int student = sit_order[order];
        // 인접한 지 체크
        vector<pair<int, int> > candi;
        int candi_num = 0;
        for(int y = 0; y < N; y++){
            for(int x = 0; x < N; x++){
                if(board[y][x] == -1){
                    // 좋아하는 학생과 각 인접한 정도 체크
                    int fav_num = 0;
                    for(int i = 0; i < 4; i++){
                        int fav = favorite[student][i];
                        int fav_y = student_pos[fav].first;
                        int fav_x = student_pos[fav].second;
                        if((abs(y-fav_y) + abs(x-fav_x)) == 1){
                            fav_num++;
                        }
                        if(i == 3 && fav_num > candi_num){
                            candi_num = fav_num;
                            candi.clear();
                            candi.push_back(make_pair(y, x));
                        }
                        else if(i == 3 && fav_num == candi_num){
                            candi.push_back(make_pair(y, x));
                        }
                    }
                }
            }
        }
        if(candi.size() > 1){ // 1을 만족하는게 여러 개면, 비어있는 칸들 중에서 그 칸의 인접한 칸 중에 비어있는게 가장 많은 곳에 자리 정함
            vector<pair<int, int> > empty;
            int empty_num = 0;
            for(int i = 0; i < candi.size(); i++){
                int y = candi[i].first; int x = candi[i].second;
                int tmp_empty_num = 0;
                for(int dir = 0; dir < 4; dir++){
                    int ny = y + dy[dir];
                    int nx = x + dx[dir];
                    if(ny >= 0 && ny < N && nx >= 0 && nx < N && board[ny][nx] == -1){
                        tmp_empty_num++;
                    }
                    if(dir == 3 && tmp_empty_num > empty_num){
                        empty_num = tmp_empty_num;
                        empty.clear();
                        empty.push_back(make_pair(y, x));
                    }
                    if(dir == 3 && tmp_empty_num == empty_num){
                        empty.push_back(make_pair(y, x));
                    }
                }
            }
            student_pos[student].first = empty[0].first;
            student_pos[student].second = empty[0].second;
        }
        else{
            student_pos[student].first = candi[0].first;
            student_pos[student].second = candi[0].second;
        }

        board[student_pos[student].first][student_pos[student].second] = student;
    }
}

void checkSatisfication(){
    for(int student = 0; student < student_num; student++){
        int y = student_pos[student].first;
        int x = student_pos[student].second;
        int fav_num = 0;
        for(int i = 0; i < 4; i++){
            int fav = favorite[student][i];
            int fav_y = student_pos[fav].first;
            int fav_x = student_pos[fav].second;
            if((abs(y-fav_y) + abs(x-fav_x)) == 1){
                fav_num++;
            }
        }
        if(fav_num == 1) ans += 1;
        else if(fav_num == 2) ans += 10;
        else if(fav_num == 3) ans += 100;
        else if(fav_num == 4) ans += 1000;
    }
}

int main() {
    cin >> N;
    student_num = pow(N, 2);
    for(int i = 0; i < student_num; i++){
        int t1, t2, t3, t4, t5;
        cin >> t1 >> t2 >> t3 >> t4 >> t5;
        sit_order.push_back(t1-1);
        favorite[t1-1].push_back(t2-1);
        favorite[t1-1].push_back(t3-1);
        favorite[t1-1].push_back(t4-1);
        favorite[t1-1].push_back(t5-1);
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            board[i][j] = -1;
        }
    }
    sitdown();
    checkSatisfication();
    cout << ans;
    return 0;
}