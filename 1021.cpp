#include <iostream>
#include <deque>
using namespace std;

int main(){
	deque<int> dq;
    int idx = 0;
    int result = 0;
    int where = 0;
	int N = 0, M = 0;
	int find[51] = { 0, };

	cin >> N >> M;
	for(int i = 0; i < M; i++){
		cin >> find[i];
	}
	
    for(int i = 0; i < N; i++){
        dq.push_back(i+1);
    }

    while(idx < M){
        for(int i = 0; i < N; i++){
                if(dq[i] == find[idx]){
                    where = i;
                    break;
                }
            }
        if(where <= dq.size() - where){
            while(1){
                if(dq.front() == find[idx]){
                    dq.pop_front();
                    idx++;
                    N--;
                    break;
                }
                else{
                    dq.push_back(dq.front());
                    dq.pop_front();
                    result++;
                }
            }
        }
        else if(where > dq.size() - where){
            while(1){
                if(dq.front() == find[idx]){
                    dq.pop_front();
                    idx++;
                    N--;
                    break;
                }
                else{
                    dq.push_front(dq.back());
                    dq.pop_back();
                    result++;
                }
            }
        }
    }
    cout << result; 
	return 0;
}