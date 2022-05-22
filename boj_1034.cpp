#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main() {
	int K, row, col;
	int ans = -1;
	string arr[50];
	cin >> row >> col;

	for (int i = 0; i < row; i++) {
		cin >> arr[i];
	}

	cin >> K;

	for (int i = 0; i < row; i++) {
		int cnt = 0;
		for (int j = 0; j < col; j++) {
			if (arr[i][j] == '0') {
				cnt++;
			}
		}
		int sum = 0;
		if (cnt <= K && cnt % 2 == K % 2) {
			for (int k = 0; k < row; k++) {
				if (arr[i] == arr[k]) {
					sum++;
				}
			}
		}
		ans = max(sum, ans);
	}
	cout << ans;
	return 0;
}

// 참고 https://ongveloper.tistory.com/172
// 전체열의 경우의 수를 다 보는 것이 아니라 현재 최대로 켤 수 있는 상황을 K에 맞춰보고 조건이 성립되는지 확인
// cnt <= K 는 꺼진 램프의 수가 K보다 작아야 K를 통해서 다 켤 수 있음
// cnt % 2 == K % 2 는 껐다 켜는걸 한 스위치에서 여러번 할 수 있으니까 
// 꺼진 램프의 개수를 껐다 켜는 횟수가 총 스위치 껐다 켜는 횟수의 짝수/홀수가 같아야 함