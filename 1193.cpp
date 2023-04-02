#include <iostream>
using namespace std;

int main(){

	int top, under;
	int tmp = 0;
	int now = 0;
	int input;
	int cnt = 1;
	cin >> input;

	while(1){
		now += cnt;
		tmp = now;
		if(input > now){
			cnt++;
			continue;
		}
		else{
			if(cnt % 2 == 0){
				top = cnt;
				under = 1;
				while(1){
					if(tmp == input){
						break;
					}
					else{
						top--;
						under++;

						tmp--;
					}
				}
				break;
			}
			else{
				top = 1;
				under = cnt;
				while(1){
					if(tmp == input){
						break;
					}
					else{
						top++;
						under--;

						tmp--;
					}
				}
				break;
			}
		}
	}
	cout << top << "/" << under;

	return 0;
}