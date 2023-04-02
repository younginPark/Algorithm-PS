#include <iostream>
#include <algorithm>
using namespace std;
int N, S;
int arr[100001];
int answer = 987654321;
int main(){
    scanf("%d %d", &N, &S);
    for(int i = 0; i < N; i++){
        scanf("%d", &arr[i]);
    }
    int left = 0, right = 0, tot = arr[0];
    while(left <= right && right < N){
        if(tot >= S){
            answer = min(answer, right-left+1);
        }
        if(tot < S){
            right++;
            tot += arr[right];
        }
        else{
            tot -= arr[left];
            left++;
        }
    }
    if(answer == 987654321){
        printf("0");
    }
    else{
        printf("%d\n", answer);
    }
    return 0;
}