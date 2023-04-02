#include <iostream>
using namespace std;

int N;
int ans = 0;
int arr[26][26];

int main(){
	scanf("%d", &N);
	for(int i = 0; i < N; i++){
		char tmpArr[26];
		scanf("%s", tmpArr); 
		printf("%s", tmpArr);
		for(int j = 0; j < N; j++){
			arr[i][j] = tmpArr[j] - '0';
		}
	}
	// for(int i = 0; i < N; i++){
	// 	for(int j = 0; j < N; i++){
	// 		printf("%d", arr[i][j]);
	// 	}
	// }
	return 0;
}