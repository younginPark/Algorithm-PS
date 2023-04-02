#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string str1;
string str2;
int dp[1001][1001];

int main(){
    cin >> str1 >> str2;
    for(int i = 1; i <= str1.length(); i++){
        for(int j = 1; j <= str2.length(); j++){
            if(str1[i-1] == str2[j-1]){
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else{
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                dp[i][j] = max(dp[i][j], dp[i-1][j-1]);
            }
        }
    }
    // for(int i = 1; i <= str1.length(); i++){
    //     for(int j = 1; j <= str2.length(); j++){
    //         printf("%d", dp[i][j]);
    //     }
    //     printf("\n");
    // }
    printf("%d\n", dp[str1.length()][str2.length()]);
    return 0;
}