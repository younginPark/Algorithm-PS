#include <iostream>
using namespace std;

int main(){

	int a, b, c;
	int div = 0;
	int cnt = 0;
	int result = 0;

	cin >> a >> b >> c;
	div = c-b;

	if(b >= c){
		result = -1;
	}
	else{
		result = a / div + 1;
	}

	cout << result;
	

	return 0;
}