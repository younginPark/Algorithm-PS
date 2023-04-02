#include <iostream>
using namespace std;

int main(){
    int tc;
    scanf("%d", &tc);
    for(int i = 0; i < tc; i++){
        int M, N, x, y;
        int find = 0;
        scanf("%d %d %d %d", &M, &N, &x, &y);
        x--;
        y--;
        for(int j = x; j < M*N; j += M){
            if(j%N == y){
                printf("%d\n", j+1);
                find = 1;
                break;
            }
        }
        if(find == 0){
            printf("-1\n");
        }
    }
    return 0;
}