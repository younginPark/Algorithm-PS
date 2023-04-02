#include <iostream>
using namespace std;

int main(){
	int N;
	unsigned long first = 0, second = 1;
	int cnt = 2;
	unsigned long sum = 0;

	cin >> N;

	if(N == 0){
		cout << first;
	}
	else if(N == 1){
		cout << second;
	}
	else if(N > 1){
		while(cnt <= N){
			sum = first+second;
			first = second;
			second = sum;
			cnt++;
		}
		cout << sum;
	}
	return 0;
}