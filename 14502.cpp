#include <iostream>
#include <queue>
#include <vector>
#define MAX_NUM 9
using namespace std;

int xx[4] = { 0, 0, -1, 1};
int yy[4] = { -1, 1, 0, 0};
int r, c;
int arr[MAX_NUM][MAX_NUM] = { 0, };
int arr_copy[MAX_NUM][MAX_NUM] = { 0, };
int ans = 0;
vector<pair<int, int> > vec;

void bfs(){
	queue<pair<int, int> > q;
	for(int i = 0; i < vec.size(); i++){
		q.push(make_pair(vec[i].first, vec[i].second));
	}

	while(!q.empty()){
		int frontY = q.front().first;
		int frontX = q.front().second;
		q.pop();

		for(int i = 0; i < 4; i++){
			int newY = frontY + yy[i];
			int newX = frontX + xx[i];

			if(newY < 0 || newY >= r || newX < 0 || newX >= c){
				continue;
			}
			else{
				if(arr_copy[newY][newX] == 0){
					arr_copy[newY][newX] = 2;
					q.push(make_pair(newY, newX));
				}
			}
		}
	}
	int result = 0;
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			if(arr_copy[i][j] == 0){
				result++;
			}
		}
	}

	if(ans < result){
		ans = result;
	}
	return;
}

void copy(){
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			arr_copy[i][j] = arr[i][j];
		}
	}
	return;
}

void wall(int cnt){
	if(cnt == 3){
		copy();
		bfs();
		return;
	}

	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			if(arr[i][j] == 0){
				arr[i][j] = 1;
				wall(cnt+1);
				arr[i][j] = 0;
			}
		}
	}
}

int main(){

	cin >> r >> c;
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			cin >> arr[i][j];
			if(arr[i][j] == 2){
				vec.push_back(make_pair(i, j));
			}
		}
	}

	wall(0);

	cout << ans;
	return 0;
}