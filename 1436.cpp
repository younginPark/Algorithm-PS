#include <iostream>
using namespace std;

int main(){
	int N;
	int cnt = 0;
	int num = 665;
	int copy = 0;
	int six = 0;
	cin >> N;

	while(cnt < N){
		num++;
		copy = num;
		six = 0;

		while(copy != 0){
			if(copy % 10 == 6){
				six++;
			}
			else{
				six = 0;
			}
			copy /= 10;
			if(six == 3){
				cnt++;
				break;
			}
		}
	}

	cout << num;

	return 0;
}