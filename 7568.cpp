#include <iostream>
using namespace std;

int main(){

	int tc = 0;
	int weight[51] = { 0, };
	int height[51] = { 0, };
	int rank[51] = { 0, };
	cin >> tc;
	for(int i = 0; i < tc; i++){
		cin >> weight[i] >> height[i];
	}

	for(int i = 0; i < tc-1; i++){
		for(int j = i+1; j < tc; j++){
			if(weight[i] > weight[j] && height[i] > height[j]){
				rank[j]++;
			}
			else if(weight[i] < weight[j] && height[i] < height[j]){
				rank[i]++;
			}
		}
	}

	for(int i = 0; i < tc; i++){
		cout << rank[i]+1 << " ";
	}
	return 0;
}