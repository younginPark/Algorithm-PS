#include <iostream>
using namespace std;

long long N, x;
long long coef[1000001] = { 0, };
long long expo[1000001] = { 0, };
long long result = 0;

int main(){
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> x;
	for(int i = N; i >= 0; i--){
		cin >> coef[i] >> expo[i];
	}
	for(int i = N-1; i >= 0; i--){
		if(i == N-1){
			if(coef[i] != 0){
				result = (coef[i+1] * x + coef[i]) % 1000000007;
			}
			else{
				result += coef[i];
			}
		}
		else{
			result = (result * x + coef[i]) % 1000000007;
		}
	}
	cout << result << "\n";
	return 0;
}