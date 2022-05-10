#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

int dy[4] = { -1, 0, +1, 0 };
int dx[4] = { 0, -1, 0, +1 };

int R, C;
char board[25][25];
int visited[25][25];
int alphabet[27];
int ans = -1;

void userInput() {
	cin >> R >> C;
	for (int i = 0; i < R; i++) {
		string str1;
		cin >> str1;
		for (int j = 0; j < str1.length(); j++) {
			board[i][j] = str1[j];
		}
	}
}

void dfs(int y, int x, int cnt) {
	if (cnt > ans) {
		ans = cnt;
	}
	for (int dir = 0; dir < 4; dir++) {
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		if (ny < 0 || nx < 0 || ny >= R || nx >= C) {
			continue;
		}
		if (visited[ny][nx] == 1 || alphabet[board[ny][nx] - 65] == 1) {
			continue;
		}
		visited[ny][nx] = 1;
		alphabet[board[ny][nx] - 65] = 1;
		dfs(ny, nx, cnt + 1);
		visited[ny][nx] = 0;
		alphabet[board[ny][nx] - 65] = 0;
	}
}

int main() {
	userInput();
	visited[0][0] = 1;
	alphabet[board[0][0] - 65] = 1;
	dfs(0, 0, 1);
	cout << ans;
	return 0;
}