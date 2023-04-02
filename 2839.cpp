#include <iostream>
using namespace std;

int main(){

	int num_5 = 0;
	int num_3 = 0;
	int total = 0;
	int copy = 0;
	int cnt = 0;

	cin >> total;
	copy = total;

	if(total % 5 == 0){
		num_5 = total / 5;
	}
	else{
		//cout << " ! 3 ";
		copy = total;
		while(1){
			cnt++;
			copy -= 3;
			if(copy % 5 == 0){
				num_3 = cnt;
				num_5 = copy / 5;
				break;
			}
			if(copy < 3){
				break;
			}
		}
	}
	//cout << " ! 4 ";

//출력
	if(num_5 + num_3 == 0){
		cout << "-1";
	}
	else{
		cout << num_5 + num_3;
	}

	return 0;
}