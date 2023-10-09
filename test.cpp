#include <iostream>
#include <functional>
#include <queue>
using namespace std;

int main(){

	priority_queue<pair<int,int> > pq;

	pq.push(make_pair(1,1));
	pq.push(make_pair(1,1));
	pq.push(make_pair(1,1));
	pq.push(make_pair(1,1));
	pq.push(make_pair(1,1));
	pq.push(make_pair(1,1));

	while(!pq.empty()){
		cout << pq.top().second << "\n";
		pq.pop();

	}
	return 0;
}