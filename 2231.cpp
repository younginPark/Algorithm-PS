#include <iostream>
using namespace std;

int main(){
	int N;
	int result = 0;
	int copy = 0;
	int tot = 0;

	cin >> N;

	for(int i = 0; i < 1000000; i++){
		copy = i;
		tot = i;
		while(copy != 0){
			tot += copy % 10;
			copy /= 10;
		}

		if(tot == N){
			result = i;
			break;
		}
	}

	cout << result;
	return 0; 
}