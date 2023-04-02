#include <iostream>
#include <queue>
using namespace std;

priority_queue<long long> pq;
int N;
int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        long long tmp1;
        scanf("%lld", &tmp1);
        if(tmp1 == 0){
            if(!pq.empty()){
                printf("%lld\n", pq.top());
                pq.pop();
            }
            else{
                printf("0\n");
            }
        }
        else{
            pq.push(tmp1);
        }

    }
    return 0;
}