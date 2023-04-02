#include <iostream>
#define NUM 101
using namespace std;

int xx[4] = { 0, 1, 0, -1}; //북동남서
int yy[4] = { -1, 0, 1, 0};

struct SNAKE{
    int head_x, head_y, tail_x, tail_y, dir, 
    dir_idx, tail_now;
};

int main(){

    int sec = 0; //결과 초
    int map_size = 0; //배열 사이즈
    int map[NUM][NUM] = { 0, }; //배열
    int apple_num = 0; //사과개수
    int dir_num = 0, dir_idx = 0; //방향 변하는 지점 개수, 그 개수 세는 변수
    int dir_time[NUM] = { 0, }; //방향 변하는 시간 언제인지
    char dir_info[NUM]; //그 시간에 어느 방향으로 바뀌는지

    int tail_arrX[101] = { 0, }; //꼬리 방향 바뀌는 지점 X
    int tail_arrY[101] = { 0, }; //꼬리 방향 바뀌는 지점 Y
    int tail_arrIdx = 0; //배열에 넣을 때 쓸 인덱스
    int tail_dir[101] = { 0, }; //이 지점에서 어떤 방향으로 바뀌는지 

    tail_dir[0] = 1;

    cin >> map_size >> apple_num;
    for(int i = 0; i < apple_num; i++){
        int tmp_x = 0, tmp_y = 0;
        cin >> tmp_y >> tmp_x;
        map[tmp_y][tmp_x] = 1;
    }
    cin >> dir_num;
    for(int i = 0; i < dir_num; i++){
        cin >> dir_time[i] >> dir_info[i];
    } //입력 끝


    SNAKE snake;
    snake.head_x = 1; //머리 위치 X
    snake.head_y = 1; //머리 위치 Y
    snake.tail_x = 1; //꼬리 위치 X
    snake.tail_y = 1; //꼬리 위치 Y
    snake.dir = 1; //동쪽
    snake.tail_now = 0; //현재 테일의 인덱스 y

    while(dir_idx <= dir_num){
        sec++;
        //1,1부터 움직이기
        if(map[snake.head_y+yy[snake.dir]][snake.head_x+xx[snake.dir]] == 2 
        || snake.head_y+yy[snake.dir] <= 0 || snake.head_y+yy[snake.dir] > map_size 
        || snake.head_x+xx[snake.dir] <= 0 || snake.head_x+xx[snake.dir] > map_size){
            cout << sec;
            break;
        }
        else if(map[snake.head_y+yy[snake.dir]][snake.head_x+xx[snake.dir]] == 1){ //사과가 있따
            map[snake.head_y+yy[snake.dir]][snake.head_x+xx[snake.dir]] = 2; //뱀몸통있다는표시
            snake.head_x += xx[snake.dir]; //머리만 이동하고 꼬리는 그대로
            snake.head_y += yy[snake.dir];
        }
        else if(map[snake.head_y+yy[snake.dir]][snake.head_x+xx[snake.dir]] == 0){ //사과 없음
            map[snake.head_y+yy[snake.dir]][snake.head_x+xx[snake.dir]] = 2;
            snake.head_x += xx[snake.dir];
            snake.head_y += yy[snake.dir];

            map[snake.tail_y][snake.tail_x] = 0;
            //머리 이동한만큼 꼬리도 따라 이동하기
            if(snake.tail_x == tail_arrX[snake.tail_now] && snake.tail_y == tail_arrY[snake.tail_now]){
                snake.tail_now++;
            }
            snake.tail_x += xx[tail_dir[snake.tail_now]];
            snake.tail_y += yy[tail_dir[snake.tail_now]];
        }

        if(sec == dir_time[dir_idx]){
            if(dir_info[dir_idx] == 'L'){
                snake.dir = (snake.dir + 3) % 4;
            }
            else if(dir_info[dir_idx] == 'D'){
                snake.dir = (snake.dir + 1) % 4;
            }
            dir_idx++;
            tail_arrX[tail_arrIdx] = snake.head_x;
            tail_arrY[tail_arrIdx] = snake.head_y;
            tail_dir[tail_arrIdx+1] = snake.dir;
            tail_arrIdx++;
        }
    }

    return 0;
}