#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int arr[1001][1001];
string str1;
string str2;
int main(){
    cin >> str1;
    cin >> str2;
    str1 = str1;
    str2 = str2;
    for(int i = 0; i <= str2.size(); i++){
        arr[i][0] = i;
    }
    for(int j = 0; j <= str1.size(); j++){
        arr[0][j] = j;
    }
    for(int i = 1; i <= str2.length(); i++){
        for(int j = 1; j <= str1.length(); j++){
            if(str2[i-1] == str1[j-1]){
                arr[i][j] = arr[i-1][j-1];
            }
            else{
                arr[i][j] = min(arr[i-1][j], arr[i][j-1]);
                arr[i][j] = min(arr[i][j], arr[i-1][j-1]) + 1;
            }
        }
    }
    printf("%d\n", arr[str2.length()][str1.length()]);
    return 0;
}