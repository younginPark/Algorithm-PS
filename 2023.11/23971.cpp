#include <iostream>
#include <cmath>
using namespace std;

double H, W, N, M;

int main(){
    cin >> H >> W >> N >> M;
    int result =ceil(H/(N+1)) * ceil(W/(M+1));
    cout << result;
    return 0;
}