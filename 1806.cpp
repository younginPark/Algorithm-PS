#include <iostream>
#include <algorithm>
using namespace std;
int N, S;
int arr[100001];
int main(){
    scanf("%d %d", &N, &S);
    for(int i = 0; i < N; i++){
        scanf("%d", &arr[i]);
    }

    int low = 0, high = 0, tot = 0, answer = 987654321;
    while(low <= high && high <= N){
        if(tot < S){
            if(high == N){
                break;
            }
            tot += arr[high];
            high++;
        }
        else if(tot >= S){
            answer = min(answer, high-low);
            if(low <= high){
                tot -= arr[low];
                low++;
            }
        }
    }
    if(answer == 987654321){
        printf("0\n");
    }
    else{
        printf("%d\n", answer);
    }
    return 0;
}