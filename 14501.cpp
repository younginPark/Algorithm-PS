#include <iostream>
#include <algorithm>
#define MAX_NUM 16
using namespace std;

int N = 0;
int ans = 0;
int result = 0, day = 0;
int term[MAX_NUM] = { 0, };
int pay[MAX_NUM] = { 0, };

void dfs(int day, int pay_tot, int recent_pay){
	if(day == N){
		ans = max(ans, pay_tot);
		return;
	}
	else if(day > N){
		ans = max(ans, pay_tot-recent_pay);
		return;
	}

	for(int i = day; i <= N; i++){
		dfs(i+term[i], pay_tot+pay[i], pay[i]);
	}
}

int main(){
	cin >> N;
	for(int i = 0; i < N; i++){
		cin >> term[i] >> pay[i];
	}
	dfs(0, 0, 0);
	cout << ans;
	return 0;
}