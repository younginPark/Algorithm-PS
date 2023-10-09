#include <iostream>
#include <cmath>
using namespace std;

/*
0,0 부터 앉혀야 최대한 많이 앉힐 수 있음
세로길이가 1이라고 생각했을 때 가로에 사람을 앉힐 수 있는 간격은 '앉을사람+가로간격' 임
그러므로 가로길이/(앉을사람1명+가로간격) 만큼 앉힐 수 있는데 
만약 결과에서 나머지가 생기면 자리가 한명 앉힐만큼 나온다는 의미로 +1 할 수 있음
=> 이거는 ceil 함수 통해 올림처리
*/

double H, W, N, M;

int main(){
    cin >> H >> W >> N >> M;
    int result =ceil(H/(N+1)) * ceil(W/(M+1));
    cout << result;
    return 0;
}