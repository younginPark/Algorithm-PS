#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
vector<pair< int, string> > v;
int N;

bool cmp(pair<int, string> a, pair<int, string> b){
    return a.first < b.first;
}

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        int tmp1;
        string tmp2;
        cin >> tmp1 >> tmp2;
        v.push_back(make_pair(tmp1, tmp2));
    }
    stable_sort(v.begin(), v.end(), cmp);
    for(int i = 0; i < N; i++){
        cout << v[i].first << " " << v[i].second << "\n";
    }
    return 0;
}