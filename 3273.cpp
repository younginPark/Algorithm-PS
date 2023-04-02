#include <iostream>
#include <algorithm>
using namespace std;

int N;
int arr[100001];
int x;
int answer;
int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d", &arr[i]);
    }
    scanf("%d", &x);
    sort(arr, arr+N);
    int left = 0, right = N-1, tot = 0;
    while(left < right){
        tot = arr[left] + arr[right];
        //printf("left: %d, right: %d, tot: %d\n", left, right, tot);
        if(tot == x){
            answer++;
        }
        if(tot < x){
            left++;
        }
        else{
            right--;
        }
    }
    printf("%d\n", answer);
    return 0;
}