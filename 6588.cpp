#include <iostream>
#include <cmath>
using namespace std;
bool prime[1000001];
int main(){
    for(int i = 0; i <= 1000000; i++){
        prime[i] = true;
    }
    prime[0] = false;
    prime[1] = false;

    for(int i = 2; i*i <= 1000000; i++){
        if(prime[i] == false){
            continue;
        }
        for(int j = i*i; j <= 1000000; j+=i){
            prime[j] = false;
        }
    }

    while(1){
        int n;
        int a, b;
        scanf("%d", &n);
        bool goldbach = false;
        if(n == 0){
            break;
        }
        for(int i = 3; i <= n; i+=2){
            if(prime[i] == true && prime[n-i] == true){
                printf("%d = %d + %d\n", n, i, n-i);
                goldbach = true;
                break;
            }
            else{
                if(i > n/2){
                    break;
                }
                continue;
            }
        }
        if(goldbach == false){
            printf("Goldbach's conjecture is wrong.\n");
        }
    }
    return 0;
}