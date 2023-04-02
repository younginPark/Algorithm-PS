#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

/*
입력을 받을 때 연산자의 개수만큼 for문을 돌면서 숫자들을 벡터에 넣어줌
해당 벡터의 크기만큼 for문을 돌면서 visited로 방문여부를 체크하면서 연산자만 따로 큐에 넣으면서 dfs 돌림
dfs를 멈추는 조건은 큐의 크기가 N-1 일 때

숫자를 미리 큐에 넣어놓고,
젤 첫번쨰 숫자는 미리 정답 변수에 저장해둠
그리고 그 이후부터 큐는 while !empty 하면서 하나씩 빼고 정답 변수에다가 연산자도 하나씩 빼면서 계산함

계산 다 끝나고 나서는 젤큰값, 작은값을 -1이 아니라면 비교해서 업데이트 해줌
*/

int N;
int number[13];
vector<int> oper;
int visited[4];
vector<int> my_oper;
long long max_num;
long long min_num;
int init_chk = 0;

void init(){
    memset(number, 0, sizeof(number));
    memset(visited, 0, sizeof(visited));
    oper.clear();
    my_oper.clear();
    init_chk = 0;
}

void userInput(){
    cin >> N;
    for(int i = 0; i < 4; i++){
        cin >> visited[i];
    }
    for(int i = 0; i < N; i++){
        cin >> number[i];
    }
}

void dfs(int cnt){
    if(cnt == N-1){
        // 계산
        long long ans = number[0];
        for(int i = 1; i < N; i++){
            if(my_oper[i-1] == 0){
                ans = ans + number[i];
            }
            else if(my_oper[i-1] == 1){
                ans = ans - number[i];
            }
            else if(my_oper[i-1] == 2){
                ans = ans * number[i];
            }
            else if(my_oper[i-1] == 3){
                ans = ans / number[i];
            }
        }
        if(init_chk == 0){
            init_chk = 1;
            min_num = ans;
            max_num = ans;
        }
        else{
            min_num = min(min_num, ans);
            max_num = max(max_num, ans);
        }
        //cout << min_num << " " << max_num << "\n";
        return;
    }
    for(int i = 0; i < 4; i++){
        if(visited[i] > 0){
            visited[i]--;
            my_oper.push_back(i);
            dfs(cnt+1);
            my_oper.pop_back();
            visited[i]++;
        }
    }
}

void solution(){
    for(int i = 0; i < 4; i++){
        if(visited[i] > 0){
            visited[i]--;
            my_oper.push_back(i);
            dfs(1);
            my_oper.pop_back();
            visited[i]++;
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
        cout << "#" << tc << " " << max_num-min_num << "\n";
    }
    return 0;
}