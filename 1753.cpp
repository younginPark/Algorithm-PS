#include <iostream>
#include <vector>
#include <queue>
#define MAX 20001
#define INF 987654321
using namespace std;

int V, E, K;
vector<pair<int, int> > graph[MAX];

vector<int> dijkstra(int start, int vertex){
    vector<int> distance(vertex+1, INF); //시작점과의 거리
    distance[start] = 0; //시작점 자기 자신과는 거리 0

    priority_queue<pair<int, int> > pq;
    pq.push(make_pair(0, start)); //거리는 0이고 시작은 시작점부터

    while(!pq.empty()){
        int cost = -pq.top().first; //start부터 현재노드까지의 거리
        int curVertex = pq.top().second; //현재 노드
        pq.pop();

        if(distance[curVertex] < cost){ //이미 기록된 거리보다 크면 패스
            continue;
        }
        for(int i = 0; i < graph[curVertex].size(); i++){ //이웃 다 둘러보기
            int neighbor = graph[curVertex][i].first; //curVertex의 이웃
            int neighborDistance = cost + graph[curVertex][i].second; //이웃과의 거리

            if(distance[neighbor] > neighborDistance){ //현재 거리보다 더 작으면 갱신
                distance[neighbor] = neighborDistance;
                pq.push(make_pair(-neighborDistance, neighbor)); //이웃과의 최소거리와 그 이웃
            }
        }
    }

    return distance;
}

int main(){
    scanf("%d %d %d", &V, &E, &K);
    for(int i = 0; i < E; i++){
        int src, dest, cost;
        scanf("%d %d %d", &src, &dest, &cost);
        graph[src].push_back(make_pair(dest, cost));
    }
    vector<int> result = dijkstra(K, V);
    for(int i = 1; i <= V; i++){
        if(result[i] == INF){
            printf("INF\n");
        }
        else{
            printf("%d\n", result[i]);
        }
    }
    return 0;
}