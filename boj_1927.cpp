#include <iostream>
#include <queue>
using namespace std;

int main(){
    int N;
    priority_queue<int, vector<int>, greater<int> > pq;
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        int tmp;
        scanf("%d", &tmp);
        if(tmp == 0 && !pq.empty()){
            printf("%d\n", pq.top());
            pq.pop();
        }
        else if(tmp != 0){
            pq.push(tmp);
        }
        else if(tmp == 0 && pq.empty()){
            printf("0\n");
        }
    }
    return 0;
}