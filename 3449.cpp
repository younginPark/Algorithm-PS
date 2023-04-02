#include <iostream>
#include <string>
using namespace std;

int main(){

    int tc;
    cin >> tc;
    for(int i = 0; i < tc; i++){
        string str1;
        string str2;
        int ans = 0;
        cin >> str1 >> str2;
        for(int j = 0; j < str1.length(); j++){
            if(str1[j] != str2[j]){
                ans++;
            }
        }
        printf("Hamming distance is %d.\n", ans);
    }
    return 0;
}