#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int L, C;
char arr[16];
bool check[16];
int vowel = 0;

void go(string answer, int idx){
    //printf("!! %s\n", answer.c_str());
    if(answer.length() == L){
        if(vowel >= 1 && L-vowel >= 2){
            printf("%s\n", answer.c_str());
            return;
        }
    }
    for(int i = idx; i < C; i++){
        if(check[i] == false){
            if(arr[i] == 'a' || arr[i] == 'e' || arr[i] == 'i' 
            || arr[i] == 'o' || arr[i] == 'u'){
                vowel++;
                check[i] = true;
                go(answer+arr[i], i);
                check[i] = false;
                vowel--;
            }
            else{
                check[i] = true;
                go(answer+arr[i], i);
                check[i] = false;
            }
        }
    }
}

int main(){
    scanf("%d %d", &L, &C);
    for(int i = 0; i < C; i++){
        scanf("%s", &arr[i]);
    }
    sort(arr, arr+C);
    string answer;
    go(answer, 0);
    return 0;
}