#include <iostream>
using namespace std;

// 6각형은 컴퓨터로 표현하기 어려움으로 구현해서 찾기보다 규칙을 찾아야 함
int num;
int main(){
    cin >> num;
    if(num == 1){
        cout << 1;
        return 0;
    }
    int val = 1;
    int cnt = 1;
    while (val <= 1000000000){
        val += (cnt * 6);
        if(num <= val){
            cout << cnt+1;
            break;
        }
        cnt++;    
    }
    return 0;
}