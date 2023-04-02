#include <iostream>
using namespace std;

int main(){

	int num = 0;
	int arr[101] = {0, };
	int s[101] = {0, };
	int b[101] = {0, };
	int hun = 0, ten = 0, one = 0;
	int hun2 = 0, ten2 = 0, one2 = 0;
	int tmp = 0; 
	int tmp2 = 0;
	int strike = 0, ball = 0;
	int result = 0;
	int cnt = 0;
//입력
	cin >> num;
	for(int i = 0; i < num; i++){
		cin >> arr[i] >> s[i] >> b[i];
	}
//비교시작
	for(int i = 123; i <= 987; i++){
		cnt = 0;
		tmp2 = i;
		one2 = tmp2 % 10;
		tmp2 /= 10;
		ten2 = tmp2 % 10;
		hun2 = tmp2 / 10;
		if(one2 == 0 || ten2 == 0 || hun2 == 0){
			continue;
		}
		if(one2 == ten2 || one2 == hun2 || hun2 == ten2){
			continue;
		}
		//cout << "*****확인222***** " << hun2 << " " << ten2 << " " << one2 << "\n";
		for(int j = 0; j < num; j++){
			cnt++;
			strike = 0; ball = 0; //초기화!
			tmp = arr[j];
			one = tmp % 10;
			tmp /= 10;
			ten = tmp % 10;
			hun = tmp / 10;
			//cout << "*****확인111***** " << hun << " " << ten << " " << one << "\n";

			if(hun == hun2){
				strike++;	
			}
			if(ten == ten2){
				strike++;
			}
			if(one == one2){
				strike++;
			}
			if(hun == ten2){
				ball++;
			}
			else if(hun == one2){
				ball++;
			}
			if(ten == hun2){
				ball++;
			}
			else if(ten == one2){
				ball++;
			}
			if(one == hun2){
				ball++;
			}
			else if(one == ten2){
				ball++;
			}

			if(strike == s[j] && ball == b[j]){
				if(cnt == num){
					result++;
					//cout << "이거야 !!! : " << i << "\n"; 
				}
				else{
					continue;
				}
			}
			else{
				break;
			}
		}

		
	}

	cout << result << "\n";

	return 0;
}
