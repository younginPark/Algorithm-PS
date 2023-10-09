#include <iostream>
#include <deque>
#include <queue>
using namespace std;

/*
뱀의 머리를 늘려 다음칸에 위치시킨다.
다음칸에 사과가 있으면 사과 없애고 꼬리 냅두고, 사과가 없으면 꼬리쪽에서 한칸 빠짐

머리가 이동할 때
이동하려는 위치가 격자를 벗어나면 게임 종료
이동하려는 위치가 자기 몸이면 게임 종료

*/

int dy[4] = { -1, 0, +1, 0 };
int dx[4] = { 0, +1, 0, -1 };

int N, K, L;
int board[101][101];
deque<pair<int, int> > snake;
int snake_dir = 1;

struct COMMAND {
    int time;
    char direction;
};
queue<COMMAND> command;

void userInput(){
    cin >> N >> K;
    for(int i = 0; i < K; i++){
        int y, x;
        cin >> y >> x;
        board[y-1][x-1] = 1;
    }
    cin >> L;
    for(int i = 0; i < L; i++){
        COMMAND tmp;
        cin >> tmp.time >> tmp.direction;
        command.push(tmp);
    }
}

int main(){
    userInput();
    snake.push_back(make_pair(0, 0));
    int round = 1;
    while(1){
        int cy = snake.front().first;
        int cx = snake.front().second;
        int ny = cy + dy[snake_dir];
        int nx = cx + dx[snake_dir];
        if(ny < 0 || nx < 0 || ny >= N || nx >= N){
            break;
        }
        int stop = 0;
        for(int i = 0; i < snake.size(); i++){
            if(snake[i].first == ny && snake[i].second == nx){
                stop = 1;
                break;
            }
        }
        if(stop == 1){
            break;
        }
        if(board[ny][nx] == 1){
            board[ny][nx] = 0;
            snake.push_front(make_pair(ny, nx));
        }
        else{
            snake.push_front(make_pair(ny, nx));
            snake.pop_back();
        }

        if(round == command.front().time){
            char changeDir = command.front().direction;
            command.pop();
            if(changeDir == 'L'){
                snake_dir = ((snake_dir - 1) + 4) % 4;
            }
            else if(changeDir == 'D'){
                snake_dir = ((snake_dir + 1) + 4) % 4;
            }
        }
        round++;
    }
    cout << round;
    return 0;
}