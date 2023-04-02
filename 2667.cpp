#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int size = 0;
int arr[26][26] = { 0, };
int town[1001] = { 0, };
int cnt = 0, idx = 0;

void dfs(int x, int y){
	arr[x][y] = 5;
	cnt++;

	if(y > 0 && arr[x][y-1] == 1){
		dfs(x,y-1);
	}
	if(x > 0 && arr[x-1][y] == 1){
		dfs(x-1,y);
	}
	if(x < size-1 && arr[x+1][y] == 1){
		dfs(x+1,y);
	}
	if(y < size-1 && arr[x][y+1] == 1){
		dfs(x,y+1);
	}

}


int main(){

	string str1;

	cin >> size;
	for(int i = 0; i < size; i++){
		cin >> str1;
		for(int j = 0; j < size; j++){
			arr[i][j] = str1.at(j) - '0';
		}
	}

	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(arr[i][j] == 1){
				dfs(i,j);
				town[idx] = cnt;
				idx++;
				cnt = 0;
			}
		}
	}

	// for(int i = 0; i < size; i++){
	// 	for(int j = 0; j < size; j++){
	// 		cout << arr[i][j] << " ";
	// 	}
	// 	cout << "\n";
	// }

	sort(town, town+idx);

	cout << idx << "\n";
	for(int i = 0; i < idx; i++){
		cout << town[i] << "\n";
	}




	return 0;
}