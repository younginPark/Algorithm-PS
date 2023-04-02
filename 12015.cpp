#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N;
int arr[1001];
int answer;
vector<int> v;
int main(){
    scanf("%d", &N);
    v.push_back(-1);
    for(int i = 0; i < N; i++){
        int tmp;
        scanf("%d", &tmp);
        if(v.back() < tmp){
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