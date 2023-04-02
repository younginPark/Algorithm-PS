#include <iostream>
using namespace std;

int main(){

	//int arr[100][100] = { 0, };
	int tc = 0;
	int h, w, n;
	int floor = 0;
	int num = 0;
	int cnt = 0;
	int copy = 0;

	cin >> tc;
	for(int i = 0; i < tc; i++){
		cin >> h >> w >> n;
		copy = n;
		while(copy >= h){
			copy -= h;
			cnt++;
		}
		if(copy != 0){
			cnt++;
		}
		num = cnt;

		cnt = 0;
		if(copy == 0){
			copy = h;
		}
		floor = copy;

		if(num < 10){
			cout << floor << "0" << num << "\n";
		}
		else{
			cout << floor << num << "\n";
		}
	}
	return 0;
}