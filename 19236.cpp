#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N = 4, M = 4;
int stop = 0;
int dirY[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dirX[8] = {0, -1, -1, -1, 0, 1, 1, 1};

struct FISH{
    int dir, x, y, order;
};

struct SHARK{
    int dir, x, y;
    int total = 0;
};

FISH map[5][5];
vector<FISH> fish_vec;
SHARK shark;

bool cmpOrder(FISH& fish1, FISH& fish2)
{
    return fish1.order < fish2.order;
}

void fish_move(){
    sort(fish_vec.begin(), fish_vec.end(), cmpOrder);

    int size = fish_vec.size();

    for(int i = 0; i < size; i++){
        FISH moving;
        FISH next;
        int change = 0;
        int count = 0;
        moving = fish_vec[i];

        while(change == 0){
            count++;
            if(0 <= moving.y + dirY[moving.dir]  && moving.y + dirY[moving.dir] < N 
            && 0 <= moving.x + dirX[moving.dir]  && moving.x + dirX[moving.dir] < M
            && map[moving.y + dirY[moving.dir]][moving.x + dirX[moving.dir]].order != -1
            && map[moving.y + dirY[moving.dir]][moving.x + dirX[moving.dir]].order != -2){
                change = 1;
                for(int j = 0; j < size; j++){
                    if(fish_vec[j].y == moving.y + dirY[moving.dir] && fish_vec[j].x == moving.x + dirX[moving.dir]){
                        //벡터에서 변경
                        swap(fish_vec[i], fish_vec[j]);
                        sort(fish_vec.begin(), fish_vec.end(), cmpOrder);
                        break;
                    }
                    swap(map[moving.y][moving.x], map[moving.y + dirY[moving.dir]][moving.x + dirX[moving.dir]]);
                }
            }
            else if(0 <= moving.y + dirY[moving.dir]  && moving.y + dirY[moving.dir] < N 
            && 0 <= moving.x + dirX[moving.dir]  && moving.x + dirX[moving.dir] < M
            && map[moving.y + dirY[moving.dir]][moving.x + dirX[moving.dir]].order != -1
            && map[moving.y + dirY[moving.dir]][moving.x + dirX[moving.dir]].order == -2){
                change = 1;
                fish_vec[i].y = map[moving.y + dirY[moving.dir]][moving.x + dirX[moving.dir]].y;
                fish_vec[i].x = map[moving.y + dirY[moving.dir]][moving.x + dirX[moving.dir]].x;
                swap(map[moving.y][moving.x], map[moving.y + dirY[moving.dir]][moving.x + dirX[moving.dir]]);
            }
            else{
                moving.dir++;
                if(count == 8){
                    break;
                }
            }
        }
    }
}

void shark_eat(){
    int change = 0;
    map[shark.y][shark.x].order = -2;
    FISH max;
    max.y = 0;
    max.x = 0;
    max.order = 0;
    max.dir = 0;
    SHARK moving;
    moving = shark;
    while(1){
        moving.y += dirY[moving.dir];
        moving.x += dirX[moving.dir];
        if(map[moving.y][moving.x].order != 100 
        && 0 <= moving.y && moving.y < N && 0 <= moving.x && moving.x < M){
            if(map[moving.y][moving.x].order > max.order){
                max = map[moving.y][moving.x];
                change = 1;
            }
            else{
                continue;
            }
        }
        else{
            stop = 1;
            break;
        }
    }
    if(change == 1){
        for(auto i = fish_vec.begin(); i < fish_vec.end(); i++){
            if((*i).x == max.x && (*i).y == max.y){
                cout << "erase: " <<(*i).order << "\n";
                fish_vec.erase(i);
                break;
            }
        }
        shark.y = max.y;
        shark.x = max.x;
        shark.dir = max.dir;
        shark.total += max.order;
        map[max.y][max.x].order = -1;
    }
}


int main(){
    for(int y = 0; y < N; y++){
        for(int x = 0; x < M; x++){
            cin >> map[y][x].order;
            cin >> map[y][x].dir;
            map[y][x].y = y;
            map[y][x].x = x;
            if(y == 0 && x == 0){
                shark.y = 0, shark.x = 0;
                shark.dir = map[y][x].dir;
                shark.total = map[y][x].order;
                map[y][x].order = -1;
            }
            else{
                FISH fish_tmp;
                fish_tmp.dir = map[y][x].dir;
                fish_tmp.order = map[y][x].order;
                fish_tmp.y = map[y][x].y;
                fish_tmp.x = map[y][x].x;
                fish_vec.push_back(fish_tmp);
            }
        }
    }

    while(stop == 0){
        fish_move();
        shark_eat();
    }
    cout << shark.total;

    return 0;
}