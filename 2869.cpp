#include <iostream>
using namespace std;

int main(){

	int a,b,v;
	int now = 0;
	int cnt = 0;

	cin >> a >> b >> v;

	if((v - a) % (a - b) == 0){
		cnt = (v - a) / (a - b);
	}
	else{
		cnt = (v - a) / (a - b) + 1;
	}

	cnt++;
	cout << cnt;

	return 0;
}