#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int arr[101];

int GCD(int a, int b){
    while(1){
        int r = a % b;
        if(r == 0){
            return b;
        }
        else{
            a = b;
            b = r;
        }
    }
}

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d", &arr[i]);
    }
    sort(arr, arr+N);
    return 0;
}