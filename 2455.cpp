#include <iostream>
#define STATION 4
using namespace std;

int main(){
	int in[STATION+1] = { 0, };
	int out[STATION+1] = { 0, };
	int now = 0;
	int max = 0;

	for(int i = 0; i < STATION; i++){
		cin >> out[i] >> in[i];
	}

	now = in[0];
	for(int i = 1; i < STATION; i++){
		now -= out[i];
		now += in[i];
		if(now > max){
			max = now;
		}
	}
	cout << max;
	return 0;
}