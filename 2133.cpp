#include <iostream>
using namespace std;

int main(){
    int N = 0;
    int arr[31] = { 1, 0, 3, 0};
    cin >> N;
    for(int i = 4; i <= N; i++){
        arr[i] = arr[i-2] * 3;
        for(int j = 4; j <= i; j+=2){
            arr[i] += arr[i-j] * 2;
        }
    }
    printf("%d\n", arr[N]);
    return 0;
}