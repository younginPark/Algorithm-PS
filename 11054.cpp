#include <iostream>
#include <algorithm>
using namespace std;
int N;
int arr[1001];
int dp1[1001];
int dp2[1001];
int result[1001];
bool cmp(int i, int j){
	return j < i;
}

int main(){
	scanf("%d", &N);
	for(int i = 0; i < N; i++){
		scanf("%d", &arr[i]);
		dp1[i] = 1;
		dp2[i] = 1;
	}
	for(int i = 0; i < N; i++){
		for(int j = 0; j < i; j++){
			if(arr[j] < arr[i]){
				dp1[i] = max(dp1[i], dp1[j]+1);
			}
		}
	}
	for(int i = N-1; i >= 0; i--){
		for(int j = N-1; j > i; j--){
			if(arr[j] < arr[i]){
				dp2[i] = max(dp2[i], dp2[j]+1);
			}
		}
	}

	// for(int i = 0; i < N; i++){
	// 	printf("%d ", dp1[i]);
	// }
	// printf("\n");
	// for(int i = 0; i < N; i++){
	// 	printf("%d ", dp2[i]);
	// }
	// printf("\n");
	
	for(int i = 0; i < N; i++){
		result[i] = dp1[i] + dp2[i] - 1;
	}
	sort(result, result+N, cmp);
	printf("%d\n", result[0]);
	return 0;
}