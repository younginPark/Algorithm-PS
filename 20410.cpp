#include <iostream>
using namespace std;

int main() {

    int m, seed, x1, x2;
    cin >> m >> seed >> x1 >> x2;

    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            if((((i*seed)+j) % m) == x1 && (((i*x1)+j) % m) == x2){
                cout << i << " " << j;
                return 0;
            }
        }
    }

    return 0;
}