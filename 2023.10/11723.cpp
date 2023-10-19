#include <iostream>
#include <string>
using namespace std;

int M;
int arr[22];

void sol(){
    string condition;
    int num;
    cin >> condition;

    if(condition == "add"){
        cin >> num;
        if(arr[num] == 0){
            arr[num] = 1;
        }
    }
    else if(condition == "remove"){
        cin >> num;
        if(arr[num] == 1){
            arr[num] = 0;
        }
    }
    else if(condition == "check"){
        cin >> num;
        if(arr[num] == 1){
            cout << "1\n";
        }
        else{
            cout << "0\n";
        }
    }
    else if(condition == "toggle"){
        cin >> num;
        if(arr[num] == 0){
            arr[num] = 1;
        }
        else{
            arr[num] = 0;
        }
    }
    else if(condition == "all"){
        for(int i = 1; i <= 20; i++){
            arr[i] = 1;
        }
    }
    else if(condition == "empty"){
        for(int i = 1; i <= 20; i++){
            arr[i] = 0;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> M;
    for(int i = 0; i < M; i++){
        sol();
    }
    return 0;
}