#include <iostream>
#include <algorithm>
using namespace std;
int answer;
int N, M;
int arr[10001];
int main(){
    scanf("%d %d", &N, &M);
    for(int i = 0; i < N; i++){
        scanf("%d", &arr[i]);
    }
    int left = 0, right = 0, tot = 0;
    while(left <= right && right <= N){
        if(tot == M){
            answer++;
        }
        if(tot < M){
            tot += arr[right];
            right++;
        }
        else if(tot >= M){
            tot -= arr[left];
            left++;
        }
    }
    printf("%d\n", answer);
    return 0;
}