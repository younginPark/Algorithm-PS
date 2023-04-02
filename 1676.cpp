#include <iostream>

using namespace std;

int main(){

    int n;
    int two = 0;
    int five = 0;
    cin >> n;
    for(int i = 1; i <= n; i++){
        int tmp = i;
        while (tmp >= 2){
            if(tmp%2 == 0){
                two++;
                tmp /= 2;
            }
            else{
                break;
            }
        }
        tmp = i;
        while (tmp >= 5){
            if(tmp%5 == 0){
                five++;
                tmp /= 5;
            }
            else{
                break;
            }
        }
    }
    printf("%d\n", min(two, five));
    
    return 0;
}
