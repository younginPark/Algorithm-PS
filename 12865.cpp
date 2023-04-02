#include<iostream>
#include<vector>
#include<algorithm>
 
using namespace std;
 
int ans[100][100001];
 
int main()
{
    int N = 0;
    int can = 0;
    vector<pair<int, int> > arr;
 
    cin >> N >> can;
 
    for (int i = 0; i < N; i++){
    	int a, b;
        cin >> a >> b;
        arr.push_back(make_pair(a, b));
    }
 
    for (int i = 0; i < N; i++)    {
        for (int j = 0; j <= can; j++){
            if(i == 0)
            {
	            if(arr[i].first <= j){
	                ans[i][j] = arr[i].second;
	            	continue;
	        	}
            }
            else if(arr[i].first <= j){
            	            //직전 무게의 최대 가치, 현재 무게의 가치 + 이전에 내 무게를 뺏을 때 만큼의 가치
                ans[i][j] = max(ans[i-1][j], arr[i].second + ans[i-1][j-arr[i].first]);
            }
            else{
                ans[i][j] = ans[i-1][j]; //이전의 최대값
            }
        }
    }
    cout << ans[N-1][can];
    return 0;
}
