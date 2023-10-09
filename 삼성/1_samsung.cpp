#include <iostream>
#define MAX_ROW 255
#define MAX_COL 1001
#define TC 10
using namespace std;

int main(){

	for(int tc = 1; tc <= TC; tc++){
		int arr[MAX_ROW+1][MAX_COL] = { 0, };
		int tot_home = 0;
		int cnt = 0;
		cin >> tot_home;
		for(int i = 0; i < tot_home; i++){
			int tmp = 0;
			cin >> tmp;
			if(tmp == 0){
				continue;
			}
			for(int j = 0; j < tmp; j++){
				arr[j][i] = 1;
			}
		}

		for(int i = 2; i < tot_home-2; i++){
			for(int j = 0; j < MAX_ROW; j++){
				if(arr[j][i] == 1){
					if(arr[j][i+2] == 0 && arr[j][i-2] == 0 && arr[j][i+1] == 0 && arr[j][i-1] == 0){
						cnt++;
					}
				}
			}
		}
		cout << "#"<< tc << " " << cnt << "\n";
	}
	return 0;
}