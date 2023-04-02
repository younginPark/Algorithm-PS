#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int arr[12];
vector <int> op;
int big = -999999999, small = 999999999;
int op_tot = 0;


void dfs(int num_pos, int ret){
	if(num_pos == N){
		//cout << "SAME!!!!!\n";
		if(ret > big){
			big = ret;
		}
		if(ret < small){
			small = ret;
		}
		return;
	}

	for(int j = 0; j < op.size(); j++){
		int now = op[j];
		int value = ret;
		if(now == 1){
			//cout << ret << "," << arr[num_pos] << " ++";
			ret += arr[num_pos];
			//cout << ret << "\n";
			op[j] = -1;
			dfs(num_pos+1, ret);
			ret = value;
			op[j] = now;
		}
		else if(now == 2){
			ret -= arr[num_pos];
			op[j] = -1;
			dfs(num_pos+1, ret);
			ret = value;
			op[j] = now;
		}
		else if(now == 3){
			//cout << ret << "," << arr[num_pos] << " **";
			ret *= arr[num_pos];
			//cout << ret << "\n";
			op[j] = -1;
			dfs(num_pos+1, ret);
			ret = value;
			op[j] = now;
		}
		else if(now == 4){
			ret /= arr[num_pos];
			op[j] = -1;
			dfs(num_pos+1, ret);
			ret = value;
			op[j] = now;
		}
	}

}

int main(){

	cin >> N;
	for(int i = 0; i < N; i++){
		cin >> arr[i];
	}
	for(int i = 1; i <= 4; i++){
		int tmp;
		op_tot += tmp;
		cin >> tmp;
		for(int j = 0; j < tmp; j++){
			op.push_back(i);
		}
	}
	dfs(1, arr[0]);

	cout << big << "\n" << small << "\n";
	return 0;
}