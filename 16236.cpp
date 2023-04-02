#include <iostream>
#include <queue>
using namespace std;

struct SHARK{
	int y, x, time;
};

int N;
int map[20][20];

int shark_size, shark_eat;
SHARK shark;

int dy[4] = { 0, 0, -1, 1};
int dx[4] = { -1, 1, 0, 0};

int main(){
	cin >> N;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			cin >> map[i][j];
			if(map[i][j] == 9){
				shark.y = i, shark.x = j, shark.time = 0;
				shark_size = 2, shark_eat = 0;
				map[i][j] = 0;
			}
		}
	}//입력 끝

	bool is_update = true;
	while(is_update){
		is_update = false;

		bool visited[20][20] = { false, };
		queue<SHARK> q;
		visited[shark.y][shark.x] = true;
		q.push(shark);//처음 아기 상어 q에 넣어줌

		SHARK candi;
		candi.y = 20, candi.time = -1;

		while(!q.empty()){
			SHARK cur = q.front(); q.pop();

			//업데이트가 이루어졌으면서 현재 값보다 candi가 작으면 break하고 is_update하러)
			if(candi.time != -1 && candi.time < cur.time){
				break;
			}

			if(map[cur.y][cur.x] < shark_size && map[cur.y][cur.x] != 0){//먹을 수 있는 물고기 발견
				is_update = true;
				if(candi.y > cur.y || (candi.y == cur.y && candi.x > cur.x)){
					candi = cur;
				}
			}

			for(int dir = 0; dir < 4; dir++){//작거나 같은거 4방향 q에 push
				SHARK next;
				next.y = cur.y + dy[dir];
				next.x = cur.x + dx[dir];
				next.time = cur.time + 1;

				if(next.y < 0 || next.y >= N || next.x < 0 || next.x >= N){
					continue;
				}
				if(visited[next.y][next.x] == false && shark_size >= map[next.y][next.x]){
					visited[next.y][next.x] = true;
					q.push(next);
				}
			}
		}
		if(is_update){
			shark = candi;
			shark_eat++;
			if(shark_eat == shark_size){
				shark_size++;
				shark_eat = 0;
			}
			map[shark.y][shark.x] = 0;
		}
	}
	cout << shark.time;
	return 0;
}