#include <iostream>
using namespace std;

int N;

int main() {
    scanf("%d", &N);

    int five_cnt = N / 5;
    int two_cnt = (N - (5 * five_cnt)) / 2;
    while((N - (5 * five_cnt)) % 2) {
        five_cnt--;
        two_cnt = (N - (5 * five_cnt)) / 2;
        if(five_cnt < 0){
            five_cnt = 0;
            two_cnt = -1;
            break;
        }
    }
    cout << five_cnt + two_cnt;

    return 0;
}