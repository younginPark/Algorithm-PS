#include <iostream>
using namespace std;

int N;
int student[1000005];
int B, C;
long long ans;

void userInput(){
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> student[i];
    }
    cin >> B >> C;
}

void solution(){
    ans = N;
    for(int i = 0; i < N; i++){
        student[i] -= B;
    }
    for(int i = 0; i < N; i++){
        if(student[i] > 0){
            ans += student[i] / C;
            if(student[i] % C > 0){
                ans++;
            }
        }
    }
}

int main(){
    userInput();
    solution();
    cout << ans;
    return 0;
}