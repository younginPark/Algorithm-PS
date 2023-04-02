#include <iostream>
using namespace std;

long long fibo(int N) {
    if(N == 0) {
        return 0;
    }
    if(N == 1) {
        return 1;
    }
    long long ans = 0;
    long long first = 0;
    long long second = 1;
    for(int i = 2; i <= N; i++){
        ans = (first + second) % 1000000007;
        first = second;
        second = ans;
    }
    return ans;
}

int main () {

    int N;
    cin >> N;
    cout << fibo(N);
    return 0;
}