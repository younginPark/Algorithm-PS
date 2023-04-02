#include <iostream>
using namespace std;

int N, M;
int arr[9] = { 0, };
bool visit[9];

void func(int cnt){
	//cout << "now cnt: " << cnt<< "\n"; 
    if(cnt==M){ //종료조건
        for(int i=0;i<M;i++){
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
    
    for(int i=0;i<N;i++){
        if(!visit[i]){
            visit[i]=true;
            arr[cnt]=i+1;
            func(cnt+1);
            visit[i]=false;
        }
    }
}
int main(){

	cin >> N >> M;

	func(0);

	return 0;
}