#include <iostream>
#include <string>
using namespace std;

int main(){

    string str;
    getline(cin, str);
    int ans = 1;
    if(str[0] == ' '){
        ans = 0;
    }
    for(int i = 0; i < str.length(); i++){
        if(str[i] == ' '){
            ans++;
        }
    }
    if(str[str.length()-1] == ' '){
        ans--;
    }
    cout << ans;
    return 0;
}