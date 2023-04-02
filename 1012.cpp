#include <iostream>
using namespace std;

int arr[51][51] = { 0, };
int w, h;

void dfs(int j, int k){
	arr[j][k] = 5;
	if(j > 0 && arr[j-1][k] == 1){
		dfs(j-1, k);
	}
	if(k > 0 && arr[j][k-1] == 1){
		dfs(j, k-1);
	}
	if(j < h-1 && arr[j+1][k] == 1){
		dfs(j+1, k);
	}
	if(k < w-1 && arr[j][k+1] == 1){
		dfs(j, k+1);
	}
}

int main(){
	int tc;
	int num;
	int x, y;
	int result = 0;

	cin >> tc;
	for(int i = 0; i < tc; i++){
		cin >> w >> h >> num;
		for(int j = 0; j < num; j++){
			cin >> x >> y;
			arr[y][x] = 1;
		}

		for(int j = 0; j < h; j++){ //8
			for(int k = 0; k < w; k++){ //10
				if(arr[j][k] == 1){
					dfs(j,k);
					result++;
				}
			}
		}
		cout << result << "\n";
		result = 0;
		for(int j = 0; j < h; j++){ //8
			for(int k = 0; k < w; k++){ //10
				arr[j][k] = 0;
			}
		}
	}//end of tc

	return 0;
}