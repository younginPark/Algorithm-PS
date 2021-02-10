#include <iostream>
#define MAX 15
using namespace std;

int col[MAX];
int N, total = 0;

bool next_col(int step){
    for(int i = 0; i < step; i++){
        if(col[i] == col[step] || abs(col[step] - col[i]) == step - i){
            return false;
        }
    }
    return true;
}

void nQueen(int x){
    if(x == N){
        total++;
    }
    else{
        for(int i = 0; i < N; i++){
            col[x] = i; //세로 열에 퀸이 몇 행이 있는지
            //대각선에 존재하지 않는 한 모든 경우 다 살핌
            if(next_col(x)){
                nQueen(x+1);
            }
        }
    }
}

int main(){
    scanf("%d", &N);
    nQueen(0);
    printf("%d\n", total);
    return 0;
}