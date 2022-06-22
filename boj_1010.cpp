#include <iostream>
using namespace std;

long long arr[35][35];
int T;

void combination() {
	for (int i = 1; i < 30; i++) {
		arr[i][i] = 1;
		arr[i][1] = i;
	}
	for (int i = 2; i < 30; i++) {
		for (int j = 2; j < 30; j++) {
			if (i > j) {
				arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
				// cout << arr[i][j] << " ";
			}
		}
	}

}

int main() {
	combination();
	cin >> T;
	for (int i = 0; i < T; i++) {
		int N, M;
		cin >> N >> M;
		cout << arr[M][N] << "\n";
	}

	return 0;
}