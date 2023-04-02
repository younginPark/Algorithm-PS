#include <iostream>
#include <queue>
using namespace std;

int result = -1;
int caveX = 0;
int caveY = 0;
int xx[4] = { 0, 0, -1, 1};
int yy[4] = { -1, 1, 0, 0};
int r, c;
pair<char,int> arr[51][51];
pair<char,int> water[51][51];
queue <pair<pair<int,int>,int > > q; //위치(y,x) , (몇분째인지) 
queue <pair<pair<int,int>,int > > water_q; //위치(y,x) , (몇분째인지)

void water_bfs(){

    while(!water_q.empty()){
        int fronty = water_q.front().first.first;
        int frontx = water_q.front().first.second;
        int time = water_q.front().second;
        water_q.pop();


        for(int i = 0; i < 4; i++){
            int newY = fronty+yy[i];
            int newX = frontx+xx[i];
            if(newY > 0 && newY <= r && newX > 0 && newX <= c && water[newY][newX].first == '.'){
                water_q.push(make_pair(make_pair(newY, newX), time+1));
                water[newY][newX].first = '*';
                water[newY][newX].second = time+1;
            }
        }
    }
}

void bfs(){
    while(!q.empty()){
        int fronty = q.front().first.first;
        int frontx = q.front().first.second;
        int time = q.front().second;
        q.pop();

        if(frontx == caveX && fronty == caveY){
            result = time;
            break;
        }

        for(int i = 0; i < 4; i++){
            int newY = fronty+yy[i];
            int newX = frontx+xx[i];
            if(newY > 0 && newY <= r && newX > 0 && newX <= c){
                if(water[newY][newX].second > time+1 && arr[newY][newX].first == '.'){
                    q.push(make_pair(make_pair(newY, newX), time+1));
                    arr[newY][newX].first = 'S';
                    arr[newY][newX].second = time+1;
                }
                else if(water[newY][newX].second == 0 && arr[newY][newX].first == '.'){
                    q.push(make_pair(make_pair(newY, newX), time+1));
                    arr[newY][newX].first = 'S';
                    arr[newY][newX].second = time+1;
                }
                else if(arr[newY][newX].first == 'D'){
                    q.push(make_pair(make_pair(newY, newX), time+1));
                    arr[newY][newX].first = 'S';
                    arr[newY][newX].second = time+1;
                }
            }
        }
    }
}

int main(){
    cin >> r >> c;
    for(int i = 1; i <= r; i++){
        for(int j = 1; j <= c; j++){
            char tmp;
            cin >> tmp;

            if(tmp == 'D'){
                caveY = i;
                caveX = j;
            }

            if(tmp == '*'){
                water[i][j] = make_pair(tmp, 0);
                water_q.push(make_pair(make_pair(i,j),0));
            }
            else if(tmp == 'S'){
                arr[i][j] = make_pair(tmp, 0);
                water[i][j] = make_pair('.', 0);
                q.push(make_pair(make_pair(i,j),0));
            }
            else{
                water[i][j] = make_pair(tmp, 0);
                arr[i][j] = make_pair(tmp, 0);
            }
        }
    }

    water_bfs();
    bfs();
    if(result == -1){
        cout << "KAKTUS";
    }
    else{
        cout << result;
    }

    
    return 0;

}