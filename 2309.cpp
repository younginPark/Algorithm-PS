#include <iostream>
#include <algorithm>
using namespace std;

int main(){
	
	int height[10] = {0, };
	int tmp[9] = {0, };
	int temp = 0;
	int sum  = 0;
	int out1 = 0, out2 = 0;
	int flag = 0;

	for(int i = 0; i < 9; i++){
		cin >> height[i];
	}

	for(int i = 0; i < 8; i++){
		flag = 0;
		for(int k = 1; k < 9; k++){
			for(int h = 0; h < 9; h++){
				if(h != i && h != k){
					tmp[h] = height[h];
				}
				else{
					tmp[h] = 0;
				}
			}
			sum = 0;
			for(int j = 0; j < 9; j++){
				sum += tmp[j];
			}
			if(sum == 100){
				flag = 100;
				break;
			}
		}
		if(flag == 100){
			break;
		}
	}


	//오름차순
	sort(tmp, tmp+9);

	//최종 출력
	for(int i = 0; i < 9; i++){
		if(tmp[i] != 0){
			cout << tmp[i] << "\n";
		}
	}

	return 0;
}