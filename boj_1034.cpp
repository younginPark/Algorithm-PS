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

// ���� https://ongveloper.tistory.com/172
// ��ü���� ����� ���� �� ���� ���� �ƴ϶� ���� �ִ�� �� �� �ִ� ��Ȳ�� K�� ���纸�� ������ �����Ǵ��� Ȯ��
// cnt <= K �� ���� ������ ���� K���� �۾ƾ� K�� ���ؼ� �� �� �� ����
// cnt % 2 == K % 2 �� ���� �Ѵ°� �� ����ġ���� ������ �� �� �����ϱ� 
// ���� ������ ������ ���� �Ѵ� Ƚ���� �� ����ġ ���� �Ѵ� Ƚ���� ¦��/Ȧ���� ���ƾ� ��