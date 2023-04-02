#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

/*
시간에 맞춰서 구현하고 종료 조건은 정비창구에 있는 손님도 없으면서 정비창구를 기다리는 손님도 없을 경우
입력받은 값과 별개로
창구를 운영할 때는 다른 변수를 이용

보낼사람은 보내고 큐에 넣을 사람은 큐에 넣은 다음에
큐에 있는 사람들을 다시 빈 접수대에 차례로 넣어줌
T는 0부터 시작

일단 접수 대기 큐에 입력 받은 사람을 순서대로 넣음
접수 창구에 사람이 언제까지 있는지에 대해 할 수 있는 배열에 0으로 초기화

1. 접수창구 배열에서 0이 아니면서 현재시간과 같으면 해당 사람을 정비창구 큐에 넣어줌, 이때 손님의 창구번호 기록
2. 정비창구 배열에서 0이 아니면서 현재시간과 같으면 빼줌, 이때 손님의 창구번호 기록, 다 마무리한 사람의 수 +1씩 해줌(종료조건으로 사용)
3. 입력 받은 큐의 top의 시간이 현재와 같은 것들은 쭉 빼내서 접수창구 큐에 넣어줌
4. 접수창구 큐가 0보다 크면 1번부터 접수창구 값이 0인거 찾아서 현재시간+해당창구일하는시간 넣어줌, 창구 없으면 break
5. 정비창구 큐가 0보다 크면 1번부터 정비창구 값이 0인거 찾아서 현재시간+해당창구일하는시간 넣어줌, 창구 없으면 break

종료조건은 정비창구에서 탈출한 사람의 수가 들어온 사람의 수와 같을 때
*/

int N, M, K, A, B;
int a[10];
int b[10];
queue<pair<int, int> > customer;

queue<int> waitA;
queue<int> waitB;
pair<int, int> timeA[10]; // (고객번호, 끝나는시간)
pair<int, int> timeB[10];
pair<int, int> customer_info[1001];
int clear_cus = 0;
int ans = 0;

void init(){
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    while(!customer.empty()) customer.pop();
    while(!waitA.empty()) waitA.pop();
    while(!waitB.empty()) waitB.pop();
    memset(timeA, 0, sizeof(timeA));
    memset(timeB, 0, sizeof(timeB));
    memset(customer_info, 0, sizeof(customer_info));
    clear_cus = 0;
    ans = 0;
}

void userInput(){
    cin >> N >> M >> K >> A >> B;
    A--; B--;
    for(int i = 0; i < N; i++){
        cin >> a[i];
    }
    for(int i = 0; i < M; i++){
        cin >> b[i];
    }
    for(int i = 0; i < K; i++){
        int tmp;
        cin >> tmp;
        customer.push(make_pair(i, tmp));
    }
}

void pirntAB(){
    cout << "창구 A: ";
    for(int i = 0; i < N; i++){
        cout << "(" << timeA[i].first << "," << timeA[i].second << ") ";
    }
    cout << "\n";

    cout << "창구 B: ";
    for(int i = 0; i < M; i++){
        cout << "(" << timeB[i].first << "," << timeB[i].second << ") ";
    }
    cout << "\n";
}

void printCustomerInfo(){
    for(int i = 0; i < K; i++){
        cout << customer_info[i].first << " " << customer_info[i].second << "\n";
    }
}

void solution(){
    int time = 0;
    // 종료조건은 정비창구에서 탈출한 사람의 수가 들어온 사람의 수와 같을 때
    while(clear_cus < K){
        // 접수창구 배열에서 0이 아니면서 현재시간과 같으면 해당 사람을 정비창구 큐에 넣어줌, 이때 손님의 창구번호 기록
        for(int i = 0; i < N; i++){
            if(time != 0 && timeA[i].second == time){
                int customer_num = timeA[i].first;
                customer_info[customer_num].first = i;
                waitB.push(customer_num);
                timeA[i].first = 0;
                timeA[i].second = 0;
            }
        }
        // 정비창구 배열에서 0이 아니면서 현재시간과 같으면 빼줌, 이때 손님의 창구번호 기록, 다 마무리한 사람의 수 +1씩 해줌(종료조건으로 사용)
        for(int i = 0; i < M; i++){
            if(time != 0 && timeB[i].second == time){
                int customer_num = timeB[i].first;
                customer_info[customer_num].second = i;
                clear_cus++;
                timeB[i].first = 0;
                timeB[i].second = 0;
            }
        }

        // 입력 받은 큐의 top의 시간이 현재와 같은 것들은 쭉 빼내서 접수창구 큐에 넣어줌
        while(1){
            if(customer.size() > 0 && customer.front().second == time){
                waitA.push(customer.front().first);
                customer.pop();
            }
            else{
                break;
            }
        }

        // 접수창구 큐가 0보다 크면 1번부터 접수창구 값이 0인거 찾아서 현재시간+해당창구일하는시간 넣어줌, 창구 없으면 break
        if(waitA.size() > 0){
            for(int i = 0; i < N; i++){
                if(timeA[i].second == 0){
                    timeA[i].first = waitA.front();
                    timeA[i].second = a[i] + time;
                    waitA.pop();
                }
                if(waitA.size() == 0){
                    break;
                }
            }
        }

        // 정비창구 큐가 0보다 크면 1번부터 정비창구 값이 0인거 찾아서 현재시간+해당창구일하는시간 넣어줌, 창구 없으면 break
        if(waitB.size() > 0){
            for(int i = 0; i < M; i++){
                if(timeB[i].second == 0){
                    timeB[i].first = waitB.front();
                    timeB[i].second = b[i] + time;
                    waitB.pop();
                }
                if(waitB.size() == 0){
                    break;
                }
            }
        }
        // cout << "time " << time << "------\n";
        // pirntAB();
        time++;
    }

    // 창구 번호 일치하는 고객의 번호 값 다 더하기
    // printCustomerInfo();
    for(int i = 0; i < K; i++){
        if(customer_info[i].first == A && customer_info[i].second == B){
            ans += i+1;
        }
    }
    if(ans == 0){
        ans = -1;
    }
}

int main(){
    int T;
    cin >> T;
    for(int tc = 1; tc <= T; tc++){
        init();
        userInput();
        solution();
        cout << "#" << tc << " "  << ans << "\n";
    }
    return 0;
}