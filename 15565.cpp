#include <iostream>
#include <algorithm>
using namespace std;
int N, K;
int arr[1000001];
int answer = 987654321;
int main(){
    scanf("%d %d", &N, &K);
    for(int i = 1; i <= N; i++){
        scanf("%d", &arr[i]);
    }
    int left = 1, right = 1, tot = 0, ans_left, ans_right;
    if(arr[left] == 1){
        tot++;
    }
    while(left <= right && right <= N){
        //printf("ing~ left: %d, right: %d, tot: %d\n", left, right, tot);
        if(tot == K){
            //printf("!! tot==K left: %d, right: %d\n", left, right);
            if(right-left < answer){
                answer = right-left;
                ans_left = left;
                ans_right = right;
            }
        }
        if(right-left >= answer || tot >= K){
            if(arr[left] == 1){
                tot--;
            }
            left++;
        }
        else if(tot < K){
            right++;
            if(arr[right] == 1){
                tot++;
            }
        }
    }
    if(answer == 987654321){
        printf("-1\n");
    }
    else{
        printf("%d\n", ans_right-ans_left+1);
    }
    return 0;
}