#include <iostream>
#include <queue>
#define MAX_ARR 21
#define NUM 5
using namespace std;

int N = 0;
int ans = 0;
int arr[MAX_ARR][MAX_ARR] = { 0, };

void move(int num){
	queue<int> q;
	if(num == 0){
		for(int i = 0; i < N; i++){
			for(int j = 0; j < N; j++){
				if(arr[i][j] != 0){
					q.push(arr[i][j]);
				}
				arr[i][j] = 0;
			}
			int idx = 0; //시작하는 쪽이 미는 방향의 맨 앞쪽이여야함, 누적되어서 더해져야하니까
			while(!q.empty()){
				int data = q.front();
				q.pop();
				if(arr[i][idx] == 0){ //다음꺼가 합쳐질 수도 있으니가 idx++ 안함
					arr[i][idx] = data;
				}
				else if(arr[i][idx] == data){
					arr[i][idx] *= 2; //한번 합쳤으니까 ++ (한번 합쳐진건 다시 안합쳐짐)
					idx++;
				}
				else{//딜리서 합쳐질 수 없으면 ++ 해서 해줌
					idx++;
					arr[i][idx] = data;
				}
			}
		}
	}
	else if(num == 1){
		for(int i = 0; i < N; i++){
			for(int j = N-1; j >= 0; j--){
				if(arr[i][j] != 0){
					q.push(arr[i][j]);
				}
				arr[i][j] = 0;
			}
			int idx = N-1;
			while(!q.empty()){
				int data = q.front();
				q.pop();
				if(arr[i][idx] == 0){
					arr[i][idx] = data;
				}
				else if(arr[i][idx] == data){
					arr[i][idx] *= 2;
					idx--;
				}
				else{
					idx--;
					arr[i][idx] = data;
				}
			}
		}

	}
	else if(num == 2){
		for(int i = 0; i < N; i++){
			for(int j = 0; j < N; j++){
				if(arr[j][i] != 0){
					q.push(arr[j][i]);
				} 
				arr[j][i] = 0;
			}
			int idx = 0;
			while(!q.empty()){
				int data = q.front();
				q.pop();
				if(arr[idx][i] == 0){ //idx++안함
					arr[idx][i] = data;
				}
				else if(arr[idx][i] == data){ //넣어주고 idx함
					arr[idx][i] *= 2;
					idx++;
				}
				else{ //idx해서 다음칸에 넣어줌
					idx++;
					arr[idx][i] = data;
				}
			}
		}
	}
	else if(num == 3){
		for(int i = 0; i < N; i++){
			for(int j = N-1; j >= 0; j--){
				if(arr[j][i] != 0){
					q.push(arr[j][i]);
				}
				arr[j][i] = 0;
			}
			int idx = N-1;
			while(!q.empty()){
				int data = q.front();
				q.pop();
				if(arr[idx][i] == 0){
					arr[idx][i] = data;
				}
				else if(arr[idx][i] == data){
					arr[idx][i] *= 2;
					idx--;
				}
				else{
					idx--;
					arr[idx][i] = data;
				}
			}
		}
	}

}

void dfs(int cnt){
	if(cnt == NUM){
		for(int i = 0; i < N; i++){
			for(int j = 0; j < N; j++){
				if(ans < arr[i][j]){
					ans = arr[i][j];
				}
			}
		}
		return;
	}
	int copy_arr[MAX_ARR][MAX_ARR] = { 0, };
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			copy_arr[i][j] = arr[i][j];
		}
	}
	for(int i = 0; i < 4; i++){
		move(i);
		dfs(cnt+1); //중복 순열이니까 한번 움직이고 dfs로 넣고

		for(int i = 0; i < N; i++){
			for(int j = 0; j < N; j++){
				arr[i][j] = copy_arr[i][j];
			}
		}

	}

}

int main(){

	cin >> N;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			cin >> arr[i][j];
		}
	}

	dfs(0);
	cout << ans;

	return 0;
}