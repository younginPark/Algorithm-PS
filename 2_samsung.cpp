#include <iostream>
#include <algorithm>
#include <string>

using namespace std;
int n;
int ans;

void dfs(int cnt, string s, int a){
	if(cnt == n){ //주어진 횟수만큼 바꿨으면 종료
		int temp = stoi(s);//숫자인데 문자열로 받아버려서
		if(temp > ans){ //제일 큰 숫자찾는거니까
			ans = temp;
		}
		return;
	}

	int sz = s.size();
	for(int i = a; i < sz-1; i++){
		for(int j = i+1; j < sz; j++){
			swap(s[i], s[j]);//근데 왜 바꾸지??????
			dfs(cnt+1, s, i); //한번 바꿨으니까 cnt++
			swap(s[i], s[j]);
		}
	}

}

int main(){

	int T = 0;
	cin >> T;

	for(int i = 1; i <= T; i++){
		string s;
		cin >> s >> n;
		ans = 0;
		if(n > s.size()){
			n = s.size();
		}

		dfs(0, s, 0);

		cout << '#' << i << ' ' << ans << "\n"; 
	}

	return 0;
}