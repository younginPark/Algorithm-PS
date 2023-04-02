#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>
#include <sstream>
#include <utility>
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(NULL); cout.tie(NULL);
#define RANGE_CHECK(y,x,n) (0<= y && y < n && 0<= x && x < n)
using namespace std;


typedef pair<int,int> P;
bool visited[900];
bool visitedArr[31][31];
int dy[4] = {-1,1,0,0};
int dx[4] = {0,0,-1,1};

int artScore;
int ans;
typedef struct GroupInfo{

    int cnt;
    int number;
    vector<P> coordinate;

}GroupInfo;


int N;
int arr[31][31];


void print(){
    
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j <N ; j++){
            cout << arr[i][j] << " ";
        }
        cout << '\n';
    }
    
    
}

void Input(){
    cin >> N;
    for(int i = 0 ; i < N ; i++){
        
        for(int j = 0 ; j < N ; j++){
            cin >> arr[i][j];
        }

    }
}

void crossRotate(){
    int tmp[31][31];
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++){
            if(i == N/2 || j == N/2){
                tmp[N-j-1][i] = arr[i][j];
            }
        }
    }
    
    
   for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++){
            if(i == N/2 || j == N/2)
                arr[i][j] = tmp[i][j];

            }

        }
}
    



void diviedSqureRotate(int y, int x){

    int tmp[31][31];

    int size = N/2;

    
    for(int i = 0 ; i < N/2 ;i++){
        
        for(int j = 0 ; j < N/2 ; j++){
            
            tmp[j][size- i - 1] = arr[i+y][j+x];
        }
    }
    
    for(int i = 0 ; i < N/2 ;i++){
        
        for(int j = 0 ; j < N/2 ; j++){
            
            arr[i+y][j+x] = tmp[i][j];
        }
    }
    
    
}
void squareRotate(){
    
    diviedSqureRotate(0,0);
    diviedSqureRotate(0 ,N/2 + 1);
    diviedSqureRotate(N/2 + 1 ,0);
    diviedSqureRotate(N/2 + 1,N/2 +1);
}

int adjCount(vector<P> & a , vector<P> & b){
    int adjcnt = 0; //인접 갯수 카운팅
    
    for(int i = 0 ; i < a.size(); i++){
        
        int y = a[i].first;
        int x = a[i].second;
        
        for(int j = 0 ; j < 4 ; j++){
            int n_y = y + dy[j];
            int n_x = x + dx[j];
            
            for(int k = 0 ; k < b.size() ; k++){
                
                if(n_y == b[k].first && n_x == b[k].second){ //상하좌우 하나라도 맞닿아있으면 증가
                    adjcnt+=1;
                }

            }

        }

    }

    
    return adjcnt;

}
int calCombi(GroupInfo& a, GroupInfo& b){
    
    int score = 0;
    
    int BeonScore = adjCount(a.coordinate, b.coordinate);
    
    score = (a.cnt + b.cnt) * a.number * b.number * BeonScore;
    
    
    
    return score;


}


void Combi(vector<GroupInfo>& v,int idx ,int size){

    if(size == 2){
        vector<GroupInfo> tmp;
        for(int i = 0 ; i < v.size() ; i++){
            if(visited[i]){
                tmp.push_back(v[i]);
            }


        }

        artScore += calCombi(tmp[0],tmp[1]); // 예술점수 계산

        return;
    }

    for(int i = idx ; i < v.size() ; i++){
        
        if(!visited[i]){
            visited[i] = true;
            Combi(v,i+1,size+1);
            visited[i]= false;
        }
        
    }

}

void dfs(GroupInfo& g,int y,int x){
    
    
    for(int i = 0 ; i < 4 ; i++){
        int n_y = y + dy[i];
        int n_x = x + dx[i];
        
        if(RANGE_CHECK(n_y,n_x,N) &&!visitedArr[n_y][n_x] && arr[n_y][n_x] == g.number){
            visitedArr[n_y][n_x] = true;
            g.cnt +=1;
            g.coordinate.push_back(make_pair(n_y,n_x)); //좌표 모으기
            dfs(g,n_y,n_x);

        }
            

    }

}
 vector<GroupInfo> findGroup(){
    

    vector<GroupInfo> v;
    memset(visitedArr,false,sizeof(visitedArr));
     
     
     
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ;j++){
            
            if(!visitedArr[i][j]){
                visitedArr[i][j] = true;
                GroupInfo g = {0,0,};
                g.coordinate.push_back(make_pair(i,j));
                g.cnt +=1;
                g.number = arr[i][j];
                dfs(g,i,j);
                v.push_back(g); //그룹 생성

            }

        }

    }

    
     
    return v;
    
 }

int calScore(){
    
    vector<GroupInfo> v = findGroup();
    
    artScore = 0;
    
    memset(visited,false,sizeof(visited));
    Combi(v,0,0);

    return artScore;

}

void solve(){
    int Rotate = 3;
    ans = calScore(); //초기 예술점수
    while(Rotate--){

        crossRotate();
        squareRotate();
    
        
        ans+=calScore();
        
    }

    cout << ans << '\n';
}
int main(){
    
    FASTIO

    Input();
    solve();
    return 0;
    
    
}