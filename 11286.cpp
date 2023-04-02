#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

priority_queue< pair<long long, long long>, vector<pair<long long, long long> >, greater<pair<long long , long long > > > pq;
int N;
int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        long long tmp1;
        scanf("%lld", &tmp1);
        if(tmp1 == 0){
            if(!pq.empty()){
                //printf("*** %lld %lld\n", pq.top().first, pq.top().second);
                if(pq.top().second == 0){
                    printf("-%lld\n", pq.top().first);
                }
                else{
                    printf("%lld\n", pq.top().first);
                }
                pq.pop();
            }
            else{
                printf("0\n");
            }
        }
        else{
            if(tmp1 < 0){
                pq.push(make_pair(abs(tmp1), 0));
            }
            else{
                pq.push(make_pair(abs(tmp1), 1));
            }
        }
    }
    return 0;
}