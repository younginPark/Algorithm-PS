#include <iostream>
#include <queue>
#include <string>
#include <cmath>
using namespace std;

/*
- 16진수를 10진수로 표현 가능해야함
- 정렬을 할 줄 알아야 함 혹은 우선순위 큐 사용
- 중복되는 값이 이미 들어가 있는지 찾을 수 있어야 함
- 입력이 공백 없이 한줄로 들어올 때 string stl을 써서 받을 수 있어야 함

각 변은 그냥 1차원 큐에 쭉 놓고 N/4개씩 문자 읽어서 10진수로 전환
N번만 돌리면 됨, 돌릴 떄는 큐에서 머리꺼 pop 해서 뒤에 push 해주면 됨

회전 시 각 변의 총 4가지 숫자를 우선순위 큐에 일단 쭉 넣음
N번 회전 다 한 후에 우선순위 큐에서 pop 하고 top이 방금 pop 한 값과 같다면 push 안하고 그렇지 않다면 다시 push
위 설명의 횟수는 우선순위 큐의 사이즈 만큼만 해줘야 함
이렇게 하면 우선순위 큐에 중복된 값은 다 사라지게 되고 여기서부터 K번째까지 pop하면서 정답을 구하면 됨
*/

int T;
int N, K;
string str1;
queue<char> q;
queue<long long> myq;
priority_queue<long long> pq;

void init(){
    while(!q.empty()) q.pop();
    while(!myq.empty()) myq.pop();
    while(!pq.empty()) pq.pop();
}

int convert16to10(char a){
    if(a == 'A'){
        return 10;
    }
    if(a == 'B'){
        return 11;
    }
    if(a == 'C'){
        return 12;
    }
    if(a == 'D'){
        return 13;
    }
    if(a == 'E'){
        return 14;
    }
    if(a == 'F'){
        return 15;
    }
    return 0;
}

void solution(int order){
    init();
    for(int i = 0; i < str1.length(); i++){
        q.push(str1[i]);
    }

    // 회전
    for(int i = 0; i < N/4; i++){
        // 숫자 N/4개씩 골라서 16진수를 10진수로 변환
        for(int loop = 0; loop < 4; loop++){
            long long num = 0;
            for(int pow_num = (N/4)-1; pow_num >= 0; pow_num--){
                char cur_num = q.front();
                q.pop();
                q.push(cur_num);
                int tmp;
                if('A' <= cur_num && cur_num <= 'F'){
                    tmp = convert16to10(cur_num);
                }
                else{
                    tmp = cur_num - '0';
                }
                long long head = pow(16, pow_num);
                num += (tmp * head);
                //cout << cur_num << " " << tmp << ", " << head << " = " << num << "\n";
            }
            pq.push(num);
            //cout << "---\n";
        } 
        int q_size = q.size();
        for(int i = 0; i < q_size-1; i++){
            int frontVal = q.front();
            q.pop();
            q.push(frontVal);
        }
    }

    int pq_size = pq.size();
    for(int i = 0; i < pq_size; i++){
        myq.push(pq.top());
        pq.pop();
    }

    int myq_size = myq.size();
    for(int i = 0; i < myq_size; i++){
        int frontVal = myq.front();
        myq.pop();
        if(frontVal == myq.front()){
            continue;
        }
        else{
            myq.push(frontVal);
        }
    }

    myq_size = myq.size();
    for(int i = 0; i < myq_size; i++){
        pq.push(myq.front());
        //cout << myq.front() << "\n";
        myq.pop();
    }


    pq_size = pq.size();
    for(int i = 0; i < pq_size; i++){
        int topVal = pq.top();
        pq.pop();
        if(topVal == pq.top()){
            continue;
        }
        else{
            pq.push(topVal);
        }
    }

    for(int i = 0; i < K-1; i++){
        pq.pop();
    }
    cout << "#" << order+1 << " " << pq.top() << "\n";
}

int main(){
    cin >> T;
    for(int i = 0; i < T; i++){
        cin >> N >> K;
        cin >> str1;
        solution(i);
    }
    return 0;
}