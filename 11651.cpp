#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b){
    if(a.second == b.second){
        return a.first < b.first;
    }
    else{
        return a.second < b.second;
    }
}

int main(){
    int N;
    vector<pair<int, int> > v;
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        int tmp1, tmp2;
        scanf("%d %d", &tmp1, &tmp2);
        v.push_back(make_pair(tmp1, tmp2));
    }
    sort(v.begin(), v.end(), cmp);

    for(int i = 0; i < N; i++){
        printf("%d %d\n", v[i].first, v[i].second);
    }
    return 0;
}