#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int N;
long long arr[100001];
int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%lld", &arr[i]);
    }
    sort(arr, arr+N);
    int left = 0, right = N-1;
    long long result1, result2;
    long long min_ans = 2000000000;
    while(left < right && right <= N){
        int tot = arr[left] + arr[right];
        if(abs(tot) < abs(min_ans)){
            min_ans = tot;
            result1 = arr[left];
            result2 = arr[right];
            //printf("작을 때: %d %d\n", result1, result2);
        }
        if(tot == 0){
            break;
        }
        if(tot > 0){
            right--;
        }
        else{
            left++;
        }
    }
    printf("%lld %lld\n", result1, result2);
    return 0;
}