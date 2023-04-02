#include <iostream>
using namespace std;

int main(){

	int e,s,m;
	int y = 1;

	cin >> e >> s >> m;

	while(y > 0){
		if(((y-e)%15 == 0) && ((y-s)%28 ==0) && ((y-m)%19 ==0)){
			cout << y;
			break;
		}
		else{
			y++;
		}
	}

	return 0;
}