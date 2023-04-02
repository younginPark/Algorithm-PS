#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    while(1) {
        int K;
        cin >> K;
        if(K == 0){
            break;
        }
        vector<int> v(K, 0);
        vector<int> comb(K, 0);
        for(int i = 0; i < 6; i++){
            comb[i] = 1;
        }
        for(int i = 0; i < K; i++){
            cin >> v[i];
        }
        do{
            for(int i = 0; i < K; i++){
                if(comb[i] != 0){
                    printf("%d ", v[i]);
                }
            }
            printf("\n");
        }while(prev_permutation(comb.begin(), comb.end()));
        printf("\n");
    }
    return 0;
}