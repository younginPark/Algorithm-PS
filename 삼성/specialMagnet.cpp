#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

/*
입력을 쭉 받는다.
입력 받은 자석의 방향에 따라 추후 회전시킬 자석의 순서를 먼저 정한다. 
1번의 자석을 회전하면 2, 3, 4 순으로 해주고
2번의 자석을 회전하면 1, 3, 4 순으로 해주고
3번의 자석을 회전하면 2, 4, 1 순으로 해주고
4번의 자석을 회전하면 3, 2, 1 순으로 해준다.

톱니의 순서는 입력 받은 것을 12시 방향부터 시계 방향 순으로 크기가 8인 배열에 넣어준다.
이때 1과 4는 비교할 위치가 고정이고, 2와 3 자석은 회전 순서에 따라 달라진다.
모듈화 하고 싶으면 저 위에 순서를 배열에 넣고 해당 순서대로 자석 돌리면 될거고 
비교할 위치는 나보다 큰 숫자인지 작은 숫자인지 확인해서 큰 숫자면 오른쪽 톱니, 작은 숫자면 왼쪽 톱니 비교 해준다고 하면 될듯

돌릴거 다 돌리고 0번째 위치의 N,S 에 따라 점수 합산

시계방향 1, 반시계방향 -1
N:0, S:1
*/

int K;
int magnet[5][9];
int tmp_magnet[5][9];
int order[4][4] = { {0, 1, 2, 3}, {1, 0, 2, 3}, {2, 1, 3, 0}, {3, 2, 1, 0} };
int cur_dir[4];
vector<pair<int, int> > command;
int ans = 0;

void init(){
    memset(magnet, 0, sizeof(magnet));
    memset(cur_dir, 0, sizeof(cur_dir));
    command.clear();
    ans = 0;
}

void userInput(){
    cin >> K;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 8; j++){
            cin >> magnet[i][j];
        }
    }
    for(int i = 0; i < K; i++){
        int tmp1, tmp2;
        cin >> tmp1 >> tmp2;
        tmp1--;
        command.push_back(make_pair(tmp1, tmp2));
    }
}

void clockWise(int mag){
    cur_dir[mag] = 1;
    for(int i = 0; i < 7; i++){
        tmp_magnet[mag][i+1] = magnet[mag][i];
    }
    tmp_magnet[mag][0] = magnet[mag][7];
}

void counterClockWise(int mag){
    cur_dir[mag] = -1;
    for(int i = 7; i > 0; i--){
        tmp_magnet[mag][i-1] = magnet[mag][i];
    }
    tmp_magnet[mag][7] = magnet[mag][0];
}

void rotateMagnet(int cur_mag, int before_mag){
    if(cur_mag == 0){
        if(magnet[0][2] != magnet[1][6]){
            if(cur_dir[1] == 1){
                counterClockWise(0);
            }
            else if(cur_dir[1] == -1){
                clockWise(0);
            }
        }
    }
    else if(cur_mag == 1){
        if(before_mag < cur_mag){
            if(magnet[1][6] != magnet[0][2]){
                if(cur_dir[0] == 1){
                    counterClockWise(1);
                }
                else if(cur_dir[0] == -1){
                    clockWise(1);
                }
            }
        }
        else{
            if(magnet[1][2] != magnet[2][6]){
                if(cur_dir[2] == 1){
                    counterClockWise(1);
                }
                else if(cur_dir[2] == -1){
                    clockWise(1);
                }
            }
        }
    }
    else if(cur_mag == 2){
        if(before_mag < cur_mag){
            if(magnet[2][6] != magnet[1][2]){
                if(cur_dir[1] == 1){
                    counterClockWise(2);
                }
                else if(cur_dir[1] == -1){
                    clockWise(2);
                }
            }
        }
        else{
            if(magnet[2][2] != magnet[3][6]){
                if(cur_dir[3] == 1){
                    counterClockWise(2);
                }
                else if(cur_dir[3] == -1){
                    clockWise(2);
                }
            }
        }
    }
    else if(cur_mag == 3){
        if(magnet[2][2] != magnet[3][6]){
            if(cur_dir[2] == 1){
                counterClockWise(3);
            }
            else if(cur_dir[2] == -1){
                clockWise(3);
            }
        }
    }
}

void copyMagnet(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 8; j++){
            magnet[i][j] = tmp_magnet[i][j];
        }
    }
}

void printMagnet(){
    cout << "------------\n";
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 8; j++){
            cout << magnet[i][j] << " ";
        }
        cout << "\n";
    }
}

void solution(){
    for(int loop = 0; loop < K; loop++){
        memset(tmp_magnet, 0, sizeof(tmp_magnet));
        memset(cur_dir, 0, sizeof(cur_dir));
        int mag_num = command[loop].first;
        int dir_num = command[loop].second;
        cur_dir[mag_num] = dir_num;
        if(dir_num == 1){
            clockWise(mag_num);
        }
        else{
            counterClockWise(mag_num);
        }
        for(int i = 1; i < 4; i++){
            rotateMagnet(order[mag_num][i], order[mag_num][i-1]);
        }
        for(int i = 0; i < 4; i++){
            if(cur_dir[i] == 0){
                //cout << i << ": ";
                for(int j = 0; j < 8; j++){
                    //cout << magnet[i][j] << " "; 
                    tmp_magnet[i][j] = magnet[i][j];
                }
                //cout << "\n";
            }
        }
        //cout << "\n";
        copyMagnet();
        //printMagnet();
    }
    ans = (magnet[0][0] * 1) + (magnet[1][0] * 2) + (magnet[2][0] * 4) + (magnet[3][0] * 8);
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