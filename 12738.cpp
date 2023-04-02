#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N;
vector<int> v;
int answer;
int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        int tmp;
        scanf("%d", &tmp);
        if(v.empty() || v.back() < tmp){
            v.push_back(tmp);
            answer++;
        }
        else{
            int idx = lower_bound(v.begin(), v.end(), tmp) - v.begin();
            v[idx] = tmp;
        }
    }
    printf("%d\n", answer);
    return 0;
}