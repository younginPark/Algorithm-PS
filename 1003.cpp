#include <iostream>
using namespace std;

int tc, N;
int zero[41] = { 1, 0, };
int one[41] = {0, 1, 0, };
//int sum[41] = { 0, 1, 0, };

void fibonacci(int n) {
	int cnt = 2;
    if (n == 0) {

        cout << zero[0] << " " << one[0] << "\n";

    } else if (n == 1) {

    	cout << zero[1] << " " << one[1] << "\n";

    } else {
    	while(cnt <= n){
	    	//sum[cnt] = sum[cnt-2] + sum[cnt-1];
	    	zero[cnt] = zero[cnt-2] + zero[cnt-1];
	    	one[cnt] = one[cnt-2] + one[cnt-1];
	    	cnt++;
	    }
	    cout << zero[n] << " " << one[n] << "\n";
    }
}

int main(){
	
	cin >> tc;
	for(int i = 0; i < tc; i++){
		cin >> N;
		fibonacci(N);
	}

	return 0;
}