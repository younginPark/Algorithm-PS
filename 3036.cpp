#include <iostream>
using namespace std;

int main(){
    int N;
    int arr[101];
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d", &arr[i]);
    }
    for(int i = 1; i < N; i++){
        int tmp1 = arr[0];
        int tmp2 = arr[i];
        int num = 2;
        while(num <= tmp1 || num <= tmp2){
            if(tmp1 % num == 0 && tmp2 % num == 0){
                tmp1 /= num;
                tmp2 /= num;
            }
            else{
                num++;
            }
        }
        printf("%d/%d\n", tmp1, tmp2);
    }
    return 0;
}