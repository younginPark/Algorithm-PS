#include <iostream>
#include <cstring>
#define MAX_NUM 1001
using namespace std;

int max(int a, int b){
	return a > b ? a : b;
}

int main(){
	char arr1[MAX_NUM] = { 0, };
	char arr2[MAX_NUM] = { 0, };
	int dp[MAX_NUM][MAX_NUM] = { 0, };
	int len1 = 0, len2 = 0;

	cin >> arr1 >> arr2;
	len1 = strlen(arr1);
	len2 = strlen(arr2);

	for(int i = 0; i < len2; i++){
		for(int j = 0; j < len1; j++){
			if(arr2[i] == arr1[j]){
				dp[i+1][j+1] = dp[i][j] + 1;
			}
			else if(arr2[i] != arr1[j]){
				dp[i+1][j+1] = max(dp[i][j+1], dp[i+1][j]);
			}
		}
	}

	cout << dp[len2][len1];


	return 0;
}