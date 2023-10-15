#include <iostream>
#include <string>
using namespace std;

string val;
int arr[27];
int main(){
    cin >> val;
    for(int i = 0; i < val.size(); i++){
        val[i] = toupper(val[i]);
    }
    for(int i = 0; i < val.size(); i++){
        arr[val[i]-65] += 1;
    }
    int cnt = 0;
    int idx = 0;
    int same = 0;
    for(int i = 0; i < 27; i++){
        if(arr[i] > cnt){
            idx = i;
            cnt = arr[i];
            same = 0;
        }
        else if(arr[i] == cnt && cnt != 0){
            same++;
        }
    }
    if(same > 0){
        cout << "?";
    }
    else{
        cout << char(idx+65);
    }
    return 0;
}