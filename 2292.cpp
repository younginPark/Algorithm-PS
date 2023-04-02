#include <iostream>
using namespace std;

int main(){

	int num = 0;
	int start = 1;
	int last = 2;
	int cnt = 0;
	cin >> num;

	cnt = 0;

	while(1){
		cnt++;
		if(start <= num && num < last){
			cout << cnt;
			break;
		}
		else{
			start = last;
			last = last + 6*cnt;
		}


	}

	return 0;
}