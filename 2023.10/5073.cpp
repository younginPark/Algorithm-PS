#include <iostream>
#include <algorithm>
using namespace std;

int arr[4];

int main(){
    for(int i = 0; i < 1000; i++){
        for(int j = 0; j < 3; j++){
            cin >> arr[j];
        }
        if(arr[0] == 0 && arr[1] == 0 && arr[2] == 0){
            break;
        }
        sort(arr, arr+3);
        if(arr[2] >= arr[0] + arr[1]){
            cout << "Invalid\n";
        }
        else if(arr[0] == arr[1] && arr[1] == arr[2]){
            cout << "Equilateral\n";
        }
        else if((arr[0] == arr[1] && arr[1] != arr[2]) || (arr[0] == arr[2] && arr[2] != arr[1]) || (arr[1] == arr[2] && arr[2] != arr[0])){
            cout << "Isosceles\n";
        }
        else if(arr[0] != arr[1] && arr[1] != arr[2]){
            cout << "Scalene\n";
        }

    }
    return 0;
}