#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
	int N = 0;
	int tmp1 = 0, tmp2 = 0;
	vector<pair<int,int> > arr;
	vector<int> dp;

	cin >> N;
	dp = vector<int>(N,1);
	for(int i = 0; i < N; i++){
		cin >> tmp1 >> tmp2;
		arr.push_back(make_pair(tmp1, tmp2));
	}

	sort(arr.begin(), arr.end()); //first기준으로 정렬

	//first는 이미 정렬되어 있으니까 second만 최장길이증가수열 찾으면 됨
	for(int i = 0; i < N; i++){
		for(int j = 0; j < i; j++){
			if(arr[j].second < arr[i].second && dp[j]+1 > dp[i]){
				dp[i] = dp[j] + 1;
			}
		}
	}

	cout << arr.size() - (*max_element(dp.begin(), dp.end())) << "\n";
	return 0;
}

