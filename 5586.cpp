#include <iostream>
#include <string>
using namespace std;

int main(){

    string str;
    int joi_cnt = 0, ioi_cnt = 0;
    cin >> str;
    for(int i = 0; i < str.length()-2; i++){
        if(str[i] == 'J' && str[i+1] == 'O' && str[i+2] == 'I'){
            joi_cnt++;
        }
        else if(str[i] == 'I' && str[i+1] == 'O' && str[i+2] == 'I'){
            ioi_cnt++;
        }
    }
    printf("%d\n", joi_cnt);
    printf("%d", ioi_cnt);
    return 0;
}