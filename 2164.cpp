#include <iostream>
#include <queue>
using namespace std;

int main(){
    int N;
    int time = 0;
    queue<int> q;
    cin >> N;
    for(int i = 1; i <= N; i++){
        q.push(i);
    }

    while(!q.empty()){
        if(time == 0){
            time = 1;
            int now = q.front();
            q.pop();
            if(q.empty()){
                cout << now;
                break;
            }
        }
        else if(time == 1){
            time = 0;
            int now = q.front();
            q.pop();
            if(q.empty()){
                cout << now;
                break;
            }
            else{
                q.push(now);
            }
        }

    }
    return 0;
}