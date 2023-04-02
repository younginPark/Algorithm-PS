#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){

    int N;
    cin >> N;
    vector<int> v;
    for(int i = 0; i < N; i++){
        v.push_back(i+1);
    }
    do{
        for(int i = 0; i < N; i++){
            printf("%d ", v[i]);
        }
        printf("\n");
    }while(next_permutation(v.begin(), v.end()));

    return 0;
}