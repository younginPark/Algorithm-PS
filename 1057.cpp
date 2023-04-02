#include <iostream>
using namespace std;

int main(){
    int N;
    int jimin = 0, hansoo = 0;
    int round = 0;
    
    cin >> N >> jimin >> hansoo;

    while(N){
        round++;
        if((jimin+1)/2 == (hansoo+1)/2){
            break;
        }
        jimin = (jimin+1)/2;
        hansoo = (hansoo+1)/2;
        N /= 2;
    }

    if(!N){
        round = -1;
    }

    cout << round;
    return 0;
}
