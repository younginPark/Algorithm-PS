#include <iostream>
#include <algorithm>
using namespace std;
int N;
int arr[1001];
int dp[1001];

bool cmp(int i, int j){
	return j < i;
}

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d", &arr[i]);
		dp[i] = 1;
    }
	for(int i = 0; i < N; i++){
		for(int j = 0; j < i; j++){
			if(arr[j] < arr[i]){
				dp[i] = max(dp[i], dp[j]+1);
			}
		}
	}
	sort(dp, dp+N, cmp);
	printf("%d\n", dp[0]);
    return 0;
}