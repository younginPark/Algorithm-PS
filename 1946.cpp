#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int tc;
int main(){
    scanf("%d", &tc);
    for(int i = 0; i < tc; i++){
        int n;
        int answer = 0;
        vector<pair<int, int > > v;
        scanf("%d", &n);
        for(int j = 0; j < n; j++){
            int tmp1, tmp2;
            scanf("%d %d", &tmp1, &tmp2);
            v.push_back(make_pair(tmp1, tmp2));
        }
        sort(v.begin(), v.end());
        // printf("***********\n");
        // for(int j = 0; j < n; j++){
        //     printf("%d %d\n", v[j].first, v[j].second);
        // }
        // printf("***********\n");
        int m = 987654321;
        for(int j = 0; j < n; j++){
            if(v[j].second < m){
                answer++;
                m = v[j].second;
            }
        }
        printf("%d\n", answer);
    }
    return 0;
}