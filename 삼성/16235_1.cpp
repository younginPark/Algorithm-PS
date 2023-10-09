#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

int N, M, K;
int ans = 0;
vector<int> ground[11][11]; //x, y, 나이
int ground_feed[11][11];
int feed[11][11];

void springAndSummer(){
    int energy = 0;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            vector<int> tmp;
            int die_old = 0;
            sort(ground[i][j].begin(), ground[i][j].end());
            int tree_cnt = ground[i][j].size();
            for(int k = 0; k < tree_cnt; k++){
                if(ground_feed[i][j] - ground[i][j][k] >= 0){
                    ground_feed[i][j] -= ground[i][j][k];
                    tmp.push_back(ground[i][j][k]+1);
                }
                else{
                    die_old += ground[i][j][k] / 2;
                }
            }
            ground[i][j].clear();
            for(int k = 0; k < tmp.size(); k++){
                ground[i][j].push_back(tmp[k]);
            }
            ground_feed[i][j] += die_old;
        }
    }
}

void fall(){
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            for(int k = 0; k < ground[i][j].size(); k++){
                if(ground[i][j][k] % 5 == 0){
                    for(int l = 0; l < 8; l++){
                        int newX = i + dx[l];
                        int newY = j + dy[l];
                        if(newX >= 1 && newX <= N && newY >= 1 && newY <= N){
                            ground[newX][newY].push_back(1);
                        }
                    }
                }
            }
        }
    }
}

void winter(){
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            ground_feed[i][j] += feed[i][j];
        }
    }
}

int main(){
    scanf("%d %d %d", &N, &M, &K);
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            scanf("%d", &feed[i][j]);
            ground_feed[i][j] = 5;
        }
    }
    for(int i = 0; i < M; i++){
        int r, c, old;
        scanf("%d %d %d", &r, &c, &old);
        ground[r][c].push_back(old);
    }

    for(int i = 0 ; i < K; i++){
        springAndSummer();
        fall();
        winter();
    }

    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            ans += ground[i][j].size();
        }
    }
    printf("%d", ans);

    return 0;
}