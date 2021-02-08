#include <iostream>
#include <string>
using namespace std;

int N;
char arr[66][66];
string result;

void go(int n, int startY, int startX){
    char now = arr[startY][startX];
    bool check = true;
    for(int i = startY; i < startY + n; i++){
        for(int j = startX; j < startX + n; j++){
            if(arr[i][j] != now){
                check = false;
                break;
            }
        }
        if(!check){
            break;
        }
    }
    if(check){
        result += arr[startY][startX];
    }
    else{
        result += '(';
        go(n/2, startY, startX);
        go(n/2, startY, startX+(n/2));
        go(n/2, startY+(n/2), startX);
        go(n/2, startY+(n/2), startX+(n/2));
        result += ')';
    }
}

int main(){
    cin >> N;
    for(int i = 1; i <= N; i++){
        string tmp;
        cin >> tmp;
        for(int j = 1; j <= N; j++){
            arr[i][j] = tmp[j-1];
        }
    }
    go(N, 1, 1);
    printf("%s\n", result.c_str());
    return 0;
}