#include <iostream>
using namespace std;

int N;

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        int tmp1, tmp2;
        int answer = 1;
        scanf("%d %d", &tmp1, &tmp2);
        int num = 2;
        while(num <= tmp1 || num <= tmp2){
            if(tmp1 % num == 0 && tmp2 % num == 0){
                tmp1 /= num;
                tmp2 /= num;
                answer *= num;
            }
            else{
                num++;
            }
        }
        printf("%d\n", answer * tmp1 * tmp2);
    }
    return 0;
}