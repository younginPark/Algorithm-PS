#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
#define BOARD_MAX_SIZE 4001
using namespace std;

struct ATOM {
    int y, x, d, e, flag;
};

int N, total_energy;
int board[BOARD_MAX_SIZE][BOARD_MAX_SIZE]; // 원자가 몇개 있는지 확인
vector<ATOM> atom;

int dy[4] = { 0, 0, -1, +1 };
int dx[4] = { 1, -1, 0, 0 };

void init(){
    N = 0;
    total_energy = 0;
    atom.clear();
    memset(board, 0, sizeof(board));
}

void userInput(){
    cin >> N;
    for(int i = 0; i < N; i++){
        int y, x, d, e;
        cin >> y >> x >> d >> e;
        y = (y + 1000) * 2;
        x = (x + 1000) * 2;
        ATOM tmp;
        tmp.y = y, tmp.x = x, tmp.d = d, tmp.e = e, tmp.flag = 0;
        atom.push_back(tmp);
        board[y][x] = 1;
    }
}

bool allDieCheck(){
    for(int i = 0; i < atom.size(); i++){
        if(atom[i].flag == 0){
            return false;
        }
    }
    return true;
}

void moveAtom(){
    while(1){
        int tmp_energy = 0;
        if(allDieCheck() == true) break;

        for(int i = 0; i < atom.size(); i++){
            if(atom[i].flag == 1) continue;

            int y = atom[i].y;
            int x = atom[i].x;
            int d = atom[i].d;

            int ny = y + dy[d];
            int nx = x + dx[d];

            if(ny < 0 || nx < 0 || ny >= BOARD_MAX_SIZE || nx >= BOARD_MAX_SIZE){
                atom[i].flag = 1;
                board[y][x] = 0;
            }
            else{
                board[y][x] = 0;
                board[ny][nx] = board[ny][nx] + 1;
                atom[i].y = ny;
                atom[i].x = nx;
            }
        }

        for(int i = 0; i < atom.size(); i++){
            if(atom[i].flag == 1) continue;
            int y = atom[i].y;
            int x = atom[i].x;
            if(board[y][x] >= 2){
                for(int j = 0; j < atom.size(); j++){
                    if(i == j) continue;
                    if(atom[j].flag == 1) continue; // 이미 죽인거면 다시 에너지를 더할 필요없음

                    int y2 = atom[j].y;
                    int x2 = atom[j].x;
                    if(y == y2 && x == x2){
                        tmp_energy += atom[j].e;
                        atom[j].flag = 1;
                    }
                }
                // 자기랑 같은 위치에 있는 것 중에 아직 안죽은거 다 처리하고 이제 본인꺼 더해줌 (마지막에 해주네)
                tmp_energy += atom[i].e;
                atom[i].flag = 1;
                board[y][x] = 0; // 죽으면 처리해주니까 따로 초기화 해줄 필요가 없음
            }
        }
        total_energy += tmp_energy;
    }
}

void solution(){
    if(atom.size() <= 1){ // 이런 예외처리도 해줌
        total_energy = 0;
        return;
    }
    moveAtom();
}

void solve(){
    int tc;
    cin >> tc;
    for(int t = 0; t < tc; t++){
        init();
        userInput();
        solution();
        cout << "#" << t+1 << " " << total_energy << "\n";
    }
}

int main(){
    solve();
    return 0;
}