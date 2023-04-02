#include <iostream>
using namespace std;

double factorial(int num){
	double result;
	if(num <= 1){
		return 1;
	}
	else{
		result = num * factorial(num - 1);
	}
	return result;
}

int main(){
	long long N, K;
	double top, bot1, bot2, result;

	cin >> N >> K;
	//26 + (N/2) - 1
	top = factorial(47);
	bot1 = factorial(25);
	bot2 = factorial(N/2);
	cout << top << ", " << bot1 << ", " << bot2 << "\n";
	if(N % 2 != 0){
		result = (top / (bot1 * bot2)) * 26;
	}
	else{
		result = (top / (bot1 * bot2));
	}

	result = factorial(result) / (factorial(K) * factorial(result-K));
	cout << result;
	return 0;
}