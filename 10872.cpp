#include <iostream>
using namespace std;

// int factorial(int N){
// 	if(N == 1){
// 		return 1;
// 	}
// 	return N * factorial(N-1);
// }

int main(){
	int N;
	cin >> N;
	int result = 1;
	//int result = factorial(N);
	for(int i = 1; i <= N; i++){
		result *= i;
	}
	cout << result << "\n";
	return 0;
}