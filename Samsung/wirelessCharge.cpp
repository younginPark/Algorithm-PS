#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

/*
고민해야하는부분
- 같은 시간에 A, B 사람 모두 같은 충전 범위에 들어왔을 때 어떻게 해야하는지
    경우의 수를 나눔
    사용자 A, B가 접속 가능한 무선충전 공간에 들어갔을 때 A의 선택에 따라 B는 최선의 선택을 함
    A는 본인이 선택 가능한 모든 경우를 선택하기 때문에 B가 나중에 선택하더라도 모든 경우에 대해서 계산해 볼 수 있음
매초마다 무선충전기개수x2(A, B) 크기의 배열을 만들어서 A와 B가 충전할 수 있는 충전기를 표시 
이후 2중 for문 돌면서 A가 충전할 수 있는 것을 선택했을 때 안에 for문에서 B가 이 충전기를 선택하면 큰지 저 충전기를 선택하면 큰지
값을 더한 후에 비교해서 최대값으로 업데이트 이후 total 변수에 더해줌
*/

int dy[4] = { -1, 0, +1, 0 };
int dx[4] = { 0, +1, 0, -1 };

int M, A;
struct CHARGER{
    int y, x;
    int c, p;
};
struct PERSON{
    int y, x;
};
PERSON PA, PB;
vector<CHARGER> charger;
vector<int> P1;
vector<int> P2;
int check_arr[9][3];
int flagA = 0, flagB = 0;
int ans = 0;

void init(){
    charger.clear();
    P1.clear();
    P2.clear();
    flagA = 0, flagB = 0;
    ans = 0;
}

void userInput(){
    cin >> M >> A;
    for(int i = 0; i < M; i++){
        int tmp;
        cin >> tmp;
        tmp--;
        P1.push_back(tmp);
    }
    for(int i = 0; i < M; i++){
        int tmp;
        cin >> tmp;
        tmp--;
        P2.push_back(tmp);
    }
    for(int i = 0; i < A; i++){
        CHARGER tmp_charger;
        cin >> tmp_charger.x >> tmp_charger.y >> tmp_charger.c >> tmp_charger.p;
        tmp_charger.y--, tmp_charger.x--;
        charger.push_back(tmp_charger);
    }
}

void checkDist(){
    for(int i = 0; i < A; i++){
        if((abs(PA.y-charger[i].y) + abs(PA.x-charger[i].x)) <= charger[i].c){
            flagA = 1;
            check_arr[i][0] = 1;
        }
    }
    for(int i = 0; i < A; i++){
        if((abs(PB.y-charger[i].y) + abs(PB.x-charger[i].x)) <= charger[i].c){
            flagB = 1;
            check_arr[i][1] = 1;
        }
    }
}

void solution(){
    PA.y = 0, PA.x = 0;
    PB.y = 9, PB.x = 9;
    // 사용자는 초기 위치 0초부터 충전 할 수 있음!
    for(int i = -1; i < M; i++){
        if(i > -1){
            PA.y = PA.y + dy[P1[i]];
            PA.x = PA.x + dx[P1[i]];
            PB.y = PB.y + dy[P2[i]];
            PB.x = PB.x + dx[P2[i]];
        }
        //cout << "**" << i+1 << ": "<< PA.y << ", " << PA.x << " / " << PB.y << ", " << PB.x << "\n";
        memset(check_arr, 0, sizeof(check_arr));
        flagA = 0, flagB = 0;
        int cur = 0;
        checkDist();
        //cout << "flag: " << flagA << ", " << flagB << "\n";
        if(flagA == 1 && flagB == 1){
            int a, b;
            for(int j = 0; j < A; j++){
                if(check_arr[j][0] == 1){
                    a = j;
                    for(int k = 0; k < A; k++){
                        if(check_arr[k][1] == 1){
                            b = k;
                            if(a == b){
                                cur = max(cur, charger[a].p);
                            }
                            else if(a != b){
                                cur = max(cur, charger[a].p + charger[b].p);
                            }
                        }
                    }
                }
            }
        }
        else if(flagA == 1 && flagB == 0){
            for(int j = 0; j < A; j++){
                if(check_arr[j][0] == 1){
                    cur = max(cur, charger[j].p);
                }
            }
        }
        else if(flagA == 0 && flagB == 1){
            for(int j = 0; j < A; j++){
                if(check_arr[j][1] == 1){
                    cur = max(cur, charger[j].p);
                }
            }
        }
        //cout << cur << "\n";
        ans += cur;
    }
}

void solve(){
    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++){
        init();
        userInput();
        solution();
        cout << "#" << tc << " " << ans << "\n";
    }
}

int main(){
    solve();
    return 0;
}