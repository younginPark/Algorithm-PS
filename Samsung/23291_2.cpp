#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>

#define MAX 110
using namespace std;

int dx[2] = { 0, -1 };
int dy[2] = { 1, 0 };

int N, K;
deque<int> bowl[MAX];

void input(){
    cin >> N >> K;
    for(int i = 0; i < N; i++){
        int tmp;
        cin >> tmp;
        bowl[0].push_back(tmp);
    }
}

bool check(){
    int minFish = 987654321;
    int maxFish = -987654321;
    for(int i = 0; i < bowl[0].size(); i++){
        minFish = min(minFish, bowl[0][i]);
        maxFish = max(maxFish, bowl[0][i]);
    }

    if((maxFish-minFish) <= K){
        return true;
    }
    return false;
}

void addFish(){
    int minFish = 987654321;
    vector<int> idxV;
    for(int i = 0; i < bowl[0].size(); i++){
        if(bowl[0][i] < minFish){
            minFish = bowl[0][i];
            idxV.clear();
            idxV.push_back(i);
        }
        else if(bowl[0][i] == minFish){
            idxV.push_back(i);
        }
    }

    for(int i = 0; i < idxV.size(); i++){
        bowl[0][idxV[i]]++;
    }
}

bool canBuild(int w, int h){
    if(bowl[0].size() - w < h){
        return false;
    }
    return true;
}

int buildBowl(){
    int width = 1;
    int height = 1;
    bool flag = false;

    while(1){
        //  높이가 놓을 가로의 길이보다 더 크면 어항 바닥 비는 곳 생기므로 안됨
        if(canBuild(width, height) == false){
            break;
        }
        // 넣어주기
        int tmpWidth = width;
        for(int i = 0; i < width; i++, tmpWidth--){
            for(int j = 0; j < height; j++){
                bowl[tmpWidth].push_back(bowl[j][i]);
            }
        }
        // 위에 올려준것들 앞에 그대로 남아있으므로 pop
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                bowl[i].pop_front();
            }
        }

        if(flag == false){
            height++;
            flag = true;
        }
        else{
            width++;
            flag = false;
        }
    }

    return height;
}

void adjustFish(int height){
    deque<int> tmpbowl[MAX];
    for(int i = 0; i < height; i++){
        tmpbowl[i] = bowl[i];
    }
    for(int i = height-1; i >= 0; i--){
        for(int j = 0; j < bowl[i].size(); j++){
            int x = i;
            int y = j;
            int num = bowl[x][y];
            for(int k = 0; k< 2; k++){
                int nx = x + dx[k];
                int ny = y + dy[k];
                if(nx >= 0 && ny < bowl[i].size()){
                    int num2 = bowl[nx][ny];
                    int diff = abs(num - num2) / 5;
                    if(diff > 0){
                        if(num > num2){
                            tmpbowl[x][y] -= diff;
                            tmpbowl[nx][ny] += diff;
                        }
                        else{
                            tmpbowl[x][y] += diff;
                            tmpbowl[nx][ny] -= diff;
                        }
                    }
                }
            }
        }
    }
    for(int i = 0; i < height; i++){
        bowl[i] = tmpbowl[i];
    }

}

void spreadBowl(int height){
    int width = bowl[height-1].size();
    int size = bowl[0].size();
    // 젤 왼쪽부터 밑에서부터 하나씩 0번째꺼에 밀어넣음
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            bowl[0].push_back(bowl[j][i]);
        }
    }
    // 2층 이상 어항들은 바로 클리어
    for(int i = 1; i < height; i++){
        bowl[i].clear();
    }
    // 1층에 기존에 있던 것들 중에서 뒤에 펼쳐져서 들어간거 말고 나머지 것들을 또다시 1층에 넣어줌
    for(int i = width; i < size; i++){
        bowl[0].push_back(bowl[0][i]);
    }
    // 기존 것들을 싹 pop
    for(int i = 0; i < size; i++){
        bowl[0].pop_front();
    }
}

void buildBowl2(){
    int n = bowl[0].size();
    // 앞에 절반 2층 거꾸로 쌓음 (거꾸로니까 push_front, 정방향이였으면 push_back)
    for(int i = 0; i < n/2; i++){
        bowl[1].push_front(bowl[0][i]);
    }
    // 앞에 절반 2층에 쌓았으니까 pop
    for(int i = 0; i < n/2; i++){
        bowl[0].pop_front();
    }
    // 빈의반 다시 거꾸로 쌓음
    for(int i = 0; i < n/4; i++){
        bowl[2].push_front(bowl[1][i]);
        bowl[3].push_front(bowl[0][i]);
    }
    for(int i = 0; i < n/4; i++){
        bowl[0].pop_front();
        bowl[1].pop_front();
    }
}

void solution(){
    int answer = 0;
    while(1) {
        if(check() == true){
            cout << answer << "\n";
            break;
        }
        addFish();
        int height = buildBowl();
        adjustFish(height);
        spreadBowl(height);
        buildBowl2();
        adjustFish(4);
        spreadBowl(4);
        answer++;
    }
}

int main(){
    input();
    solution();
    return 0;
}