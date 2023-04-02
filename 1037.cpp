#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N;
vector<int> v;
int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        int tmp;
        scanf("%d", &tmp);
        v.push_back(tmp);
    }
    sort(v.begin(), v.end());
    printf("%d\n", v[0] * v[N-1]);
    return 0;
}