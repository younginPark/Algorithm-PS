#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int N, M;
vector<int> crane; 
vector<int> box;
int ans = 0;

void userInput() {
	cin >> N;
	int tmp;
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		crane.push_back(tmp);
	}

	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> tmp;
		box.push_back(tmp);
	}
	sort(crane.begin(), crane.end(), greater<int>());
	sort(box.begin(), box.end(), greater<int>());
}

void solution() {
	while (!box.empty()) {
		ans++;
		for (int i = 0; i < crane.size(); i++) {
			for (int j = 0; j < box.size(); j++) {
				if (crane[i] >= box[j]) {
					box.erase(box.begin() + j);
					break;
				}
			}
		}
	}
}

int main() {
	userInput();
	if (box[0] > crane[0]) {
		cout << -1;
		return 0;
	}
	solution();
	cout << ans;
	return 0;
}