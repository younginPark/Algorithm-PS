#include <iostream>
#include <string>
#include <queue>
using namespace std;

int main(){
    string str1;
    cin >> str1;
    priority_queue<int> pq;
    for(int i = 0; i < str1.length(); i++){
        pq.push(str1[i] - 48);
    }
    while(!pq.empty()){
        printf("%d", pq.top());
        pq.pop();
    }
    return 0;
}